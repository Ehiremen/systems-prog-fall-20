//
//  protocol.hpp
//  Programs
//
//  Created by Ehiremen Ekore on 12/10/20.
//  Copyright © 2020 Ehiremen Ekore. All rights reserved.
//

#pragma once
#include <iostream>

using namespace std;

const int PORT = 1234;

enum commands {
    HELLO,
    GETUP,
    SIT,
    WANT,
    ACK,
    NACK,
    QUIT,
    PRIZE
};

const string commandsStr[] = {
    "HELLO",
    "GETUP",
    "SIT",
    "WANT",
    "ACK",
    "NACK",
    "QUIT",
    "PRIZE"
};
/*
* HELLO: From kid to mom as soon as the connection is made. A HELLO message is a string of the form "HELLO bobby", where bobby is the kid’s name.
* GETUP: From mom to kid at beginning of each round. A GETUP message is a string of the form "GETUP 8", where 8 is the current number of chairs.
* SIT: From mom to kid when she turns off the music. Example: SIT
* WANT: From kid to mom when kid gets the SIT message. A WANT message is a string of
the form "WANT 3", where 3 is the chosen chair number.
* ACK: Your choice is approved – sit in it. Example: ACK
* NACK: Bad choice – somebody else already took that chair. A NACK message is a string such as "NACK 01001101", which says that chairs 1, 4, 5, and 7 are still available.
* QUIT: You lost; time to quit. (From mom to the chairless kid when there are no chairs left.) Example: QUIT
* PRIZE: mom sends the surviving kid a message about winning. Example: PRIZE
*/
