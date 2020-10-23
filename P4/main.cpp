//
//  main.cpp
//  Programs
//
//  Created by Ehiremen Ekore on 9/30/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include <stdio.h>
#include "Params.hpp"
#include "FileID.hpp"
#include "Sniff.hpp"

using namespace std;

int main (int argc, char* argv[]) {
    banner();
    
    std::cerr << "\tWelcome to our sniffer!" << endl << endl;
    
    Params p = Params(argc, argv);
    Sniff sniff = Sniff(p);
    sniff.run(p.getStartingDirectory());
//    chdir(p.getStartingDirectory());
//    sniff.oneDir();
//    sniff.print(cout);
    
    bye();
    return 0;
}
