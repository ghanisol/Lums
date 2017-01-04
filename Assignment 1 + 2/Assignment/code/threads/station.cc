#ifndef STATION_CC
#define STATION_CC

#include "station.h"

station::station()
{
    train_lock = new Lock("trainLock");
    for (int i = 0; i < 5; i++)
    {
	trainLimit[i] = new Semaphore("lim_sem", 50);
    }
}

station::~station()
{
    delete [] trainLimit;
    delete train_lock;
}

void station::GoingFromTo(int src, int dest)
{
    train_lock->Acquire();
    fromStat[src].Wait(train_lock);
    train_lock->Release();

    trainLimit[(lastT+src) % 5]->P();

    train_lcok->Acquire();
    toStat[dest].Wait(train_lock);

    train_lock->Release();

    trainLimit[(lastT+dest) % 5]->V();
}

void station::stop(int cur_floor)
{
    train_lock->Acquire();

    toStat[cur_floor].Broadcast(train_lock);
    fromStat[cur_floor].Broadcast(train_lock);

    train_lock->Release();
}

void station::main()
{
    while(true)
    {
 	for (int i = 0; i < 10; i++)
	{
	    stop(i);
	    stop(i+1);
	    stop(i+2);
	    stop(i+3);
	    stop(i+4);
	    
   	    lastT = (lastT + 1) % 10;
	}
    }

}
