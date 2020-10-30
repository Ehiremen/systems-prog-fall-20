//
//  FileID.cpp
//  Programs
//
//  Created by Ehiremen Ekore on 9/30/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include "FileID.hpp"

FileID::FileID (string fileName, int nodeNumber, string path) {
    this->fileName = fileName;
    pathnameRelToStartDir = path + "/" + fileName;
    iNodeNumber = nodeNumber;
    
//    cerr << "\tNew FileID created for: " << pathnameRelToStartDir << endl;
}

// -----------------------------------------------------------------------

void FileID::print( ostream& out) {
//    out << "\t" << iNodeNumber << "\t" << pathnameRelToStartDir << endl;
    out << endl << "found " << foundSniffWords.size() << " queried word(s) in ";
    out <<pathnameRelToStartDir << endl;
    
    for (string word: foundSniffWords) out << word << " ";
    out << endl;
}

// -----------------------------------------------------------------------

void FileID::insertFoundWord (string& word) {
    // check if word isn't already in vector
    // add word to vector if it isn't there already
    if (find(foundSniffWords.begin(), foundSniffWords.end(), word) == foundSniffWords.end()) {
        foundSniffWords.push_back(word);
    }
}
