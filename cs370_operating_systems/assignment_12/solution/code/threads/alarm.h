#ifndef ALARMOO_H
#define ALARMOO_H

#include "synch.h"

class Alarm
{
    public:
    	List *sleepQ;

	Alarm() { sleepQ = NULL; }
	~Alarm() { delete sleepQ; }
 	void GoForSleep(int howLong);
 	void wakeUp();
};

#endif
