//
//  kidLogic.hpp
//  Programs
//
//  Created by Ehiremen Ekore on 12/10/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//


#pragma once
#include <vector>
#include "protocol.hpp"
#include "socktypes.h"
#include "tools.hpp"

using namespace std;

const int bufferLen = 100;

enum StateT { NEWBIE, MARCHING, SEEKING, SITTING, KIDQUIT };
const string stateName[] = {
    "NEWBIE", "MARCHING", "SEEKING", "SITTING", "KIDQUIT"
};

class KidLogic {
private:
    int momFd;
    FILE* momIn, * momOut;
    int nChairs;
    string kidName;
    char* command;
    StateT pcol = NEWBIE;
    int currentChair = -1, wantThisChair = 0;
    
    // variables for handling socket i/o
    char buffer[bufferLen];
    int nBytes = 0;

    
    void doCommand ();
    void doGetup ();
    void doSit (bool fromNack = false, int choiceFromNack = 0);
    void doAck ();
    void doQuit ();
    void doPrize ();
    void doNack ();
    
public:
    KidLogic (int momFd, string name);
    ~KidLogic () = default;
    void run ();
    string getName() { return kidName; }
};
