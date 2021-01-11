//
//  main.cpp
//  P5_v2
//
//  Created by Ehiremen Ekore on 1/6/21.
//  Copyright © 2021 Ehiremen Ekore. All rights reserved.
//

#include "tools.hpp"
#include "Mom.hpp"

int main(int argc, char* argv[]) {
    
    banner();
    emphasisBanner("WELCOME TO MUSICAL THREADS!");
    
    if (argc != 2) {
        fatal("ERROR; must run game with only one extra argument (number--int--of kids!)\n");
    }
   
    Mom mom(argv);
    
    return 0;
}
