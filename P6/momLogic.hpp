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

struct Player {
        string name = "??";
        bool alive = false;
        FILE* kidIn;   // Stream for kid to send to mom.
        FILE* kidOut;  // Stream for mom to send to kid.
};

class MomLogic {
private:
    char* chairs;
    int counter;
    Player* players;
    // C-streams, buffers, and everything else needed to communicate between one of the MomLogic functions and another
    void initRound ();
    void stopTheMusic ();
    void checkSockets ();
    
public:
    MomLogic ();
    ~MomLogic ();
    void run ();
};
