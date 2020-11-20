//
//  Kid.hpp
//  Programs
//
//  Created by Ehiremen Ekore on 11/8/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#pragma once

#include "tools.hpp"
#include "Model.hpp"
#include <signal.h>

class Kid {
private:
    Model* sharedModel;
    int kidID;
    pthread_t tid;
    sigset_t sigSet;
    int wantSeat, seatNumber;
    ostringstream ss;
    string whereAmI = "In kid #";
    
    struct sigaction sigControl;
    void sigHandler (int sig);
    const char* sigName (int sig);
    
public:
    Kid(Model* model, int ID);
    ~Kid();
    void play();
    int getID() { return kidID; }
    pthread_t getTid() { return tid; }
    bool isStanding() { return (seatNumber == -1); }
    void standUp() { seatNumber = -1; printf("%s standing up!\n", whereAmI.c_str()); }
    void doMarch();
    void doSit();
    int getSeatNumber() { return seatNumber; }
};
