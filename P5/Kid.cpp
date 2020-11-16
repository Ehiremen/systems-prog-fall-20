//
//  Kid.cpp
//  Programs
//
//  Created by Ehiremen Ekore on 11/8/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include "Kid.hpp"

extern void* startThread (void* kid);

Kid::Kid(Model* model, int ID) : sharedModel(model), kidID(ID) {
//    kidID = ID;
//    sharedModel = model;
    
    seatNumber = -1;
    
    sigemptyset(&sigSet);
    sigaddset(&sigSet, SIGUSR1);
    sigaddset(&sigSet, SIGUSR2);
    sigaddset(&sigSet, SIGQUIT);
    
    int rc = pthread_create( &tid, NULL, startThread, (void *)this );
    if(rc) fatal ("ERROR; return code from pthread_create() is %d", rc);
}

// -----------------------------------------------------------------------

Kid::~Kid() {
    cerr << "Kid #" << kidID << " is no more" << endl;
}

// -----------------------------------------------------------------------

void Kid::play() {
    
}

// -----------------------------------------------------------------------

void Kid::doMarch() {
    wantSeat = rand()%sharedModel->nChairs;
    
    pthread_mutex_lock( &sharedModel->turn_mutex);
    sharedModel->nMarching++;
    pthread_cond_signal( &sharedModel->turn );
    pthread_mutex_unlock( &sharedModel->turn_mutex);
}

// -----------------------------------------------------------------------

void Kid::doSit() {
    // make things fair for all kids by sleeping for a random amount of time
    int randomSleepTime = rand()%1000;
    usleep(randomSleepTime);
    pthread_kill( tid, SIGQUIT );
    
    int tryingThisSeat = wantSeat;
    
    pthread_mutex_lock( &sharedModel->turn_mutex);
    sharedModel->nMarching--;
    
    int numChairsInPlay = sharedModel->nChairs;
    do {
        
        // chair is free!
        if (sharedModel->chairArrayPtr[tryingThisSeat] == -1) {
            sharedModel->chairArrayPtr[tryingThisSeat] = kidID;
            seatNumber = tryingThisSeat;
            break;
        }
        
        // chair is not free :(, move to next chair
        else {
            tryingThisSeat = (tryingThisSeat + 1);
            
            // using this if statement to avoid doing a modular
            // operation on each iteration of the loop
            if (tryingThisSeat == numChairsInPlay) tryingThisSeat = 0;
        }
        
    } while (tryingThisSeat != wantSeat);
    
    if (seatNumber == -1) {
        // didn't get a seat, signal mum that I'm quitting
        
        ss.str("");
        ss <<"Bye from kid #" << kidID <<": no chair for me :(\n";
        cout <<ss.str();
        pthread_cond_signal( &sharedModel->turn );
        pthread_mutex_unlock( &sharedModel->turn_mutex);
        pthread_exit(0);
    }
    
    else {
        pthread_cond_signal( &sharedModel->turn );
        pthread_mutex_unlock( &sharedModel->turn_mutex);
    }
    
}
