//
//  kidLogic.cpp
//  Programs
//
//  Created by Ehiremen Ekore on 12/10/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include "kidLogic.hpp"

KidLogic::KidLogic (int momFd, string name) : momFd(momFd), kidName(name) {
//    momIn = fdopen( momFd, "r" );
//    momOut = fdopen( momFd, "w" );
    mom = fdopen(momFd, "r+");
    cout << "writing to mom\n";
    
//    * weird that fprintf() doesn't write to mom's stream, but write() does...
//    fprintf(momOut, "%s", kidName.c_str());
    cout << "MomFD = " << momFd << endl;
    nBytes = write( momFd, kidName.c_str(), kidName.size() );
    cout << "mom knows my name!\n\n";
}

// ---------------------------------------------------

void KidLogic::run() {
    fprintf(mom, "In Kid, printing to mom\n");
    sleep(3);
    cout << "Done sleeping \n";
//    do {
        doCommand();
//    } while (pcol != KIDQUIT);
}

// ---------------------------------------------------

void KidLogic::doCommand() {
//    if(recv(momFd, buffer, bufferLen, MSG_PEEK) == 0) return;
    cout << "In " << kidName << " reading from mom\n";
//    bzero(buffer, bufferLen);
    nBytes = read(momFd, buffer, sizeof(buffer));
    
//    fscanf(momOut, "%s", buffer);
    
//    int status = fscanf(momIn, "%6s", buffer);
//    fscanf(momIn, "%6s", buffer);
//    scanf("%6s", buffer);
    command = buffer;
    
    cout << "In " << kidName << " done reading from mom\n\n";
//    if (status!=1) fatalp("Error reading command");
    cout << "State = "<< stateName[pcol] << ", Command is: " <<command << endl ;
    try{
        if (strcmp( "GETUP", command) == 0) doGetup();
        else if (strcmp( "SIT", command) == 0) doSit();
        else if (strcmp( "NACK", command) == 0) doNack();
        else if (strcmp( "ACK", command) == 0) doAck();
        else if (strcmp( "QUIT", command) == 0) doQuit();
        else if (strcmp( "PRIZE", command) == 0) doPrize();
        else throw( "Protocol is mixed up." );
    }
    catch (string& s) {
        cout << s <<" ["<< command <<"]\n";
        exit(1); }
    catch (...) {
        cout << "weird shit is happening\n";
    }
}

// ---------------------------------------------------

void KidLogic::doGetup () {
    cout << "standing up\n"; return;
    
    int status = fscanf( mom, "%d", &nChairs );
    currentChair = -1;
    if (status!=1) fatalp("Error reading command");
}

void KidLogic::doSit (){
    
}

void KidLogic::doAck (){
    
}

void KidLogic::doQuit (){
    cout << kidName << ": I'm out of the game :(" << endl;
    pcol = KIDQUIT;
}

void KidLogic::doPrize (){
    cout << kidName << ": OMG! No way I won!!!" << endl;
    pcol = KIDQUIT;
}

void KidLogic::doNack (){
    
}
