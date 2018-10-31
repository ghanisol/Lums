#ifndef ELEVATOR_CC
#define ELEVATOR_CC

#include "elevator.h"

elevator::elevator()
{
    elev_lock = new Lock("elevLock");
    userLimit = new Semaphore("userL_sem", 20);
}

elevator::~elevator()
{
    delete elev_lock;
    delete userLimit;
}

void elevator::GoingFromTo(int from, int to)
{
    
    elev_lock->Acquire();
    fromFloor[from].Wait(elev_lock);
    elev_lock->Release();

    userLimit->P();

    elev_lock->Acquire();
    toFloor[to].Wait(elev_lock);
    
    elev_lock->Release();

    userLimit->V();
}

void elevator::stop(int cur_floor)
{
    elev_lock->Acquire();

    toFloor[cur_floor].Broadcast(elev_lock);
    fromFloor[cur_floor].Broadcast(elev_lock);

    elev_lock->Release();
}

void elevator::main()
{
    while(true)
    {
	for (int cur_floor = 0; cur_floor < 5; cur_floor++)
	{
	    stop(cur_floor);
	}

	for (int cur_floor = 5; cur_floor > 0; cur_floor--)
	{
	    stop(cur_floor);
	}
    }
}

#endif
