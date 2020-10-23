//
//  main.cpp
//  Programs
//
//  Created by Ehiremen Ekore on 9/25/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include <stdio.h>
#include "Params.hpp"

int main (int argc, char* argv[]) {
    banner();
    
    Params p = Params(argc, argv);
    p.print();
    
    bye();
    return 0;
}
