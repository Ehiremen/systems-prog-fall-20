//
//  kid.cpp
//  Programs
//
//  Created by Ehiremen Ekore on 12/10/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include <iostream>

using namespace std;

int main (int argc, char* argv[]) {
    cout << "Kid!" << endl;
    
    if (argc != 3) {
        cout << "need more items!" << endl;
        return -1;
    }
    
    const string proc = argv[0];       // name of executable
    const string host = argv[1]; // registered network name of server.
    const string myName = argv[2];     // name of kid
    
    return 0;
}
