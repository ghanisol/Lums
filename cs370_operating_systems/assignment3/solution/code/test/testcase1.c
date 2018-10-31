
#include "syscall.h"

int
main()
{
	int 	ID_1;
	int 	ID_2;
	char 	buf[100];

	Write("STARTING THE TEST CASE\n\n", 24, ConsoleOutput);
	Create("testcase1.txt");
	Create("testcase2.txt");
	ID_1 = Open("testcase1.txt");
	ID_2 = Open("testcase2.txt");
	Write("THIS IS FILE ONE\n", 17, ID_1);
	Write("THIS IS FILE TWO\n", 17, ID_2);
	Close(ID_1);
	// ID_1 = Open("testcase1.txt");
	Read(buf, 17, ID_1);
	Write("PRINTING THE READ BUFFER:\n----------", 36, ConsoleOutput);
	Write(buf, 17, ConsoleOutput);
	Write("\n----------", 11, ConsoleOutput);
	Write("\n\nABOUT TO CLOSE\n----------", 27, ConsoleOutput);
	Exit(0);
	Write("\nCLOSE FAILED\n", 14, ConsoleOutput);
	
	return 0;
}