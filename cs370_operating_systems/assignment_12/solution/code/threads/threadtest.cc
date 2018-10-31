// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "synch.h"
#include "unistd.h"

#include "sendRcv.cc"
#include "elevator.cc"
#include "alarm.cc"

// testnum is set in main.cc
int testnum = 1;

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 100; num++) {
	
	Semaphore *semTest = new Semaphore("Test Semaphore", 1);
	semTest->P();
	printf("*** thread %d looped %d times\n", which, num);
	semTest->V();
	delete semTest;
    }
}

//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1");

    Thread *t = new Thread("forked thread", 3, 0);
    t->Fork(SimpleThread, 1);

    Thread *t2 = new Thread("forked thread 2", 1, 0);
    t2->Fork(SimpleThread, 2);

    Thread *t3 = new Thread("forked thread 3", 5, 0);
    t3->Fork(SimpleThread, 3);
	
    Thread *t4 = new Thread("forked thread 4", 2, 0);
    t4->Fork(SimpleThread, 4);

    //SimpleThread(0);
}

//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    switch (testnum) {
    case 1:
	ThreadTest1();
	break;
    default:
	printf("No test specified.\n");
	break;
    }
}

