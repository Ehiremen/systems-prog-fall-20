//
//  kidLogic.cpp
//  Programs
//
//  Created by Ehiremen Ekore on 12/10/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#include "kidLogic.hpp"

KidLogic::KidLogic (int momFd, string name) : momFd(momFd), kidName(name) {
    srand( time (NULL) );
    momIn = fdopen( momFd, "r" );
    momOut = fdopen( momFd, "w" );
    cout << "In " << kidName << ": writing to mom\n";
    
    int status = fprintf(momOut, "%s\n", kidName.c_str());
    fflush(momOut);
    if (status > 0) cout << "In " << kidName << ": mom knows my name!\n\n";
    else fatalp("In %s: error writing name to mom\n", kidName.c_str());
}

// ---------------------------------------------------

void KidLogic::run() {
    cout << "Taking a quick nap\n";
    usleep(rand()%2000);
    cout << "Done sleeping\n";
    do {
        doCommand();
    } while (pcol != KIDQUIT);
}

// ---------------------------------------------------

void KidLogic::doCommand() {
    cout << "\nIn " << kidName << ": reading from mom\n";
    memset(buffer, '\0', sizeof(buffer));
    
    int status = fscanf(momIn, "%6s", buffer);
    command = buffer;
    if (status<1) fatalp("Error reading command");
    
    cout << "In " << kidName << ": done reading from mom\n";
    cout << "State = "<< stateName[pcol] << ", Command is: " << command << endl ;
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
        cout << "In " << kidName << ": Weird things are happening\n";
    }
}

// ---------------------------------------------------

void KidLogic::doGetup () {
    for (int n=0; n<30; n++) cout << "=";
    cout << "\nIn " << kidName << ": got GETUP\n";
    pcol = MARCHING;
    int status = fscanf( momIn, "%d", &nChairs );
    currentChair = -1;
    if (status!=1) fatalp("Error reading num chairs\n");
}

// ---------------------------------------------------

void KidLogic::doSit (bool fromNack, int choiceFromNack){
    pcol = SEEKING;
    if (!fromNack){
        cout << "In " << kidName << ": got SIT\n";
        wantThisChair = rand()%nChairs;
    }
    else wantThisChair = choiceFromNack;
    
    int status = fprintf(momOut, "%s %d\n", commandsStr[WANT].c_str(), wantThisChair);
    fflush(momOut);
    if (status > 0) cout << "In " << kidName << ": asked for seat " << wantThisChair << "\n";
    else fatalp("In %s: error asking mom for chair\n", kidName.c_str());
}

// ---------------------------------------------------

void KidLogic::doAck (){
    cout << "In " << kidName << ": got ACK\n";
    currentChair = wantThisChair;
    cout << "In " << kidName << ": Yay, I got a seat!\n";
    pcol = SITTING;
}

// ---------------------------------------------------

void KidLogic::doNack (){
    cout << "In " << kidName << ": got NACK\n";
    
    // get list of chairs from mom and figure out which is/are free
    memset(buffer, '\0', sizeof(buffer));
    int status = fscanf( momIn, "%s", buffer );
    if (status<1) fatalp("Error reading num chairs\n");
    
    string chairStates = buffer;
    vector<int> freeChairs;
    
    for (int c = 0; c < chairStates.size(); ++c) {
        if (chairStates[c] == '1') freeChairs.push_back(c);
    }
    
    // try to sit in a random chair again
    int wants = freeChairs[rand()%freeChairs.size()];
    doSit(true, wants);
}

// ---------------------------------------------------

void KidLogic::doQuit (){
    cout << kidName << ": I'm out of the game :(\n\n";
    pcol = KIDQUIT;
}

// ---------------------------------------------------

void KidLogic::doPrize (){
    cout << "\n\n" << kidName << ": OMG! No way I won!!!\n\n";
    pcol = KIDQUIT;
}
