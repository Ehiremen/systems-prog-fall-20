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
    
    cerr << "\tWelcome to our sniffer!" << endl << endl;
    
    Params p = Params(argc, argv);
    Sniff sniff = Sniff(p);
    sniff.run(p.getStartingDirectory());
    
    bye();
    return 0;
}

/*
 findit -i --verbose -d ../dir CSCI csci flippin ehis jenn junk random file

 ---------------------------------------------------------------
     Ehis and Jenny
     CSCI 4547
     Fri Oct 30 2020    12:39:31
 ---------------------------------------------------------------
     Welcome to our sniffer!

 Params instance successfully created
 Command: findit -i --verbose -d ../dir CSCI csci flippin ehis jenn junk random file
     Verbose? Yes
     Case insensitive? Yes
     Recursive? No
     Outputting to: Console screen
     Directory? ../dir
     Searching for: ../dir CSCI csci flippin ehis jenn junk random file

 Sniffer instance successfully created

 Param passed: ../dir

 before chdir, cwd: /Users/ehis/UNH/20 Fall/Systems/Programs/P4

 after chdir, cwd: /Users/ehis/UNH/20 Fall/Systems/Programs/dir

 starting sniff...

 dir (dir)
     name: file2.txt
     name: empty.txt (is empty file)
     name: file3.txt
     name: file1.txt
     name: sub1 (dir)
         name: blank.txt
         name: junk.txt
         name: jenny.txt
         name: third.txt (is empty file)
         name: random.txt
     name: linkFile1
     name: myjunk.txt
     name: sub2 (dir)
         name: someFile.txt
         name: sub2-2 (dir)
             name: sub2_2_file.txt
             name: sub3 (dir)
                 name: sub3_file1.txt
                 name: sub3_file2.txt
         name: sub2-1 (dir)
             name: sub2_1_file2.txt
             name: sub2_1_file1.txt

 ============================================================
                         SNIFFER RESULTS
 ============================================================
 found 1 queried word(s) in ./file2.txt
 csci

 found 1 queried word(s) in ./file1.txt
 csci

 found 1 queried word(s) in ./sub1/blank.txt
 file

 found 1 queried word(s) in ./sub1/junk.txt
 junk

 found 2 queried word(s) in ./sub1/jenny.txt
 jenn ehis

 found 1 queried word(s) in ./sub1/random.txt
 random

 found 1 queried word(s) in ./linkFile1
 csci

 found 1 queried word(s) in ./myjunk.txt
 csci

 found 2 queried word(s) in ./sub2/someFile.txt
 random file

 found 1 queried word(s) in ./sub2/sub2-2/sub2_2_file.txt
 file

 found 1 queried word(s) in ./sub2/sub2-2/sub3/sub3_file1.txt
 csci

 found 1 queried word(s) in ./sub2/sub2-2/sub3/sub3_file2.txt
 file

 found 1 queried word(s) in ./sub2/sub2-1/sub2_1_file2.txt
 file

 found 3 queried word(s) in ./sub2/sub2-1/sub2_1_file1.txt
 random flippin file

 ------------------------------------------------------------


 ---------------------------------------------------------------
 Normal termination.
 */
