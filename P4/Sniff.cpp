//
//  Sniff.cpp
//  Programs
//
//  Created by Ehiremen Ekore on 9/30/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include "Sniff.hpp"

Sniff::Sniff(Params& params) : params(params) {
    params.print();
//    firstSearchDirectory = params.getStartingDirectory();
//    chdir(params.getStartingDirectory());
    startingPath = ".";
    currentDirName = ".";
    
    istringstream searchWords(params.getWords());
    
    string tempWord;
    for(;;) {
        searchWords >> tempWord;
        words.push_back(tempWord);
        if( searchWords.eof() ) break;
     }
    
    // remove duplicates from words vector
    words.resize(distance(words.begin(), unique(words.begin(), words.end())));
    
    cerr << "Sniff initialized" << endl;
}

// -----------------------------------------------------------------------------

void Sniff::print( ostream& out ) {
    if (suspiciousFiles.empty()){
        out << "No suspicious files found" << endl << endl;
    }
    
    else {
        out << "Suspicious files:" << endl;
        out << "\tiNode Num" << "\tFile name" << endl;
        for (FileID fID: suspiciousFiles) { fID.print(out); }
        out << endl;
    }
}

// -----------------------------------------------------------------------------

void Sniff::oneDir() {
    if ((dir = opendir(".")) == NULL) {
        cerr << "Unable to open dir\n";
    }
//    if ((dir = opendir(params.getStartingDirectory())) == NULL) {
//        cerr << "Unable to open starting directory \n";
//        return;
//    }
    // change the below to show RELATIVE path, not absolute path
    string cwd = getcwd(NULL, 0);
    cerr << "\ncwd: " << cwd << endl;
    
    
    currentDirEntry = readdir(dir); // discard .
    currentDirEntry = readdir(dir); // discard ..
    
    while ((currentDirEntry = readdir(dir)) != NULL) {
        // discard entry if not regular file or directory
        if ((currentDirEntry->d_type != DT_REG) && (currentDirEntry->d_type != DT_DIR)) {
            continue;
        }
        
        // echo entry's name if verbatim switch is on
        if (params.isVerbatim()) {
            cerr << "\rname: " << currentDirEntry->d_name << endl;
        }
        
        // handle directories
        if (currentDirEntry->d_type == DT_DIR) {
            cerr << "\tSkipped directory: " << currentDirEntry->d_name << endl;
        }
        
        // handle regular file
        else if (currentDirEntry->d_type == DT_REG) {
            FileID tempFile = oneFile();
            if (tempFile.countFoundWords() > 0) {
                suspiciousFiles.push_back(tempFile);
            }
        }
        
        cerr << "\tdone processing " << currentDirEntry->d_name << endl << endl;
    }
    
    closedir(dir);
}

// -----------------------------------------------------------------------------

FileID Sniff::oneFile() {
    FileID currentFile = FileID(currentDirEntry->d_name, currentDirEntry->d_ino, currentDirName);
    
    ifstream thisFile;
    thisFile.open(currentFile.getName());
    
    if (!thisFile) {
        cerr << "\t" << currentFile.getName() << " is empty\n";
    }
    else {
        string currentWord, alphaChars, wordToCheck;
        
        // populate all alpha chars
        for(int k=0; k<26; ++k) { alphaChars += ('a' + k);}
        for(int k=0; k<26; ++k) { alphaChars += ('A' + k);}
        
        // read file till eof
        while(!thisFile.eof()) {
            thisFile >> currentWord;
            size_t endOfString = currentWord.find_last_of(alphaChars);
            wordToCheck = currentWord.substr(0, endOfString+1);
            
            // compare wordToCheck against all words in words vector
            vector<string> tempFoundWords = searchWord(wordToCheck, params.isCaseSensitive());
            for(string s: tempFoundWords) { currentFile.insertFoundWord(s); }
        }
    }
    
    thisFile.close();
    return currentFile;
}

// -----------------------------------------------------------------------------

vector<string> Sniff::searchWord (string word, bool isCaseSensitive) {
    if (word.empty()) return {};
    
    vector<string> out;
    
    if (!isCaseSensitive) { transform(word.begin(), word.end(), word.begin(), ::tolower); }
    
    for (string s: words) {
        string w = s; // make a case sensitive copy of word in vector
        
        // if not case insensitive, also convert each string in vector
        if (!isCaseSensitive) {
            transform(s.begin(), s.end(), s.begin(), ::tolower);
        }
        
        if (word.find(s) != string::npos) {
            // word was found
            out.push_back(w);
        }
    }
    return out;
}

// -----------------------------------------------------------------------------

void Sniff::run(string startingDir) {
    startingPath = ".";
    currentDirName = ".";
    
    cerr << "\n param passed: " << startingDir << endl;
    cerr << "\nbefore, cwd: " << getcwd(NULL, 0) << endl;
    
    chdir(startingDir.c_str());
    
    cerr << "\nafter, cwd: " << getcwd(NULL, 0) << endl;
    
    oneDir();
    print(cout);
    
}

// -----------------------------------------------------------------------------

void Sniff::travel(string path, string nextDir){
    
}
