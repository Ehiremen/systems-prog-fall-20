//
//  mom.cpp
//  Programs
//
//  Created by Ehiremen Ekore on 12/10/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include "momLogic.hpp"
#define limitN 25
#define _XOPEN_SOURCE_EXTENDED 500

using namespace std;

int doWelcome(int welcomeSock, int* nClip, toPoll* worker,
              const char* greeting);
void printSockInfo(char* who, sockInfo sock);
int doService(toPoll* p){ return -1; }

int main (int argc, char* argv[]) {
    banner();
    
    // validate args
    if (argc != 2) {
        fatal("I only want to know how many kids are coming (<= %d)\n", limitN);
    }
    
    const int numExpected = stoi(argv[1]);
    if (numExpected > limitN) {
        fatal("can't take more than %d kids!\n", limitN);
    }
    
    char* proc = argv[0];
    
    // ============================================
    
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd<0 ) fatalp("Socket: Can't create socket");
    
    char hostName[256];
    gethostname(hostName, 256);          // get name of local host.
    say("server is %s", hostName);
    
    int nCli = 0;                        // number of working sockets still alive
    int welcomeSock;                     // fd for the welcoming socket
    
    toPoll ufds[limitN + 1];         // These are the connections to poll.
    toPoll* const welcome = &ufds[0];    // entry for the welcome socket
    toPoll* const worker = &ufds[1];     // first working socket.
    
    int status;                          // return values from system calls.
    socklen_t sockLen;                   // # bytes in network address struct
    
    sockInfo host;                       // welcome socket
    host.sin_family = AF_INET;           // Address family internet
    host.sin_port = htons(PORT);         // Use a fixed port number
    host.sin_addr.s_addr = INADDR_ANY;   // Accept connections from anybody.
    
    char greeting[256];
    sprintf(greeting, "Connected to (%s.%d)\n", hostName, ntohs(host.sin_port));
    
    // ============================================
    // Create an internet socket in the file table; return the file descriptor.
    // Use INET protocol family, stream i/o, exact protocol irrelevant (== 0)
     
    // ============================================
    
    welcomeSock = socket(AF_INET, SOCK_STREAM, 0);
    if (welcomeSock < 0) fatalp("%s: can't assign fd for socket", argv[0]);
    welcome->fd = welcomeSock;        // record socket fd in polling structure
    welcome->events = POLLIN;        // let socket listen for calls from clients
    
    // TCP connection
    int trueVal = 1;
    status = setsockopt(welcomeSock, SOL_SOCKET, SO_REUSEADDR, &trueVal, sizeof(int));
    if (status < 0) fatalp("Can’t set reuse socket option");
    
    /// ============================================
    
    // Bind the file descriptor to a network address structure.
    sockLen = sizeof(host);
    //    status = bind(welcomeSock, (sockUnion*) &host, sockLen);
    status = ::bind(welcomeSock, (sockUnion*) &host, sockLen);
    
    if (status < 0) fatalp("Can't bind socket (%d)", welcomeSock);
    
    // This block is debugging code ---------------------------------------------
    // ntohs: converts an integer in network representation to the host
    // representation. Takes care of big-endian vs. little-endian incompatibility.
    // Find out what port number actually got assigned to the welcome socket.
    status = getsockname(welcomeSock, (sockUnion*) &host, &sockLen);
    if (status<0) fatal("%s: can't get port# of socket (%d)", proc, welcomeSock);
    printf("Opened socket as fd (%d) on port (%d) for stream i/o\n",
           welcomeSock, ntohs(host.sin_port));
    printSockInfo("welcome", host);
    
    // Mark welcomeSock as a welcome mat that clients can connect to.
    status = ::listen(welcomeSock, limitN);             // have enough room for the max number of players
    if (status < 0) fatalp("%s: Unable to listen on socket.", proc);
    printf("Just called listen(); now waiting for a client to show up\n");
    
    // ============================================
    // -------------------------------------------------------- main welcoming loop
    // Listen simultaneously to welcomeSock for new connections and to all of the
    // working sockets for data. Do not exit; servers operate in an infinite loop.
    //
    for (;;) {
        status = poll(ufds, 1 + nCli, -1);
        //printf("."); fflush(stdout);
        if (status < 0)  fatalp("Error in poll().\t");
        if (status == 0) sayp("%s: poll timed out\t", proc);
        // ============================================
        // If welcome socket has a caller, service it.
        if (welcome->revents != 0 )    {
            if (welcome->revents & POLLIN)    {
                if (nCli < limitN) // create a new client connection.
                    nCli += doWelcome(welcomeSock, &nCli, worker, greeting);
                if (nCli >= limitN || nCli == numExpected) break;
            }
            else fatalp("Error involving welcome mat: %d", welcome->revents);
        }
        
    }    // end welcome loop
    
    // allow reading AND writing on welcome socket
    welcome->events = POLLIN | POLLOUT;
        
    MomLogic momLogic(welcome, worker, numExpected);
    cout << "In mom: debug line\n";
    momLogic.run();
    
    // close all except the welcomeSocket
    for (int k=0; k<numExpected; ++k) {
        if (worker[k].fd < 0) continue;
        close( worker[k].fd ) ;
    }
    close(welcomeSock);
    
    bye();
    return 0;
}

//==============================================================================
// Returns 1 if connection succeeded; 0 if no new worker was created
int doWelcome(int welcomeSock, int* nClip, toPoll* worker,
              const char* greeting) {
    int nCli = *nClip;    // Make a local copy of the in/out parameter
    sockInfo newCaller;
    socklen_t sockLen = sizeof newCaller;
    
    int newfd = accept(welcomeSock, (sockUnion*) &newCaller, &sockLen);
    if (newfd < 0) {
        say("False alarm: packet was rejected.");
        return 0;  // False alarm, nobody there, 0 new clients.
    }
    
    printSockInfo("working--from newCaller", newCaller);  // same as getpeername
    
    // --------------------------- Put new socket into our polling list.
    worker[nCli].fd = newfd;
    worker[nCli].events = POLLIN | POLLOUT;
    worker[nCli].revents = 0;
    
    // ----------------------------- We have a new caller -- send an ack.
    int bytes = write(newfd, greeting, strlen(greeting));
    if (bytes < 1) say("Error while writing to socket");
    
    *nClip = nCli;        // Return the possibly-modified index of last client.
    return 1;
}

//==============================================================================

void printSockInfo(char* who, sockInfo sock) {
    printf("%s socket is  {\n\t"
           "sin_family        = %d\n\t"
           "sin_addr.s_addr   = %s\n\t"
           "sin_port          = %d\n\t"
           "}\n", who, sock.sin_family, inet_ntoa(sock.sin_addr),
           ntohs(sock.sin_port));
}
