//
//  Mom.cpp
//  P5_v2
//
//  Created by Ehiremen Ekore on 1/10/21.
//  Copyright © 2021 Ehiremen Ekore. All rights reserved.
//

#include "Mom.hpp"

// GLOBAL FUNCTIONS
// -----------------------------------------------------------

void* startThread (void* kid) {
    Kid* k = (Kid*) kid;
    k->play();
    return NULL;
}

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

// -----------------------------------------------------------

void emphasisBanner(const string str) {
    const string tab = "    ";
    const int msgLen = str.length();
    const int borderLen = msgLen + (4*tab.length());
    
    ostringstream ss;
    
    ss << "\n" << tab << " ";
    for (int i=0; i<borderLen; i++) ss << "-";
    ss << "\n" << tab << "|";
    for (int i=0; i<borderLen; i++) ss << " ";
    ss << "|\n";
    ss << tab << "|" << tab << tab << str << tab << tab << "|";
    ss << "\n" << tab << "|";
    for (int i=0; i<borderLen; i++) ss << " ";
    ss << "|\n" << tab << " ";
    for (int i=0; i<borderLen; i++) ss << "-";
    ss << "\n\n";
    
    printf("%s", ss.str().c_str());
}

// -----------------------------------------------------------

Mom::Mom (char* argv[]): numKids(stoi(argv[1])) {
    srand(time (NULL) );    // Random numbers used by all threads.
    
    if (numKids <= 1) {
        fatal("Need at least 2 kids for the game. Bye!\n\n");
    }

    kidsStillPlaying = numKids;
    
    model = new Model(numKids - 1);
    kids = new Kid*[numKids];
    
    for (int k=0; k<numKids; k++) {
        kids[k] = new Kid(model, k);
    }
    
    printf("In Mom: Game created for %d kids!\n", numKids);
    
    doGame();
}

// -----------------------------------------------------------

Mom::~Mom() {
    for (int k=0; k<numKids; k++) delete kids[k];
    delete[] kids;
    delete model;
    cout << "\nParty's over, kids!\n";
}

// -----------------------------------------------------------

void Mom::doGame() {
    for (;;) {
        playOneRound(model, kids);
        if (kidsStillPlaying == 1) break;
    }
    sayWinner();
    getKidsBack();
}

// -----------------------------------------------------------

void Mom::playOneRound(Model* m, Kid* players[]){
    printf("\n---------------------------------------------\n\n");
    
    startMusic(m, players);
    stopMusic(m, players);
    removeLoser();
}

// -----------------------------------------------------------

void Mom::startMusic(Model* m, Kid* players[]){
    int rc;
    pthread_mutex_lock(&m->mtx);
    fill_n(m->chairArray, m->numChairs, -1);
    m->nMarching = 0;
    
    kidsStillPlaying = model->numChairs + 1;
    pthread_mutex_unlock(&m->mtx);
    
    // ---------------------------------
    
    for (int k=0; k<kidsStillPlaying; k++) {
        players[k]->standUp();
        rc = pthread_kill(players[k]->getTid(), SIGUSR1);
        if (rc < 0) fatal("ERROR; returned from Kid #%d pthread_kill(SIGUSR1): %d", players[k]->getID(), rc);
    }
    
//    pthread_mutex_lock(&m->mtx);
    
    int localMarching;
    for (;;) {
        pthread_mutex_lock(&m->mtx);
        rc = pthread_cond_wait(&m->turn, &m->mtx);
        localMarching = m->nMarching;
        pthread_mutex_unlock(&m->mtx);
        
        if (rc < 0) fatal("ERROR; returned from pthread_cond_wait(): %d", rc);
        
        if (localMarching == kidsStillPlaying) {
            printf("\nIn Mom: Everyone is marching now\n\n");
            break;
        }
    }
     
//    pthread_mutex_unlock(&m->mtx);
}

// -----------------------------------------------------------

void Mom::stopMusic(Model* m, Kid* players[]) {
    sleep(2);
    int rc;
    
    for (int k=0; k<kidsStillPlaying; k++) {
        rc = pthread_kill(players[k]->getTid(), SIGUSR2);
        if (rc < 0) fatal("ERROR; returned from Kid #%d pthread_kill(SIGUSR2): %d", players[k]->getID(), rc);
    }
    
    int localMarching;
    for (;;) {
        pthread_mutex_lock(&m->mtx);
        rc = pthread_cond_wait(&m->turn, &m->mtx);
        localMarching = m->nMarching;
        pthread_mutex_unlock(&m->mtx);
        
        if (rc < 0) fatal("ERROR; returned from pthread_cond_wait(): %d", rc);
        
        if (localMarching == 0) {
            printf("\nIn Mom: All seats are taken!\n\n");
            break;
        }
    }
}

// -----------------------------------------------------------

void Mom::removeLoser() {
//    cerr << "finding loser" << endl;
    int loserID = -1;
    
    for (int p=0; p<kidsStillPlaying; p++) {
        if (kids[p]->isStanding()) {
            loserID = kids[p]->getID();
            swap(kids[p], kids[kidsStillPlaying-1]);
            pthread_mutex_lock(&model->mtx);
            model->numChairs--;
            pthread_mutex_unlock(&model->mtx);
            break;
        }
    }
    
    printf("In Mom: this round's loser is kid#%d\n", loserID);
    pthread_kill(kids[kidsStillPlaying-1]->getTid(), SIGQUIT);
    
    kidsStillPlaying--; // a kid has been removed from the game
    
    if (kidsStillPlaying == 1) { // kids[0] has won
        try {
            pthread_kill(kids[0]->getTid(), SIGQUIT);
        } catch (...) {
            cout << "Couldn't SIGQUIT kids[0]\n";
        }
    }
//    pthread_mutex_unlock(&model->mtx);
}

// -----------------------------------------------------------

void Mom::getKidsBack(){
    int rc, who;
    printf("In Mom: Getting kids back\n");
    
    for (int t=0; t<numKids; t++) {
        who = kids[t]->getID();
        rc = pthread_join(kids[t]->getTid(), NULL);
        
        if (rc) fatal("ERROR; returned from join(): %d", rc);
        printf("In Mom: Welcome home kid #%d\n", who);
    }
}

// -----------------------------------------------------------

void Mom::sayWinner(){
    ostringstream ss;
    ss << "Kid #" << kids[0]->getID() << " wins the game!";
    emphasisBanner(ss.str());
}
