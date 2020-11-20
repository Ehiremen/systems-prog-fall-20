//
//  main.cpp
//  Programs
//
//  Created by Ehiremen Ekore on 10/30/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include "tools.hpp"
#include "Mom.hpp"

using namespace std;

void* startThread (void* kid) {
    Kid* k = (Kid*) kid;
    k->play();
    return NULL;
}

// -----------------------------------------------------------------------

int main (int argc, char* argv[]) {
    banner();
    cerr << "\tWelcome to musical chairs!\n\n";
    
    if (argc != 2) {
        fatal("ERROR; must run game with only one extra argument (number--int--of kids!)\n");
    }
   
    Mom mom(argv);
    mom.doGame();
    
    bye();
    exit( 0 );
}
