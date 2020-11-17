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
    if (sig == SIGKILL) {
        exit(sig);
    }
}

// -----------------------------------------------------------------------
// Prototypes

void PlayOneRound( Model* m, Kid* players[] );
void removeLoser( Model* m, Kid* players[] );

// -----------------------------------------------------------------------

int main (int argc, char* argv[]) {
    banner();
    cerr << "\tWelcome to musical chairs!\n\n";
    
    if (argc != 2) {
        fatal("ERROR; must run game with only one extra argument (number--int--of kids!\n");
    }
    
    srand(time ( NULL ));   // Random numbers used by all threads.
//    signal(SIGINT, sigHandler);
    
    const int numKids = stoi(argv[1]);
    Model m(numKids - 1);
    int rc, who;
    
    Kid* kids[numKids];     // array of pointers to Kid objects for each player.
    
    // loop to create the required number of kids
    for (int k=0; k<numKids; k++) {
        kids[k] = new Kid(&m, k);
    }
    
    cout << endl << endl << "Kids are alive now!" << endl << endl;
    
    PlayOneRound(&m, kids);
    printf ("round is over\n");
    /*
    for (int k=numKids; k>0; k--) {
        PlayOneRound(&m, kids);
        
        if (k==1) {
            printf("\n\tWe have a winner!!!\n");
            printf("\t\tCongratulations kid #%d\n", m.chairArrayPtr[0]);
            break;
        }
    }
    */
    
    // joining loop
    for (int t=0; t<numKids; t++) {
        who = kids[t]->getID();
        rc = pthread_join(kids[t]->getTid(), NULL);
        
        if (rc) fatal("ERROR; returned from join(): %d", rc);
        printf("In main: Welcome home %d\n", who);
    }
    
    bye();
    exit( 0 );
}

// -----------------------------------------------------------------------

void PlayOneRound( Model* m, Kid* players[] ) {
    printf("\n-------------------------------------------\n");
    int rc;
    
    pthread_mutex_lock(&m->turn_mutex);
    
    const int kidsPlaying = m->nChairs + 1;
    m->nMarching = 0;
    for (int n=0; n<m->nChairs; n++) {
        m->chairArrayPtr[n] = -1;
    }
    
    pthread_mutex_unlock(&m->turn_mutex);
    
    for (int k=0; k<kidsPlaying; k++) {
        players[k]->standUp();
        rc = pthread_kill(players[k]->getTid(), SIGUSR1);
        
        if (rc < 0) fatal("ERROR; returned from pthread_kill(): %d", rc);
    }
    
    for (;;) {
        rc = pthread_cond_wait(&m->turn, &m->turn_mutex);
        
        pthread_mutex_lock(&m->turn_mutex);
        if (m->nMarching == kidsPlaying) {
            pthread_mutex_unlock(&m->turn_mutex);
            break;
        }
        pthread_mutex_unlock(&m->turn_mutex);
        
        if (rc != 0) fatal("ERROR; returned from pthread_cond_wait(): %d", rc);
    }
    
    sleep(2);
    
    for (int k=0; k<kidsPlaying; k++) {
        rc = pthread_kill(players[k]->getTid(), SIGUSR2);
        
        if (rc < 0) fatal("ERROR; returned from pthread_kill(): %d", rc);
    }
    
    for (;;) {
        rc = pthread_cond_wait(&m->turn, &m->turn_mutex);
        
        pthread_mutex_lock(&m->turn_mutex);
        if (m->nMarching == 0) {
            printf("In main: got all kids back this round!\n");
            pthread_mutex_unlock(&m->turn_mutex);
            break;
        }
        pthread_mutex_unlock(&m->turn_mutex);
        
        if (rc != 0) fatal("ERROR; returned from pthread_cond_wait(): %d", rc);
    }
    
    removeLoser(m, players);
    
}

// -----------------------------------------------------------------------

void removeLoser( Model* m, Kid* players[] ) {
    int loserID = -1;
    pthread_mutex_lock(&m->turn_mutex);
    const int kidsPlaying = m->nChairs + 1;
    
    for (int p=0; p<kidsPlaying; p++) {
        if (players[p]->getSeatNumber() == -1) {
            loserID = players[p]->getID();
            swap(players[p], players[kidsPlaying-1]);
            m->nChairs--;
            break;
        }
    }
    
    pthread_kill(players[kidsPlaying-1]->getTid(), SIGQUIT);
    pthread_mutex_unlock(&m->turn_mutex);
    
    printf("kid #%d is out this round\n", loserID);
}
