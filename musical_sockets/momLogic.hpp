//
//  momLogic.hpp
//  Programs
//
//  Created by Ehiremen Ekore on 12/10/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#pragma once
#include "protocol.hpp"
#include "socktypes.h"
#include "tools.hpp"

using namespace std;

const int bufferLen = 100;

class MomLogic {
private:
    struct Player {
            string name = "??";
            bool alive = true;
            bool standing = false;
            FILE* kidIn;   // Stream for kid to send to mom.
            FILE* kidOut;  // Stream for mom to send to kid.
    };
    
    toPoll* kidSocks;
    char* chairs;
    Player* players;
    int freeChairsThisRound, startingN, playersThisRound;
    bool gameOver = false;
    // C-streams, buffers, and everything else needed to communicate between one of the MomLogic functions and another
    
    // variables for handling socket i/o
    char buffer[bufferLen];
    
    void playOneRound();
    void initRound();
    void openPlayerIOStreams();
    void getKidsNames();
    void stopTheMusic();
    void doPoll();
    void handleWantMessage(int id);
    void quitStandingPlayers();
    
public:
    MomLogic (toPoll* socks, int N);
    ~MomLogic ();
    void run();
};
