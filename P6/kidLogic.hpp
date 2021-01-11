//
//  kidLogic.hpp
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
    
    void doCommand ();
    void doGetup ();
    void doSit ();
    void doAck ();
    void doQuit ();
    void doPrize ();
    void doNack ();
    
public:
    KidLogic (int fd, string name);
    ~KidLogic ();
    void run ();
};
