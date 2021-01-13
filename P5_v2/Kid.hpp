//
//  Kid.hpp
//  P5_v2
//
//  Created by Ehiremen Ekore on 1/10/21.
//  Copyright © 2021 Ehiremen Ekore. All rights reserved.
//

#pragma once

#include<signal.h>
#include <pthread.h>
#include "tools.hpp"
#include "model.hpp"

using namespace std;

class Kid {
private:
    Model* sharedModel;
    int kidID;
    pthread_t tid;
    sigset_t sigSet;
    int wantSeat, seatNumber;
    ostringstream ss;
    string whereAmI;
    
    void sigHandler( int sig );
    void clearSS() { ss.str(string()); }
    
public:
    Kid(Model* model, int ID);
    ~Kid();
    void play();
    void doMarch();
    void doSit();
    
    int getID() { return kidID; }
    pthread_t getTid() { return tid; }
    bool isStanding() { return (seatNumber == -1); }
    void standUp() { seatNumber = -1; printf("%s standing up!\n", whereAmI.c_str()); }
    int getSeatNumber() { return seatNumber; }  // didn't use, ended up using isStanding() where relevant
};
