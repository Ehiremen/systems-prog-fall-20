//
//  model.hpp
//  Programs
//
//  Created by Ehiremen Ekore on 1/6/21.
//  Copyright © 2021 Ehiremen Ekore. All rights reserved.
//

#pragma once
#include <pthread.h>
#include "tools.hpp"

using namespace std;

struct Model {
    int numChairs;
    int* chairArray;
    int nMarching = 0;
    pthread_mutex_t mtx     = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t  turn    = PTHREAD_COND_INITIALIZER;
    
    Model (int nChairs) {
        numChairs = nChairs;
        chairArray = new int[numChairs];
        fill_n(chairArray, numChairs, -1);
        printf("Model is ready :)\n");
    }
    
    ~Model () { delete chairArray; }
};
