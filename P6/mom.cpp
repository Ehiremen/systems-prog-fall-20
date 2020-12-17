//
//  mom.cpp
//  Programs
//
//  Created by Ehiremen Ekore on 12/10/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include <iostream>
#include "momLogic.hpp"

using namespace std;

int main (int argc, char* argv[]) {
    cout << "Mom!" << endl;
    if (argc != 2) {
        cout << "I only want to know how many kids are coming" << endl;
        return -1;
    }
    
    const int N = stoi(argv[1]);
    
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd<0 ) fatalp("Socket: Can't create socket");
    
    sockaddr_in info={0};
    char host[256];
    
    info.sin_family = AF_INET;
    info.sin_port = htons(PORT);
    info.sin_addr.s_addr = INADDR_ANY;
    gethostname(host, 256);
    
    pollfd socks[N];
    
    
    
    
    for (int k=0; k<N; ++k) {
            if (socks[k].fd < 0) continue;
            close( socks[k].fd ) ;
    }
    
    return 0;
}
