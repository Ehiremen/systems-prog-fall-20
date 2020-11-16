//
//  Model.hpp
//  Programs
//
//  Created by Ehiremen Ekore on 11/8/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#pragma once

#include "tools.hpp"

using namespace std;

// using typedef so I don't need to use Model scope later on
typedef struct Model {
    mutex mtx;
    int nChairs;
    int* chairArrayPtr;
    int nMarching;
    pthread_mutex_t turn_mutex  = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t  turn        = PTHREAD_COND_INITIALIZER;
    
    Model (int numChairs) {
        nChairs = numChairs;
        chairArrayPtr = (int*) malloc (numChairs * sizeof(int));
        printf("Model is alive!!!\n");
    }
    
    ~Model () {
        delete chairArrayPtr;
    }
    
} Model;
