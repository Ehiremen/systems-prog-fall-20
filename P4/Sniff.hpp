//
//  Sniff.hpp
//  Programs
//
//  Created by Ehiremen Ekore on 9/30/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#pragma once

#include "Params.hpp"
#include "FileID.hpp"
#include "tools.hpp"
#include <dirent.h>
#include <algorithm>    // for std::unique
#include <sys/stat.h>   // for testing entry types

class Sniff {
private:
    Params params;
    string startingPath;
    string currentDirName;
    vector<string> words;
    vector<FileID> suspiciousFiles;
    string alphaChars;
    const string tab = "    "; // explicitly setting my tabs to 4 spaces
    ostream& myOutStream;
    
//    DIR *dir;
//    struct dirent *currentDirEntry;
    
    vector<string> searchWord (string word, bool isCaseSensitive);
    /*
    struct dirent {
        ino_t      d_ino; // file or I-node number
        __uint16_t d_reclen; // length of this record
        __uint8_t  d_type; // file type, see below
        __uint8_t  d_namlen; // strlen( d_name )
        char       d_name[255 + 1]; // name must be<= 255
    };
     */
    
public:
    Sniff(Params& params);
    void oneDir();
    FileID oneFile(struct dirent *currentDirEntry);
    void run(string startingDir);
    void travel(string path, string nextDir, int depth);
    void print( ostream& out );

};
