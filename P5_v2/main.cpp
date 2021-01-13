//
//  main.cpp
//  P5_v2
//
//  Created by Ehiremen Ekore on 1/6/21.
//  Copyright © 2021 Ehiremen Ekore. All rights reserved.
//

/*
 Please note: For some reason, after compiling, the program may randomly terminate
 when executed. I can't tell why this happens. In any case, simply re-run
 (no need to re-compile) until it executes.
 
 Thank you.
 */

#include "tools.hpp"
#include "Mom.hpp"

int main(int argc, char* argv[]) {
    
    banner();
    emphasisBanner("WELCOME TO MUSICAL THREADS!");
    
    if (argc != 2) {
        fatal("ERROR; must run game with only one extra argument (number--int--of kids!)\n");
    }
   
    Mom mom(argv);
    
    return 0;
}

// 2 SAMPLE RUNS...

/*
[ehis] lexy:~/<2>Systems/Programs/p5_v2~> musical-threads 3

---------------------------------------------------------------
    Ehis and Jenny
    CSCI 4547
    Tue Jan 12 2021    16:04:26
---------------------------------------------------------------

     -------------------------------------------
    |                                           |
    |        WELCOME TO MUSICAL THREADS!        |
    |                                           |
     -------------------------------------------

Model is ready :)
In kid #0:  Created kid #0
In kid #1:  Created kid #1
In kid #2:  Created kid #2
In Mom: Game created for 3 kids!

---------------------------------------------

In kid #0:  standing up!
In kid #1:  standing up!
In kid #2:  standing up!
In kid #1:  received Sig: SIGUSR1
In kid #1:  I'm marching!
In kid #0:  received Sig: SIGUSR1
In kid #0:  I'm marching!
In kid #2:  received Sig: SIGUSR1
In kid #2:  I'm marching!

In Mom: Everyone is marching now

In kid #0:  received Sig: SIGUSR2
In kid #2:  received Sig: SIGUSR2
In kid #1:  received Sig: SIGUSR2
    In kid #1:  Going for a chair
        In kid #1:  Got chair #1
    In kid #1:  Done trying to sit
    In kid #2:  Going for a chair
        In kid #2:  Got chair #0
    In kid #2:  Done trying to sit
    In kid #0:  Going for a chair
    In kid #0:  Going for a chair
    In kid #0:  Done trying to sit

In Mom: All seats are taken!

In Mom: this round's loser is kid#0

---------------------------------------------

In kid #0:  received Sig: SIGQUIT
In kid #0:  End of the road for me
In kid #2:  standing up!
In kid #1:  standing up!
In kid #2:  received Sig: SIGUSR1
In kid #2:  I'm marching!
In kid #1:  received Sig: SIGUSR1
In kid #1:  I'm marching!

In Mom: Everyone is marching now

In kid #2:  received Sig: SIGUSR2
In kid #1:  received Sig: SIGUSR2
    In kid #2:  Going for a chair
        In kid #2:  Got chair #0
    In kid #2:  Done trying to sit
    In kid #1:  Going for a chair
    In kid #1:  Done trying to sit

In Mom: All seats are taken!

In Mom: this round's loser is kid#1

     -------------------------------------
    |                                     |
    |        Kid #2 wins the game!        |
    |                                     |
     -------------------------------------

In kid #2:  received Sig: SIGQUIT
In kid #1:  received Sig: SIGQUIT
In kid #1:  End of the road for me
In kid #2:  End of the road for me
In Mom: Getting kids back
In Mom: Welcome home kid #2
In Mom: Welcome home kid #1
In Mom: Welcome home kid #0
Kid #2 is no more
Kid #1 is no more
Kid #0 is no more

Party's over, kids!
 
*/

// ==================================================================

