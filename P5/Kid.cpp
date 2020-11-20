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
    int rc;
    seatNumber = -1;
    
    sigemptyset(&sigSet);
    sigaddset(&sigSet, SIGUSR1);
    sigaddset(&sigSet, SIGUSR2);
    sigaddset(&sigSet, SIGQUIT);
    
    sigControl.sa_handler = sigHandler;
    sigControl.sa_mask = sigSet;
    sigControl.sa_flags = 0;
    
    
    whereAmI += to_string(kidID) + ":";
    
    rc = pthread_create( &tid, NULL, startThread, (void *) this );
    if(rc) fatal ("ERROR; return code from pthread_create() is %d", rc);
    else {
        printf("%s Created kid #%d\n", whereAmI.c_str(), kidID);
    }
}

// -----------------------------------------------------------------------

Kid::~Kid() {
    cerr << "Kid #" << kidID << " is no more" << endl;
}

// -----------------------------------------------------------------------

void Kid::sigHandler( int sig ) {
    printf ("Caught signal: %s\n", sigName(sig));
    
    if (sig == SIGUSR1) doMarch();
    else if (sig == SIGUSR2) doSit();
    else if (sig == SIGQUIT){
        cout << whereAmI << " This is the end of the road for kid #" << kidID << endl;
//            printf("%s This is the end of the road for kid #%d\n", whereAmI.c_str(), kidID);
        pthread_exit(NULL);
    }
    else {
        exit(sig);
    }
}

// -----------------------------------------------------------------------

const char* Kid::sigName (int sig) {
    switch (sig) {
        case SIGUSR1:
            return "SIGUSR1"; break;
            
        case SIGUSR2:
            return "SIGUSR2"; break;
            
        case SIGQUIT:
            return "SIGQUIT"; break;
            
        default: return "Unexpected signal";
    }
}

// -----------------------------------------------------------------------

void Kid::play() {
    int rc, sig;
    for (;;) {
        rc = sigwait(&sigSet, &sig);
        printf("%s received Sig %d\n", whereAmI.c_str(), sig);
        
        
        if (sig == SIGUSR1) doMarch();
        else if (sig == SIGUSR2) doSit();
        else if (sig == SIGQUIT){
            cout << whereAmI << " This is the end of the road for kid #" << kidID << endl;
            pthread_exit(NULL);
        }
        else {
            exit(sig);
        }
    }
}

// -----------------------------------------------------------------------

void Kid::doMarch() {
    printf("%s I'm marching!\n", whereAmI.c_str());
    
    pthread_mutex_lock( &sharedModel->mtx);
    wantSeat = rand()%sharedModel->nChairs;
    sharedModel->nMarching++;
    pthread_cond_signal( &sharedModel->turn );
    pthread_mutex_unlock( &sharedModel->mtx);
    
    printf("%s Donemarching!\n", whereAmI.c_str());
}

// -----------------------------------------------------------------------

void Kid::doSit() {
    // make things fair for all kids by sleeping for a random amount of time
    int randomSleepTime = rand()%1000;
    usleep(randomSleepTime);
    
    int tryingThisSeat = wantSeat;
    
    pthread_mutex_lock( &sharedModel->mtx);
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
        // signal mum that I'm quitting
        
        ss.str("");
        ss << whereAmI << " Bye from kid #" << kidID <<": no chair for me :(\n";
        cout <<ss.str();
        pthread_cond_signal( &sharedModel->turn );
        pthread_mutex_unlock( &sharedModel->mtx);
        pthread_exit(NULL);
    }
    
    else {
        printf("%s got chair #%d\n", whereAmI.c_str(), seatNumber);
        pthread_cond_signal( &sharedModel->turn );
        pthread_mutex_unlock( &sharedModel->mtx);
    }
}
