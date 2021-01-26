//
//  Kid.cpp
//  P5_v2
//
//  Created by Ehiremen Ekore on 1/10/21.
//  Copyright © 2021 Ehiremen Ekore. All rights reserved.
//

#include "Kid.hpp"

extern void* startThread (void* kid);
const char* sigName (int sig);

// -----------------------------------------------------------

Kid::Kid(Model* model, int ID) : sharedModel(model), kidID(ID) {
    seatNumber = -1;
    
    // add signals to listen for
    sigemptyset(&sigSet);
    sigaddset(&sigSet, SIGUSR1);
    sigaddset(&sigSet, SIGUSR2);
    sigaddset(&sigSet, SIGQUIT);
    
    whereAmI = "In kid #" + to_string(kidID) + ": ";
    
    int rc = pthread_create( &tid, NULL, startThread, (void*) this );
    if(rc) fatal ("ERROR; return code from pthread_create() is %d", rc);
    else printf("%s Created kid #%d\n", whereAmI.c_str(), kidID);
}

// -----------------------------------------------------------

Kid::~Kid() {
    ss << "Kid #" << kidID << " is no more\n";
    printf("%s", ss.str().c_str());
    clearSS();
}

// -----------------------------------------------------------

void Kid::play() {
    int rc, sig;
    
    for (;;) {
        rc = sigwait(&sigSet, &sig);
        if (rc == -1) fatal("Can't handle this signal\n");
        
        else {
            printf("%s received Sig: %s\n", whereAmI.c_str(), sigName(sig));
            
            if (sig == SIGUSR1) doMarch();
            else if (sig == SIGUSR2) doSit();
            else if (sig == SIGQUIT) {
                printf("%s End of the road for me\n", whereAmI.c_str());
                pthread_exit(NULL);
                break;
            }
            else printf("False pass\n");
        }
    }
}

// -----------------------------------------------------------

void Kid::doMarch() {
    printf("%s I'm marching!\n", whereAmI.c_str());
    
    pthread_mutex_lock( &sharedModel->mtx);
    wantSeat = rand()%sharedModel->numChairs;
    sharedModel->nMarching++;
    pthread_cond_signal( &sharedModel->turn );
    pthread_mutex_unlock( &sharedModel->mtx);
}

// -----------------------------------------------------------

void Kid::doSit() {
    // sleep for a random amount of time (0.2-2 seconds)
    int randomSleepTime = (rand()%1800) + 200;
    usleep(randomSleepTime);
    int tryingThisSeat = wantSeat;
    
    // ------------------
    
    int numChairsInPlay = sharedModel->numChairs;
    
    do {
        ss << "\t" << whereAmI << " Going for a chair\n";
        printf("%s", ss.str().c_str());
        clearSS();
        
        // chair is(possibly) free!
        if (sharedModel->chairArray[tryingThisSeat] == -1) {
            pthread_mutex_lock(&sharedModel->mtx);
            
            if (sharedModel->chairArray[tryingThisSeat] != -1) {
                pthread_mutex_unlock( &sharedModel->mtx );
            }
            else { // actually got the seat, yay
                sharedModel->chairArray[tryingThisSeat] = kidID;
                seatNumber = tryingThisSeat;
                pthread_cond_signal( &sharedModel->turn );
                pthread_mutex_unlock( &sharedModel->mtx );
                
                ss << "\t\t" << whereAmI << " Got chair #" << tryingThisSeat << "\n";
                printf("%s", ss.str().c_str());
                clearSS();
                
                break;
            }
        }
        
        // move to next chair
        tryingThisSeat++;
        
        // using this if statement to avoid doing a modular
        // operation on each iteration of the loop
        if (tryingThisSeat == numChairsInPlay) tryingThisSeat = 0;
        
    } while (tryingThisSeat != wantSeat);
    
    ss << "\t" << whereAmI << " Done trying to sit\n";
    printf("%s", ss.str().c_str());
    clearSS();
    // ------------------
    
    pthread_mutex_lock( &sharedModel->mtx );
    sharedModel->nMarching--;
    pthread_cond_signal( &sharedModel->turn );
    pthread_mutex_unlock( &sharedModel->mtx );
    
}
