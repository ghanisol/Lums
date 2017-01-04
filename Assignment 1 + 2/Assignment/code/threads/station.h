#ifndef STATION_H
#define STATION_H

#include "synch.h"

class station
{
    private:
	Lock *train_lock;
	Condition toStat[10];
	Condition fromStat[10];
	Semaphore *trainLimit[5];
	int lastT = 6;

    public:
	station();
	~station();
	void GoingFromTo(int src, int dest);
	void main();
	void stop(int cur_floor);
};


#endif
