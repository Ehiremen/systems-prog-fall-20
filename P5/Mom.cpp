//
//  Mom.cpp
//  Programs
//
//  Created by Ehiremen Ekore on 11/20/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include "Mom.hpp"

Mom::Mom( char* argv[] ) : numKids( stoi(argv[1]) ) {
    srand(time ( NULL ));   // Random numbers used by all threads.
    
    m = Model(numKids - 1);
    kids = new Kid*[numKids];
    
    // loop to create the required number of kids
    for (int k=0; k<numKids; k++) {
        kids[k] = new Kid(&m, k);
    }
    
    cout << "\nMum is ready for action\n";
}

// -----------------------------------------------------------------------

Mom::~Mom() {
    
}

// -----------------------------------------------------------------------

void Mom::doGame() {
    playOneRound();
    printf("round is over\n");
    
    /*
    for (int k=numKids; k>0; k--) {
        playOneRound();
        
        if (k==1) {
            printf("\n\tWe have a winner!!!\n");
            printf("\t\tCongratulations kid #%d\n", m.chairArrayPtr[0]);
            break;
        }
    }
    */
    
    getKidsBack();
}

// -----------------------------------------------------------------------

void Mom::playOneRound() {
    printf("\n-------------------------------------------\n");
    int rc;
    
    pthread_mutex_lock(&m.mtx);
    const int numChairs = m.nChairs;
    const int kidsThisRound = numChairs + 1;
    
    m.nMarching = 0;
    for (int n=0; n<numChairs; n++) { // mark all chairs empty
        m.chairArrayPtr[n] = -1;
    }
    pthread_mutex_unlock(&m.mtx);
    
    // ---------------------------------
    
    for (int k=0; k<kidsThisRound; k++) { // tell each kid to stand
        rc = pthread_kill(kids[k]->getTid(), SIGUSR1);
        
        if (rc < 0) fatal("ERROR; returned from pthread_kill(): %d", rc);
    }
    
    // ---------------------------------
    
    for (;;) { // loop until each kid is marching
        pthread_mutex_lock(&m.mtx);
        rc = pthread_cond_wait(&m.turn, &m.mtx);
        
        if (m.nMarching == kidsThisRound) {
            pthread_mutex_unlock(&m.mtx);
            break;
        }
        pthread_mutex_unlock(&m.mtx);
        
        if (rc != 0) fatal("ERROR; returned from pthread_cond_wait(): %d", rc);
    }
    
    // ---------------------------------
    
    sleep(2);
    
    for (int k=0; k<kidsThisRound; k++) { // tell each kid to sit
        rc = pthread_kill(kids[k]->getTid(), SIGUSR2);
        if (rc < 0) fatal("ERROR; returned from pthread_kill(): %d", rc);
    }
    
    // ---------------------------------
    
    for (;;) { // loop until all kids have stopped marching
        rc = pthread_cond_wait(&m.turn, &m.mtx);
        
        pthread_mutex_lock(&m.mtx);
        if (m.nMarching == 0) {
            printf("In main: got all kids back this round!\n");
            pthread_mutex_unlock(&m.mtx);
            break;
        }
        pthread_mutex_unlock(&m.mtx);
        
        if (rc != 0) fatal("ERROR; returned from pthread_cond_wait(): %d", rc);
    }
    
    removeLoser();
}

// -----------------------------------------------------------------------

void Mom::removeLoser() {
    int loserID = -1;
    
    pthread_mutex_lock(&m.mtx);
    const int kidsPlaying = m.nChairs + 1;
    
    for (int p=0; p<kidsPlaying; p++) {
        if (kids[p]->getSeatNumber() == -1) {
            loserID = kids[p]->getID();
            swap(kids[p], kids[kidsPlaying-1]);
            m.nChairs--;
            break;
        }
    }
    
    pthread_kill(kids[kidsPlaying-1]->getTid(), SIGQUIT);
    
    if (kidsPlaying <= 2) { // kids[0] has won
        try {
            pthread_kill(kids[0]->getTid(), SIGQUIT);
        } catch (...) {
            cout << "Couldn't SIGQUIT kids[0]\n";
        }
    }
    pthread_mutex_unlock(&m.mtx);
    
    printf("kid #%d is out this round\n", loserID);
}

// -----------------------------------------------------------------------

void Mom::getKidsBack() {
    int rc, who;
    
    for (int t=0; t<numKids; t++) {
        who = kids[t]->getID();
        rc = pthread_join(kids[t]->getTid(), NULL);
        
        if (rc) fatal("ERROR; returned from join(): %d", rc);
        printf("In main: Welcome home %d\n", who);
    }
}
