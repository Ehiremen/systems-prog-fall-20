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
    
    vector<string> searchWord (string word, bool isCaseSensitive);
    
public:
    Sniff(Params& params);
    FileID oneFile(struct dirent *currentDirEntry);
    void run(string startingDir);
    void travel(string path, string nextDir, int depth);
        // passing depth to Sniff::travel to help with formatting verbose output as a tree
    void print( ostream& out );

};

/*
 * Took out Sniff::oneDir... that logic now exists in Sniff::travel
 * No longer keeping DIR *dir and struct dirent currentDirEntry as
    global variables... Instead, both are now local to Sniff::travel
    and Sniff::oneFile now takes currentDirEntry as a parameter
 */
