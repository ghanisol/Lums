#ifndef ALARMOO_CC
#define ALARMOO_CC

#include "alarm.h"

void Alarm::GoForSleep(int howLong)
{
    sleepQ->SortedInsert((void *)currentThread, howLong + stats->totalTicks);
    IntStatus oldLevel = interrupt->SetLevel(IntOff);
    currentThread->Sleep();
}


#endif
