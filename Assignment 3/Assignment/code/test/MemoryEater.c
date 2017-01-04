#include "syscall.h"

int
main()
{
	char* str;
	int array[5000];
	int i;
	//str = "I eat memory and do nothing\0";
        //Write("ello", 4, 1);
	Write("I eat memory and do nothing", 26, 1);

	for (i = 0; i<500; i++)
	{
		array[i] = 0;
	}
	//str = "I eat memory and do nothing\0";
	Write("I eat memory and do nothing", 26, 1);
	Close(1);
	Exit(0);
	Halt();
}
