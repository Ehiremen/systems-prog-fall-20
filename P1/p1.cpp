//
//  p1.cpp
//  P1
//
//  Created by Ehiremen Ekore on 9/8/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char * argv[]) {
    ofstream myOut("P1_Ekore.txt", ios::out | ios::app);
    
    // print a line of dashes
    myOut << setw(60) << setfill('-') << "-" << endl;
    cout << setw(60) << setfill('-') << "-" << endl;
    
    // do argv[0]
    myOut << setw(10) << setfill(' ') << left << "command";
    myOut << argv[0] << endl;
    cout << setw(10) << setfill(' ') << left << "command";
    cout << argv[0] << endl;
    
    // handle the other args
    for (int k=1; k<argc; ++k) {
        string argType;
        string argToPrint = argv[k];
        
        // check first char of argv[k] to know if argv[k] is switch or not
        // if it's a switch, remove the leading '-'
        if (argv[k][0] == '-') {
            argType = "switch";
            argToPrint = argToPrint.substr(1);
        }
        else argType = "argument";
        
        myOut << setw(10) << setfill(' ') << left << argType;
        myOut << argToPrint << endl;
        cout << setw(10) << setfill(' ') << left << argType;
        cout << argToPrint << endl;
    }
    
    return 0;
}

/*
 Comments on output:
 
 For test e:
*   mytemp.txt was created because of the "> mytemp.txt" when executing P1 from
    the command line.
*   mytemp.txt comes out empty because there's no html file in the program's
    directory. Personally, I wonder why the system didn't treat the "*.html" as
    an empty arg when it realized there were no html files.
*   after further testing, it seems like it's because I don't have any html file
    in my directory. I tried taking out different switches from e, and I
    narrowed it down to the "*.html". Also, things worked out when I put a
    .html file into my directory
 
 For test f:
*   both bak files in my directory show up in my .txt file.
*   Interestingly, there isn't any log file, but test f doesn't return empty
    (whereas test e was empty for a similar reason).
 */
