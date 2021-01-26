//
//  kid.cpp
//  Programs
//
//  Original code gotten from Alice Fischer lecture code examples
//  Modified by Ehiremen Ekore on 12/10/20.
//

#include <iostream>
#include "kidLogic.hpp"

#define _XOPEN_SOURCE_EXTENDED 500

using namespace std;

void printSockInfo(char* who, sockInfo sock);

int main (int argc, char* argv[]) {
    banner();
    
    // echo command
    cout << "Command: ";
    for (int k=0; k<argc; k++) cout << argv[k] << " ";
    cout << "\n";
    
    if (argc != 3) {
        fatal("expected: %s hostname myName\n", argv[0]);
    }
    
    const string proc = argv[0];    // name of executable
    const string servername = argv[1];    // registered network name of server.
    const string myName = argv[2];  // name of kid
    
    // =========================================================================
    // Install a socket in the client's file table.
    // Make an internet-transmitted, file-i/o-style, protocol-whatever plug
    int clientSock = socket( AF_INET, SOCK_STREAM, 0 );
    if ( clientSock<0 ) fatalp( "%s: can't assign fd for client socket", proc.c_str() );
    
    // =========================================================================
    // Use a domain name server to get the IP address associated with the host.
    // The name server returns a list of IP addresses.  We want the first one.
    hostInfo* remoteHost = gethostbyname( servername.c_str() );
    if (remoteHost == NULL) fatalp("%s: unknown host: %s\n", proc.c_str(), servername.c_str());
    
    // =========================================================================
    // This series of system calls sets up the client's socket structure.
    sockInfo clientInfo;
    clientInfo.sin_family = AF_INET;    // Address family internet
     
    // Copy info about the server into the client's socket structure.
    memmove( &clientInfo.sin_addr, remoteHost->h_addr_list[0], remoteHost->h_length);
    
    // Copy the agreed-upon port number into the client's socket structure.
    // Convert it first from the local representation to the internet standard.
    clientInfo.sin_port = htons( PORT );
    printSockInfo( "client", clientInfo );
    
    // =========================================================================
    // Info in the client struct is now complete and ready to connect to server.
    int status = ::connect( clientSock, (sockUnion*) &clientInfo, sizeof (clientInfo) );
    cout << "Connected on clientSock: " << clientSock << endl;
    if ( status < 0 ) fatalp("%s: Connection to %s refused.\n", proc.c_str(), servername.c_str());
    printf("%s: connection established to %s.\n", proc.c_str(), servername.c_str());
        
    
    // wait for server ot acknowledge message
    char buffer[bufferLen];
    int nBytes = read(clientSock, buffer, bufferLen);
    if (nBytes<0) fatal("%s: Error while reading from socket.", proc.c_str());
    
    
    KidLogic kidLogic(clientSock, myName);
    kidLogic.run();
    close(clientSock);
    
    bye();
    return 0;
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
