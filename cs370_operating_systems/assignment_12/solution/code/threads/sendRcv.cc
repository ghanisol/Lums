#ifndef SENDRCV_CC
#define SENDRCV_CC

#include "sendRcv.h"

sendRcv::sendRcv()
{
    mon_lock = new Lock("monLock");       
}

sendRcv::~sendRcv()
{

}

void sendRcv::Send(int port, int msg)
{
    List *waitingL = Recv[port].getList();
    if (!waitingL->IsEmpty())
    {
	mon_lock->Acquire();

	Buffer[port] = msg;
	Recv[port].Signal(mon_lock);    

	mon_lock->Release();
    }
    else
    {
	mon_lock->Acquire();

	Sender[port].Wait(mon_lock);
	Buffer[port] = msg;
	mesg[port].V();

        mon_lock->Release();
    }
}

void sendRcv::Receive(int port, int *msg)
{
    List *waitingL = Sender[port].getList();
    if (waitingL->IsEmpty())
    {
        mon_lock->Acquire();

        Sender[port].Signal(mon_lock);
        mesg[port].P();	

	*msg = Buffer[port];

        mon_lock->Release();
    }
    else
    {
        mon_lock->Acquire();

        Recv[port].Wait(mon_lock);
        *msg = Buffer[port];

        mon_lock->Release();
    }

}

#endif
