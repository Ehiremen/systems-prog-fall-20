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
            FILE* kidIn;   // Stream for kid to send to mom.
            FILE* kidOut;  // Stream for mom to send to kid.
    };
    
    toPoll* kidSocks;
    toPoll* momSock;
    char* chairs;
    Player* players;
    int counter, startingN, playersAlive;
    // C-streams, buffers, and everything else needed to communicate between one of the MomLogic functions and another
    
    const char chairFree = '1';
    const char chairTaken = '0';
    
    // variables for handling socket i/o
    char buffer[bufferLen];
    int nBytes = 0;
    
    void playOneRound();
    void initRound ();
    void stopTheMusic ();
    void checkSockets () {}
    void openPlayerIOStreams();
    void getKidsNames();
    
public:
    MomLogic (toPoll* momSock, toPoll* socks, int N);
    ~MomLogic ();
    void run();
};
