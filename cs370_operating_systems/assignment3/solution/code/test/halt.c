/* halt.c
 *	Simple program to test whether running a user program works.
 *	
 *	Just do a "syscall" that shuts down the OS.
 *
 * 	NOTE: for some reason, user programs with global data structures 
 *	sometimes haven't worked in the Nachos environment.  So be careful
 *	out there!  One option is to allocate data structures as 
 * 	automatics within a procedure, but if you do this, you have to
 *	be careful to allocate a big enough stack to hold the automatics!
 */

#include "syscall.h"

int
main()
{
/*
    char * stir;
//    Create("ghani.txt");
    Create("faizi.txt");
//    Open("ghani.txt");
    Open("faizi.txt");
//    Write("Hello World" ,11, 2); 
 
//    a = Read(stir, 11, 2);
//    Write(stir, 11, 1);

    Close(2);
//    Close(1);
*/
/*    SpaceId a ;
    int x;
    a = Exec("../test/shell");
    Create("aftershell.txt");
    x = Join(a);
    Create("exectest.txt");*/
    Create("party.txt");
    Open("party.txt");
    Exit(0);
    Halt();
    /* not reached */
}
