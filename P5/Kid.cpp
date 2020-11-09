//
//  Kid.cpp
//  Programs
//
//  Created by Ehiremen Ekore on 11/8/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include "Kid.hpp"

extern void* startThread (void* kid);

Kid::Kid(Model* model, int ID) {
    kidID = ID;
    sharedModel = model;
    
    seatNumber = -1;
    
    sigemptyset(&sigSet);
    sigaddset(&sigSet, SIGUSR1);
    sigaddset(&sigSet, SIGUSR2);
    sigaddset(&sigSet, SIGQUIT);
    
    int rc = pthread_create( &tid, NULL, startThread, (void *)this );
    if(rc) fatal ("ERROR; return code from pthread_create() is %d", rc);
}

void Kid::play() {
    
}

void Kid::doMarch() {
    wantSeat = rand()%sharedModel->nChairs;
    
    sharedModel->nMarching++;
    pthread_cond_signal( &sharedModel->turn );
}

void Kid::doSit() {
    // make things fair for all kids by sleeping for a random amount of time
    int randomSleepTime = rand()%1000;
    usleep(randomSleepTime);
    pthread_kill( tid, SIGQUIT );
    
    int tryingThisSeat = wantSeat;
    
    sharedModel->nMarching++;
    pthread_mutex_lock( &sharedModel->turn_mutex);
 
    do {
        
        // chair is free!
        if (sharedModel->chairArrayPtr[tryingThisSeat] == -1) {
            sharedModel->chairArrayPtr[tryingThisSeat] = kidID;
            seatNumber = tryingThisSeat;
            break;
        }
        
        tryingThisSeat = (tryingThisSeat + 1) % sharedModel->nChairs;
    } while (tryingThisSeat != wantSeat);
    
    if (seatNumber == -1) {
        // didn't get a seat, signal mum I'm quitting
        
        ss.str("");
        ss <<"Bye from kid# " << kidID <<": no chair for me :(\n";
        cout <<ss.str();
        pthread_mutex_unlock( &sharedModel->turn_mutex);
        pthread_cond_signal( &sharedModel->turn );
        pthread_exit(0);
    }
    else {
        pthread_mutex_unlock( &sharedModel->turn_mutex);
        pthread_cond_signal( &sharedModel->turn );
    }
    
}
