//
//  momLogic.cpp
//  Programs
//
//  Created by Ehiremen Ekore on 12/10/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include "momLogic.hpp"

MomLogic::MomLogic (toPoll* momSock, toPoll* socks, int N) : momSock(momSock), kidSocks(socks), startingN(N) {
    chairs = new char[N];
//    chairs[N] = '\0';   // end the chairs array with a null terminator
    players = new Player[N];
    
    openPlayerIOStreams();
    cout << "In MomLogic: debug line\n";
}

// ---------------------------------------------------

MomLogic::~MomLogic() {
    delete chairs;
//    for (int k=0; k<startingN; k++) delete players[k];
    delete [] players;
}

// ---------------------------------------------------

void MomLogic::run(){
    cout << "In MomLogic: Running\n";
    getKidsNames();
    cout << "In MomLogic: Got names\n";
    playersAlive = startingN;
//    for (int round=1; round<startingN; ++round) {
        playOneRound();
//    }
}

// ---------------------------------------------------

void MomLogic::openPlayerIOStreams() {  // open both input and output
                                        // streams for all players
    for (int p=0; p<startingN; ++p) {
        cout << "In MomLogic: opening io streams\n";
        players[p].kidIn = fdopen( kidSocks[p].fd, "r" );
        players[p].kidOut = fdopen( kidSocks[p].fd, "w" );
        cout << "player " << p << " fd = " << kidSocks[p].fd << endl;
    }
}

// ---------------------------------------------------

void MomLogic::getKidsNames() {
    for (int k=0; k<startingN; k++){
        fscanf(players[k].kidIn, "%s", buffer);
        players[k].name = buffer;
        cout << "player " << k << " got name: " << buffer << endl;
//        printf("%s is your name\n", players[k].name.c_str());
    }
}

// ---------------------------------------------------

void MomLogic::playOneRound() {
    initRound();
    //stopTheMusic();
    
}

// ---------------------------------------------------

void MomLogic::initRound() {
    int chairsThisRound = playersAlive - 1;
    for (int c=0; c<chairsThisRound; ++c) {
        chairs[c] = '1';
    }
    cout << "In MomLogic: chairs are free!\n";
    chairs[chairsThisRound] = '\0';
    
    // tell all remaining players to GETUP
    for (int p=0; p<startingN; ++p) {
        if (!players[p].alive) continue;
        
        
//        int status = fprintf( players[p].kidOut, "%s %d", commandsStr[GETUP].c_str(), chairsThisRound );
//        if (status!=1) fatalp("Error writing \"GETUP\" to %s", players[p].name.c_str());
        
//        else cout << "In MomLogic: player told to get up\n";
//        fflush(players[p].kidOut);
        
         
        nBytes = write(kidSocks[p].fd, commandsStr[GETUP].c_str(), commandsStr[GETUP].size());
//        nBytes = write(momSock->fd, commandsStr[GETUP].c_str(), commandsStr[GETUP].size());
//        fflush(players[p].kidOut);
        cout << commandsStr[GETUP] << endl << endl;
        if (nBytes <= 0) fatalp("Error writing \"GETUP\" to %s", players[p].name.c_str());
    }
    
    cout << "In MomLogic: GETUP sent to all kids\n";
}

// ---------------------------------------------------

void MomLogic::stopTheMusic () {
    sleep(2);
    for (int p=0; p<startingN; ++p) {
        if (!players[p].alive) continue;
        
        nBytes = write(kidSocks[p].fd, commandsStr[GETUP].c_str(), commandsStr[GETUP].size());
        
        if (nBytes <= 0) fatalp("Error writing \"SIT\" to %s", players[p].name.c_str());
        /*
        int status = fprintf( players[p].kidOut, "%s\n", commandsStr[SIT].c_str() );
        if (status!=1) fatalp("Error writing \"SIT\" to %s", players[p].name.c_str());
        fflush(players[p].kidOut);
         */
    }
}
