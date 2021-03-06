//
//  FileID.hpp
//  Programs
//
//  Created by Ehiremen Ekore on 9/30/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#pragma once

#include "tools.hpp"
#include <vector>

class FileID {
private:
    string fileName;
    int iNodeNumber;
    string pathnameRelToStartDir;
    vector<string> foundSniffWords;
    
public:
    FileID (string fileName, int nodeNumber, string path);
    void print( ostream& out);
    void insertFoundWord (string& word);
    int countFoundWords() { return foundSniffWords.size(); }
    
    // ifstream.open() fails if only fileName is used as name.
    // this is why we are using the name relative to starting directory
    string getName() { return pathnameRelToStartDir; }
};
