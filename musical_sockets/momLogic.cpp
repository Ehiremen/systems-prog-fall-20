//
//  momLogic.cpp
//  Programs
//
//  Created by Ehiremen Ekore on 12/10/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include "momLogic.hpp"

MomLogic::MomLogic (toPoll* socks, int N) : kidSocks(socks), startingN(N) {
    chairs = new char[N];
    chairs[N-1] = '\0';   // end the chairs array with a null terminator
    players = new Player[N];
    openPlayerIOStreams();
}

// ---------------------------------------------------

MomLogic::~MomLogic() {
    delete chairs;
    delete [] players;
}

// ---------------------------------------------------

void MomLogic::run(){
    cout << "In MomLogic: Running\n";
    getKidsNames();
    cout << "In MomLogic: Got names\n\n";
    
    for (int r=0; r<=startingN; r++) {
        playersThisRound = 0;
        for (int p=0; p<startingN; ++p) {
            if (players[p].alive) playersThisRound++;
        }
        if (playersThisRound<=0) break;
        playOneRound();
        if (gameOver) break;
    }
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
    int status, numNamesGotten = 0;
    for (;;) {
        status = poll(kidSocks, startingN, -1);
        if (status < 0)  fatalp("Error in poll().\t");
        if (status == 0) {
            cout << "In MomLogic: poll timed out\n";
            continue;
        }
        
        for (int k=0; k<startingN; k++){
            if (kidSocks[k].revents != 0 && players[k].alive){
                fscanf(players[k].kidIn, "%s", buffer);
                players[k].name = buffer;
                cout << "player " << k << " got name: " << buffer << endl;
                numNamesGotten++;
            }
        }
        if (numNamesGotten == startingN) break;
    }
    
}

// ---------------------------------------------------

void MomLogic::playOneRound() {
    
    if (playersThisRound == 1) {
        cout << "\n";
        for (int i=0; i<40; i++) cout << "=";
        cout << "\n\nIn MomLogic: We have a winner!\n";
        for (int p=0; p<startingN; ++p) {
            if (players[p].alive) {
                cout << "Congrats, " << players[p].name << endl;
                fprintf(players[p].kidOut, "%s\n", commandsStr[PRIZE].c_str());
                fflush(players[p].kidOut);
                break;
            }
        }
        gameOver = true;
    }
    
    else {
        initRound();
        stopTheMusic();
    }
}

// ---------------------------------------------------

void MomLogic::initRound() {
    // make some sort of heading
    cout << "\n";
    for (int i=0; i<15; i++) cout << "=";
    cout << "NEW ROUND";
    for (int i=0; i<15; i++) cout << "=";
    cout << "\n";
    
    freeChairsThisRound = playersThisRound - 1;
    for (int c=0; c<freeChairsThisRound; ++c) {
        chairs[c] = '1';
    }
    cout << "In MomLogic: chairs are free!\n";
    chairs[freeChairsThisRound] = '\0';
    
    // tell all remaining players to GETUP
    for (int p=0; p<startingN; ++p) {
        if (!players[p].alive) continue;
        
        int status = fprintf( players[p].kidOut, "%s %d\n", commandsStr[GETUP].c_str(), freeChairsThisRound );
        fflush(players[p].kidOut);
        if (status<1) fatalp("Error writing \"GETUP\" to %s", players[p].name.c_str());
        players[p].standing = true;
    }
    
    cout << "In MomLogic: GETUP sent to all kids\n";
}

// ---------------------------------------------------

void MomLogic::stopTheMusic () {
    sleep(2);
    for (int p=0; p<startingN; ++p) {
        if (!players[p].alive) continue;
        int status = fprintf( players[p].kidOut, "%s\n", commandsStr[SIT].c_str() );
        if (status<1) fatalp("Error writing \"SIT\" to %s", players[p].name.c_str());
        fflush(players[p].kidOut);
    }
    doPoll();
}

// ---------------------------------------------------

void MomLogic::doPoll() {
    int status;
    for (;;) {
        status = poll(kidSocks, startingN, -1);
        if (status < 0)  fatalp("Error in poll().\t");
        if (status == 0) {
            cout << "In MomLogic: poll timed out\n";
            continue;
        }
        
        int k;
        for (k = 0; k < startingN; k++) {
            if (kidSocks[k].revents != 0 && players[k].alive) handleWantMessage(k);
        }
        
        if (freeChairsThisRound == 0) {
            quitStandingPlayers();
            break;
        }
        if (playersThisRound <= 1) break;
    }
}

// ---------------------------------------------------

void MomLogic::handleWantMessage(int id) {
    memset(buffer, '\0', sizeof(buffer));
    int seatToCheck = -1;
    if (kidSocks[id].revents != 0) {
        if (kidSocks[id].revents & POLLIN) {// This is a read event--read it
            int status = fscanf(players[id].kidIn, "%s %d", buffer, &seatToCheck);
            
            if (errno == ECONNRESET) {
                sayp("Kid %s disappeared", players[id].name.c_str());
                playersThisRound--;
                players[id].alive = false;
                fclose(players[id].kidIn);
                fclose(players[id].kidOut);
                return;
            }
            
            // ====================
            
            if (strcmp(buffer, "WANT") == 0 ) {
                if ((freeChairsThisRound > 0) && (chairs[seatToCheck] == '1')) { // chair is free
                    fprintf(players[id].kidOut, "%s\n", commandsStr[ACK].c_str());
                    fflush(players[id].kidOut);
                    chairs[seatToCheck] = '0'; // mark chair as taken
                    --freeChairsThisRound;
                    --playersThisRound;
                    players[id].standing = false;
                    cout << "In MomLogic: ACK sent to " << players[id].name << endl;
                    return;
                }
                else { // chair is not free
                    if (freeChairsThisRound < 1) {
                        fprintf(players[id].kidOut, "%s\n", commandsStr[QUIT].c_str());
                        fflush(players[id].kidOut);
                        players[id].alive = false;
                        --playersThisRound;
                        cout << "In MomLogic: " << players[id].name << " is out this round\n";
                        return;
                    }
                    
                    
                    // for some reason, using commandsStr[NACK]
                    // caused the NACK to not be received
                    fprintf(players[id].kidOut, "%s %s\n", "NACK", chairs);
                    fflush(players[id].kidOut);
                }
            }
            else {
                cout << "In MomLogic: not sure how to handle command (" << buffer << ")\n";
            }
        }
    }
    
    else if (kidSocks[id].revents & POLLHUP) {  // Caller hung up.
        say("Kid %s left :(\n", players[id].name.c_str());
        players[id].alive = false;
        playersThisRound--;
        fclose(players[id].kidIn);
        fclose(players[id].kidOut);
    }
}

// ---------------------------------------------------

void MomLogic::quitStandingPlayers() {
    for (int p=0; p<startingN; ++p) {
        if (players[p].alive && players[p].standing) {
            fprintf(players[p].kidOut, "%s\n", commandsStr[QUIT].c_str());
            fflush(players[p].kidOut);
            players[p].alive = false;
        }
    }
    cout << "In MomLogic: sent \"QUIT\" to all standing kids\n";
}
