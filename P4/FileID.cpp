//
//  FileID.cpp
//  Programs
//
//  Created by Ehiremen Ekore on 9/30/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include "FileID.hpp"

FileID::FileID (string name, int nodeNumber, string path) {
    fileName = name;
    pathnameRelToStartDir = path + "/" + name;
    iNodeNumber = nodeNumber;
    
    cerr << "\tNew FileID created" << endl;
}

// -----------------------------------------------------------------------------

void FileID::print( ostream& out) {
    out << "\t" << iNodeNumber << "\t" << pathnameRelToStartDir << endl;
}

// -----------------------------------------------------------------------------

void FileID::insertFoundWord (string& word) {
    // check if word isn't already in vector
    // add word to vector if it isn't there already
    if (find(foundSniffWords.begin(), foundSniffWords.end(), word) == foundSniffWords.end()) {
        foundSniffWords.push_back(word);
    }
}
