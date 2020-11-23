//
//  Mom.hpp
//  Programs
//
//  Created by Ehiremen Ekore on 11/20/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#pragma once
#include "tools.hpp"
#include "Model.hpp"
#include "Kid.hpp"
#include <signal.h>

using namespace std;

void* startThread (void* kid);

class Mom {
private:
    const int numKids;
    Kid** kids; // array of pointers to Kid objects for each player.
    Model m;
    
    void playOneRound();
    void removeLoser();
    void getKidsBack();
    
public:
    Mom( char* argv[] );
    ~Mom();
    void doGame();
};