/*
 [ehis] lexy:~/<2>Systems/Programs/p5_v2~> musical-threads 10

 ---------------------------------------------------------------
     Ehis and Jenny
     CSCI 4547
     Wed Jan 13 2021    15:25:43
 ---------------------------------------------------------------

      -------------------------------------------
     |                                           |
     |        WELCOME TO MUSICAL THREADS!        |
     |                                           |
      -------------------------------------------

 Model is ready :)
 In kid #0:  Created kid #0
 In kid #1:  Created kid #1
 In kid #2:  Created kid #2
 In kid #3:  Created kid #3
 In kid #4:  Created kid #4
 In kid #5:  Created kid #5
 In kid #6:  Created kid #6
 In kid #7:  Created kid #7
 In kid #8:  Created kid #8
 In kid #9:  Created kid #9
 In Mom: Game created for 10 kids!

 ---------------------------------------------

 In kid #0:  standing up!
 In kid #1:  standing up!
 In kid #2:  standing up!
 In kid #3:  standing up!
 In kid #4:  standing up!
 In kid #5:  standing up!
 In kid #6:  standing up!
 In kid #7:  standing up!
 In kid #8:  standing up!
 In kid #0:  received Sig: SIGUSR1
 In kid #3:  received Sig: SIGUSR1
 In kid #6:  received Sig: SIGUSR1
 In kid #6:  I'm marching!
 In kid #9:  standing up!
 In kid #4:  received Sig: SIGUSR1
 In kid #4:  I'm marching!
 In kid #0:  I'm marching!
 In kid #7:  received Sig: SIGUSR1
 In kid #7:  I'm marching!
 In kid #3:  I'm marching!
 In kid #1:  received Sig: SIGUSR1
 In kid #1:  I'm marching!
 In kid #9:  received Sig: SIGUSR1
 In kid #9:  I'm marching!
 In kid #2:  received Sig: SIGUSR1
 In kid #2:  I'm marching!
 In kid #5:  received Sig: SIGUSR1
 In kid #5:  I'm marching!
 In kid #8:  received Sig: SIGUSR1
 In kid #8:  I'm marching!

 In Mom: Everyone is marching now

 In kid #0:  received Sig: SIGUSR2
 In kid #6:  received Sig: SIGUSR2
 In kid #1:  received Sig: SIGUSR2
 In kid #3:  received Sig: SIGUSR2
 In kid #4:  received Sig: SIGUSR2
 In kid #5:  received Sig: SIGUSR2
 In kid #7:  received Sig: SIGUSR2
 In kid #8:  received Sig: SIGUSR2
 In kid #9:  received Sig: SIGUSR2
 In kid #2:  received Sig: SIGUSR2
     In kid #0:  Going for a chair
         In kid #0:  Got chair #1
     In kid #0:  Done trying to sit
     In kid #4:  Going for a chair
         In kid #4:  Got chair #3
     In kid #4:  Done trying to sit
     In kid #9:  Going for a chair
         In kid #9:  Got chair #4
     In kid #9:  Done trying to sit
     In kid #1:  Going for a chair
         In kid #1:  Got chair #7
     In kid #1:  Done trying to sit
     In kid #3:  Going for a chair
     In kid #3:  Going for a chair
         In kid #3:  Got chair #8
     In kid #3:  Done trying to sit
     In kid #8:  Going for a chair
     In kid #8:  Going for a chair
         In kid #8:  Got chair #2
     In kid #8:  Done trying to sit
     In kid #7:  Going for a chair
     In kid #5:  Going for a chair
     In kid #2:  Going for a chair
     In kid #2:  Going for a chair
     In kid #6:  Going for a chair
         In kid #2:  Got chair #5
     In kid #6:  Going for a chair
     In kid #6:  Going for a chair
     In kid #6:  Going for a chair
     In kid #5:  Going for a chair
     In kid #5:  Going for a chair
     In kid #2:  Done trying to sit
         In kid #6:  Got chair #6
     In kid #6:  Done trying to sit
         In kid #5:  Got chair #0
     In kid #7:  Going for a chair
     In kid #7:  Going for a chair
     In kid #7:  Going for a chair
     In kid #7:  Going for a chair
     In kid #5:  Done trying to sit
     In kid #7:  Going for a chair
     In kid #7:  Going for a chair
     In kid #7:  Going for a chair
     In kid #7:  Going for a chair
     In kid #7:  Done trying to sit

 In Mom: All seats are taken!

 In Mom: this round's loser is kid#7

 ---------------------------------------------

 In kid #0:  standing up!
 In kid #1:  standing up!
 In kid #2:  standing up!
 In kid #0:  received Sig: SIGUSR1
 In kid #2:  received Sig: SIGUSR1
 In kid #2:  I'm marching!
 In kid #1:  received Sig: SIGUSR1
 In kid #1:  I'm marching!
 In kid #3:  standing up!
 In kid #7:  received Sig: SIGQUIT
 In kid #3:  received Sig: SIGUSR1
 In kid #3:  I'm marching!
 In kid #4:  standing up!
 In kid #5:  standing up!
 In kid #0:  I'm marching!
 In kid #7:  End of the road for me
 In kid #4:  received Sig: SIGUSR1
 In kid #4:  I'm marching!
 In kid #5:  received Sig: SIGUSR1
 In kid #5:  I'm marching!
 In kid #6:  standing up!
 In kid #9:  standing up!
 In kid #8:  standing up!
 In kid #6:  received Sig: SIGUSR1
 In kid #6:  I'm marching!
 In kid #9:  received Sig: SIGUSR1
 In kid #9:  I'm marching!
 In kid #8:  received Sig: SIGUSR1
 In kid #8:  I'm marching!

 In Mom: Everyone is marching now

 In kid #0:  received Sig: SIGUSR2
 In kid #2:  received Sig: SIGUSR2
 In kid #1:  received Sig: SIGUSR2
 In kid #3:  received Sig: SIGUSR2
 In kid #4:  received Sig: SIGUSR2
 In kid #5:  received Sig: SIGUSR2
 In kid #6:  received Sig: SIGUSR2
 In kid #8:  received Sig: SIGUSR2
 In kid #9:  received Sig: SIGUSR2
     In kid #9:  Going for a chair
         In kid #9:  Got chair #6
     In kid #9:  Done trying to sit
     In kid #2:  Going for a chair
         In kid #2:  Got chair #4
     In kid #2:  Done trying to sit
     In kid #0:  Going for a chair
     In kid #1:  Going for a chair
     In kid #4:  Going for a chair
     In kid #4:  Going for a chair
     In kid #1:  Going for a chair
         In kid #0:  Got chair #3
     In kid #0:  Done trying to sit
         In kid #1:  Got chair #5
     In kid #1:  Done trying to sit
         In kid #4:  Got chair #7
     In kid #3:  Going for a chair
     In kid #3:  Going for a chair
     In kid #3:  Going for a chair
     In kid #4:  Done trying to sit
     In kid #3:  Going for a chair
     In kid #8:  Going for a chair
         In kid #3:  Got chair #0
     In kid #8:  Going for a chair
     In kid #8:  Going for a chair
     In kid #8:  Going for a chair
     In kid #3:  Done trying to sit
         In kid #8:  Got chair #1
     In kid #8:  Done trying to sit
     In kid #6:  Going for a chair
     In kid #6:  Going for a chair
     In kid #5:  Going for a chair
         In kid #6:  Got chair #2
     In kid #6:  Done trying to sit
     In kid #5:  Going for a chair
     In kid #5:  Going for a chair
     In kid #5:  Going for a chair
     In kid #5:  Going for a chair
     In kid #5:  Going for a chair
     In kid #5:  Going for a chair
     In kid #5:  Going for a chair
     In kid #5:  Done trying to sit

 In Mom: All seats are taken!

 In Mom: this round's loser is kid#5

 ---------------------------------------------

 In kid #0:  standing up!
 In kid #1:  standing up!
 In kid #5:  received Sig: SIGQUIT
 In kid #5:  End of the road for me
 In kid #2:  standing up!
 In kid #3:  standing up!
 In kid #4:  standing up!
 In kid #0:  received Sig: SIGUSR1
 In kid #0:  I'm marching!
 In kid #2:  received Sig: SIGUSR1
 In kid #2:  I'm marching!
 In kid #4:  received Sig: SIGUSR1
 In kid #4:  I'm marching!
 In kid #3:  received Sig: SIGUSR1
 In kid #3:  I'm marching!
 In kid #8:  standing up!
 In kid #6:  standing up!
 In kid #9:  standing up!
 In kid #1:  received Sig: SIGUSR1
 In kid #1:  I'm marching!
 In kid #8:  received Sig: SIGUSR1
 In kid #8:  I'm marching!
 In kid #6:  received Sig: SIGUSR1
 In kid #6:  I'm marching!
 In kid #9:  received Sig: SIGUSR1
 In kid #9:  I'm marching!

 In Mom: Everyone is marching now

 In kid #0:  received Sig: SIGUSR2
 In kid #3:  received Sig: SIGUSR2
 In kid #9:  received Sig: SIGUSR2
 In kid #2:  received Sig: SIGUSR2
 In kid #8:  received Sig: SIGUSR2
 In kid #6:  received Sig: SIGUSR2
 In kid #4:  received Sig: SIGUSR2
 In kid #1:  received Sig: SIGUSR2
     In kid #8:  Going for a chair
         In kid #8:  Got chair #4
     In kid #2:  Going for a chair
     In kid #8:  Done trying to sit
     In kid #9:  Going for a chair
         In kid #9:  Got chair #3
     In kid #9:  Done trying to sit
         In kid #2:  Got chair #6
     In kid #2:  Done trying to sit
     In kid #1:  Going for a chair
     In kid #1:  Going for a chair
         In kid #1:  Got chair #0
     In kid #1:  Done trying to sit
     In kid #3:  Going for a chair
         In kid #3:  Got chair #5
     In kid #3:  Done trying to sit
     In kid #4:  Going for a chair
         In kid #4:  Got chair #1
     In kid #4:  Done trying to sit
     In kid #6:  Going for a chair
     In kid #6:  Going for a chair
     In kid #6:  Going for a chair
     In kid #6:  Going for a chair
     In kid #6:  Going for a chair
         In kid #6:  Got chair #2
     In kid #6:  Done trying to sit
     In kid #0:  Going for a chair
     In kid #0:  Going for a chair
     In kid #0:  Going for a chair
     In kid #0:  Going for a chair
     In kid #0:  Going for a chair
     In kid #0:  Going for a chair
     In kid #0:  Going for a chair
     In kid #0:  Done trying to sit

 In Mom: All seats are taken!

 In Mom: this round's loser is kid#0

 ---------------------------------------------

 In kid #9:  standing up!
 In kid #1:  standing up!
 In kid #2:  standing up!
 In kid #3:  standing up!
 In kid #4:  standing up!
 In kid #0:  received Sig: SIGQUIT
 In kid #3:  received Sig: SIGUSR1
 In kid #0:  End of the road for me
 In kid #3:  I'm marching!
 In kid #2:  received Sig: SIGUSR1
 In kid #4:  received Sig: SIGUSR1
 In kid #8:  standing up!
 In kid #1:  received Sig: SIGUSR1
 In kid #1:  I'm marching!
 In kid #2:  I'm marching!
 In kid #4:  I'm marching!
 In kid #9:  received Sig: SIGUSR1
 In kid #9:  I'm marching!
 In kid #8:  received Sig: SIGUSR1
 In kid #8:  I'm marching!
 In kid #6:  standing up!
 In kid #6:  received Sig: SIGUSR1
 In kid #6:  I'm marching!

 In Mom: Everyone is marching now

 In kid #9:  received Sig: SIGUSR2
 In kid #3:  received Sig: SIGUSR2
 In kid #2:  received Sig: SIGUSR2
 In kid #1:  received Sig: SIGUSR2
 In kid #8:  received Sig: SIGUSR2
 In kid #6:  received Sig: SIGUSR2
 In kid #4:  received Sig: SIGUSR2
     In kid #1:  Going for a chair
         In kid #1:  Got chair #5
     In kid #1:  Done trying to sit
     In kid #6:  Going for a chair
     In kid #6:  Going for a chair
         In kid #6:  Got chair #0
     In kid #6:  Done trying to sit
     In kid #9:  Going for a chair
     In kid #9:  Going for a chair
         In kid #9:  Got chair #1
     In kid #9:  Done trying to sit
     In kid #8:  Going for a chair
         In kid #8:  Got chair #2
     In kid #8:  Done trying to sit
     In kid #4:  Going for a chair
     In kid #4:  Going for a chair
     In kid #4:  Going for a chair
     In kid #4:  Going for a chair
     In kid #4:  Going for a chair
         In kid #4:  Got chair #3
     In kid #4:  Done trying to sit
     In kid #3:  Going for a chair
     In kid #3:  Going for a chair
         In kid #3:  Got chair #4
     In kid #3:  Done trying to sit
     In kid #2:  Going for a chair
     In kid #2:  Going for a chair
     In kid #2:  Going for a chair
     In kid #2:  Going for a chair
     In kid #2:  Going for a chair
     In kid #2:  Going for a chair
     In kid #2:  Done trying to sit

 In Mom: All seats are taken!

 In Mom: this round's loser is kid#2

 ---------------------------------------------

 In kid #9:  standing up!
 In kid #1:  standing up!
 In kid #2:  received Sig: SIGQUIT
 In kid #1:  received Sig: SIGUSR1
 In kid #2:  End of the road for me
 In kid #1:  I'm marching!
 In kid #6:  standing up!
 In kid #3:  standing up!
 In kid #4:  standing up!
 In kid #6:  received Sig: SIGUSR1
 In kid #3:  received Sig: SIGUSR1
 In kid #9:  received Sig: SIGUSR1
 In kid #9:  I'm marching!
 In kid #4:  received Sig: SIGUSR1
 In kid #6:  I'm marching!
 In kid #3:  I'm marching!
 In kid #4:  I'm marching!
 In kid #8:  standing up!
 In kid #8:  received Sig: SIGUSR1
 In kid #8:  I'm marching!

 In Mom: Everyone is marching now

 In kid #9:  received Sig: SIGUSR2
 In kid #3:  received Sig: SIGUSR2
 In kid #1:  received Sig: SIGUSR2
 In kid #4:  received Sig: SIGUSR2
 In kid #8:  received Sig: SIGUSR2
 In kid #6:  received Sig: SIGUSR2
     In kid #4:  Going for a chair
         In kid #4:  Got chair #4
     In kid #4:  Done trying to sit
     In kid #9:  Going for a chair
         In kid #9:  Got chair #1
     In kid #9:  Done trying to sit
     In kid #8:  Going for a chair
     In kid #1:  Going for a chair
     In kid #1:  Going for a chair
     In kid #8:  Going for a chair
         In kid #1:  Got chair #2
     In kid #1:  Done trying to sit
     In kid #8:  Going for a chair
         In kid #8:  Got chair #3
     In kid #8:  Done trying to sit
     In kid #3:  Going for a chair
     In kid #3:  Going for a chair
     In kid #3:  Going for a chair
     In kid #3:  Going for a chair
     In kid #6:  Going for a chair
     In kid #6:  Going for a chair
     In kid #6:  Going for a chair
         In kid #3:  Got chair #0
     In kid #3:  Done trying to sit
     In kid #6:  Going for a chair
     In kid #6:  Going for a chair
     In kid #6:  Done trying to sit

 In Mom: All seats are taken!

 In Mom: this round's loser is kid#6

 ---------------------------------------------

 In kid #9:  standing up!
 In kid #1:  standing up!
 In kid #8:  standing up!
 In kid #3:  standing up!
 In kid #4:  standing up!
 In kid #6:  received Sig: SIGQUIT
 In kid #6:  End of the road for me
 In kid #9:  received Sig: SIGUSR1
 In kid #9:  I'm marching!
 In kid #1:  received Sig: SIGUSR1
 In kid #1:  I'm marching!
 In kid #8:  received Sig: SIGUSR1
 In kid #8:  I'm marching!
 In kid #4:  received Sig: SIGUSR1
 In kid #4:  I'm marching!
 In kid #3:  received Sig: SIGUSR1
 In kid #3:  I'm marching!

 In Mom: Everyone is marching now

 In kid #9:  received Sig: SIGUSR2
 In kid #1:  received Sig: SIGUSR2
 In kid #3:  received Sig: SIGUSR2
 In kid #8:  received Sig: SIGUSR2
 In kid #4:  received Sig: SIGUSR2
     In kid #1:  Going for a chair
         In kid #1:  Got chair #1
     In kid #1:  Done trying to sit
     In kid #3:  Going for a chair
     In kid #3:  Going for a chair
         In kid #3:  Got chair #2
     In kid #3:  Done trying to sit
     In kid #4:  Going for a chair
     In kid #4:  Going for a chair
         In kid #4:  Got chair #3
     In kid #4:  Done trying to sit
     In kid #8:  Going for a chair
     In kid #9:  Going for a chair
     In kid #9:  Going for a chair
     In kid #8:  Going for a chair
         In kid #9:  Got chair #0
     In kid #9:  Done trying to sit
     In kid #8:  Going for a chair
     In kid #8:  Going for a chair
     In kid #8:  Done trying to sit

 In Mom: All seats are taken!

 In Mom: this round's loser is kid#8

 ---------------------------------------------

 In kid #9:  standing up!
 In kid #1:  standing up!
 In kid #4:  standing up!
 In kid #3:  standing up!
 In kid #9:  received Sig: SIGUSR1
 In kid #9:  I'm marching!
 In kid #4:  received Sig: SIGUSR1
 In kid #4:  I'm marching!
 In kid #8:  received Sig: SIGQUIT
 In kid #8:  End of the road for me
 In kid #1:  received Sig: SIGUSR1
 In kid #1:  I'm marching!
 In kid #3:  received Sig: SIGUSR1
 In kid #3:  I'm marching!

 In Mom: Everyone is marching now

 In kid #9:  received Sig: SIGUSR2
 In kid #1:  received Sig: SIGUSR2
 In kid #4:  received Sig: SIGUSR2
 In kid #3:  received Sig: SIGUSR2
     In kid #1:  Going for a chair
         In kid #1:  Got chair #1
     In kid #1:  Done trying to sit
     In kid #9:  Going for a chair
         In kid #9:  Got chair #2
     In kid #9:  Done trying to sit
     In kid #4:  Going for a chair
     In kid #4:  Going for a chair
     In kid #4:  Going for a chair
     In kid #3:  Going for a chair
     In kid #3:  Going for a chair
     In kid #3:  Going for a chair
     In kid #3:  Done trying to sit
         In kid #4:  Got chair #0
     In kid #4:  Done trying to sit

 In Mom: All seats are taken!

 In Mom: this round's loser is kid#3

 ---------------------------------------------

 In kid #9:  standing up!
 In kid #1:  standing up!
 In kid #3:  received Sig: SIGQUIT
 In kid #3:  End of the road for me
 In kid #4:  standing up!
 In kid #1:  received Sig: SIGUSR1
 In kid #1:  I'm marching!
 In kid #4:  received Sig: SIGUSR1
 In kid #4:  I'm marching!
 In kid #9:  received Sig: SIGUSR1
 In kid #9:  I'm marching!

 In Mom: Everyone is marching now

 In kid #9:  received Sig: SIGUSR2
 In kid #1:  received Sig: SIGUSR2
 In kid #4:  received Sig: SIGUSR2
     In kid #4:  Going for a chair
         In kid #4:  Got chair #0
     In kid #4:  Done trying to sit
     In kid #9:  Going for a chair
         In kid #9:  Got chair #1
     In kid #9:  Done trying to sit
     In kid #1:  Going for a chair
     In kid #1:  Going for a chair
     In kid #1:  Done trying to sit

 In Mom: All seats are taken!

 In Mom: this round's loser is kid#1

 ---------------------------------------------

 In kid #9:  standing up!
 In kid #4:  standing up!
 In kid #1:  received Sig: SIGQUIT
 In kid #1:  End of the road for me
 In kid #9:  received Sig: SIGUSR1
 In kid #9:  I'm marching!
 In kid #4:  received Sig: SIGUSR1
 In kid #4:  I'm marching!

 In Mom: Everyone is marching now

 In kid #9:  received Sig: SIGUSR2
 In kid #4:  received Sig: SIGUSR2
     In kid #9:  Going for a chair
         In kid #9:  Got chair #0
     In kid #9:  Done trying to sit
     In kid #4:  Going for a chair
     In kid #4:  Done trying to sit

 In Mom: All seats are taken!

 In Mom: this round's loser is kid#4

      -------------------------------------
     |                                     |
     |        Kid #9 wins the game!        |
     |                                     |
      -------------------------------------

 In Mom: Getting kids back
 In kid #4:  received Sig: SIGQUIT
 In kid #4:  End of the road for me
 In kid #9:  received Sig: SIGQUIT
 In kid #9:  End of the road for me
 In Mom: Welcome home kid #9
 In Mom: Welcome home kid #4
 In Mom: Welcome home kid #1
 In Mom: Welcome home kid #3
 In Mom: Welcome home kid #8
 In Mom: Welcome home kid #6
 In Mom: Welcome home kid #2
 In Mom: Welcome home kid #0
 In Mom: Welcome home kid #5
 In Mom: Welcome home kid #7
 Kid #9 is no more
 Kid #4 is no more
 Kid #1 is no more
 Kid #3 is no more
 Kid #8 is no more
 Kid #6 is no more
 Kid #2 is no more
 Kid #0 is no more
 Kid #5 is no more
 Kid #7 is no more

 Party's over, kids!
 */
