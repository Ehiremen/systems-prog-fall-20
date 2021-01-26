//
//  Mom.hpp
//  P5_v2
//
//  Created by Ehiremen Ekore on 1/10/21.
//  Copyright © 2021 Ehiremen Ekore. All rights reserved.
//

#pragma once
#include <signal.h>
#include "model.hpp"
#include "Kid.hpp"
#include "tools.hpp"

using namespace std;

void* startThread (void* kid);
const char* sigName (int sig);
void emphasisBanner(string str);    //creates a dashed-box around the
                                    // passed string

class Mom {
private:
    const int numKids;
    int kidsStillPlaying;
    Kid** kids;
    Model* model;

    void doGame();
    void playOneRound(Model* m, Kid* players[]);
    void startMusic(Model* m, Kid* players[]);
    void stopMusic(Model* m, Kid* players[]);
    void removeLoser();
    void getKidsBack();
    void sayWinner();
    
public:
    Mom (char* argv[]);
    ~Mom();
};
