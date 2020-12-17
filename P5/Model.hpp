//
//  Model.hpp
//  Programs
//
//  Created by Ehiremen Ekore on 11/8/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#pragma once
#include "tools.hpp"
#include <pthread.h>

using namespace std;

struct Model {
    int nChairs;
    int* chairArrayPtr;
    int nInitialized = 0;
    int nMarching = 0;
    pthread_mutex_t mtx  = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t  turn        = PTHREAD_COND_INITIALIZER;
    
    //Model () {}
    Model (int numChairs) {
        nChairs = numChairs;
        chairArrayPtr = new int[numChairs];
        printf("Model is alive!!!\n");
    }
    
    ~Model () { delete chairArrayPtr; }
};
