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

int main (int argc, char* argv[]) {
    banner();
    cerr << "\tWelcome to musical chairs!\n\n";
    
    if (argc != 2) {
        fatal("ERROR; must run game with only one extra argument (number--int--of kids!\n");
    }
    
    srand(time ( NULL ));  // Random numbers used by all threads.
    signal(SIGINT, sigHandler);
    
    int numKids = stoi(argv[1]);
    Model m(numKids);
    
    bye();
    return 0;
}
