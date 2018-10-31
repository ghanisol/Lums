#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "synch.h" 

class elevator
{
    private:
	Lock *elev_lock;
	Condition toFloor[5];
	Condition fromFloor[5];
	Semaphore *userLimit;
    
    public:
	elevator();
	~elevator();
	void GoingFromTo(int from, int to);
	void main();
	void stop(int cur_floor);
	
};

#endif
