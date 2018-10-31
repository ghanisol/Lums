#ifndef SENDRCV_H
#define SENDRCV_H

#include "synch.h"

class sendRcv
{
    private:
	Lock *mon_lock;
	Condition Sender[10];
	Condition Recv[10];
	int Buffer[10];
	Semaphore mesg[10];

    public:
	sendRcv();
	~sendRcv();
	void Send(int port, int msg);
	void Receive(int port, int *msg);
};

#endif
