//
//  main.cpp
//  Programs
//
//  Created by Ehiremen Ekore on 10/30/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include "tools.hpp"
#include "Model.hpp"
#include "Kid.hpp"
#include <signal.h>

using namespace std;

void* startThread (void* kid) {
    Kid* k = (Kid*) kid;
    k->play();
    return NULL;
}

// -----------------------------------------------------------------------

const char* sigName (int sig) {
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

void sigHandler (int sig) {
    printf ("Caught signal: %s\n", sigName(sig));
}

// -----------------------------------------------------------------------
// Prototypes

void PlayOneRound( Model* m, Kid* players[] );

// -----------------------------------------------------------------------

int main (int argc, char* argv[]) {
    banner();
    cerr << "\tWelcome to musical chairs!\n\n";
    
    if (argc != 2) {
        fatal("ERROR; must run game with only one extra argument (number--int--of kids!\n");
    }
    
    srand(time ( NULL ));   // Random numbers used by all threads.
    signal(SIGINT, sigHandler);
    
    const int numKids = stoi(argv[1]);
    Model m(numKids - 1);
    int rc;
    pthread_t who;
    
    Kid* kids[numKids];     // array of pointers to Kid objects for each player.
    
    // loop to create the required number of kids
    for (int k=0; k<numKids; k++) {
        kids[k] = new Kid(&m, k);
    }
    
    for (int k=numKids; k>0; k--) {
        PlayOneRound(&m, kids);
        
        if (k==1) {
            printf("\n\tWe have a winner!!!\n");
            printf("\t\tCongratulations kid #%d\n", m.chairArrayPtr[0]);
        }
    }
    
    // joining loop
    for (int t=0; t<numKids; t++) {
        who = kids[t]->getTid();
        rc = pthread_join(kids[t]->getTid(), NULL);
        
        if (rc) fatal("ERROR; returned from join(): %d", rc);
        printf("In main: Welcome home %ld\n", who);
    }
    
    bye();
    return 0;
}

// -----------------------------------------------------------------------

void PlayOneRound( Model* m, Kid* players[] ) {
    
}
