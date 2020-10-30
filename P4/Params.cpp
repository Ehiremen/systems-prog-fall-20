//
//  Params.cpp
//  Programs
//
//  Created by Ehiremen Ekore on 9/30/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include "Params.hpp"

Params:: Params(int argc, char* argv[]) {
    int currentArg = 0, optIndex;
    
    for (; ; ) {
        int opt = getopt_long(argc, argv, short_opts, long_opts, &optIndex);
        
        if (opt == -1) break;
        
        currentArg++;
        
        switch (opt) {
            case 'd':
                switchDir = true;
                startingDirectory = optarg;
                currentArg++;
                break;
                
            case 'i':
                switchI = true;
                break;
                
            case 'R':
                switchR = true;
                break;
                
            case 'o':
                
                if (optarg != NULL){
                    myOutFile.open(optarg, ios::out | ios::app);
                    outFileName = optarg;
                    switchO = true;
                }
                currentArg++;
                break;
                
            case '?':
                fatal("Unidentified option specified\n");
                break;
                
            case ':':
                fatal("Missing required argument\n");
                break;
                
            case 0:
                if (string(long_opts[optIndex].name).compare("verbose") == 0){
                    switchVerbose = true;
                }
                
                else {
                    fatal("Unrecognized long option specified\n");
                }
                
                break;
                
            default:
                break;
        }
    }
    
    if (!switchDir) {
        fatal("Starting directory not specified!\n");
    }
    
    // store all words after the last argument as searchWords
    for (; currentArg < argc; ++currentArg) {
        searchWords += string(argv[currentArg]);
        searchWords += " ";
    }
    
    // copy entire command
    for (int n=0; n<argc; n++) {
        argsCopy += string(argv[n]) + " ";
    }
    
    cerr << "Params instance successfully created" << endl;
}

// -----------------------------------------------------------------------

void Params:: print() {
    ostream& out = getOutputStream();
    
    out << "Command: " << argsCopy << endl;
    out << "\tVerbose? " << printBool(switchVerbose) << endl;
    out << "\tCase insensitive? " << printBool(switchI) << endl;
    out << "\tRecursive? " << printBool(switchR) << endl;
    
    if (switchO){
        out << "\tOutput file name: " << outFileName << endl;
    }
    else {
        out << "\tOutputting to: Console screen" << endl;
    }
    
    out << "\tDirectory? " << startingDirectory << endl;
    
    if (!searchWords.empty()) out << "\tSearching for: " << searchWords << endl;
    
    out << endl;
}

// -----------------------------------------------------------------------

Params::Params(const Params& param2){
    outFileName = param2.outFileName;
    searchWords = param2.searchWords;
    startingDirectory = param2.startingDirectory;
    
    //switches
    switchDir = param2.switchDir;
    switchI = param2.switchI;
    switchR = param2.switchR;
    switchO = param2.switchO;
    switchVerbose = param2.switchVerbose;
    
    if (switchO) { // if an outfile was specified
        myOutFile.open(outFileName, ios::out | ios::app);
    }
    
    argsCopy = param2.argsCopy;
}
