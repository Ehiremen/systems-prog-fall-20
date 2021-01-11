//
//  kidLogic.cpp
//  Programs
//
//  Created by Ehiremen Ekore on 12/10/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include "kidLogic.hpp"

void KidLogic::run() {
    do {
        doCommand();
    } while (pcol != KIDQUIT);
}

void KidLogic::doCommand() {
    int status = fscanf( momIn, "%6s", command );
    if (status!=1) fatalp("Error reading command");
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
}

void KidLogic::doGetup () {
    
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
