//
//  Params.hpp
//  Programs
//
//  Created by Ehiremen Ekore on 9/30/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#pragma once

#include "tools.hpp"
#include <getopt.h>

using namespace std;

const char* const short_opts = ":d:iRo::"; // ':' means the preceeding arg needs
                                          // a required argument
    // ':' at the beginning of short_ops so compiler can distinguish '?' from ':'

static struct option long_opts[] = {
    {"dir", required_argument, NULL, 'd'},
    {"verbose", no_argument, NULL, 0},
    {NULL, 0, NULL, 0}
};

class Params {
private:
    ofstream myOutFile;
    string outFileName;
    string searchWords;
    char* startingDirectory;
    
    //switches
    bool switchDir = false;
    bool switchI = false;
    bool switchR = false;
    bool switchO = false;
    bool switchVerbose = false;
    
    string argsCopy;
    string printBool(bool b) { return (b ? "Yes" : "No"); }
    
public:
    Params(int argc, char* argv[]);
    Params(const Params& p2);
    void print();
    char* getStartingDirectory() {return startingDirectory; }
    string getWords() { return searchWords; }
    bool isVerbatim() { return switchVerbose; }
    bool isCaseSensitive() { return !switchI; }
    ostream& getOutputStream() { return switchO ? myOutFile : cout; }
};
