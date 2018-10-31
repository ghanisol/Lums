
#include "syscall.h"

int
main()
{
	int ID;
	Write("\n\n*** ONE ***\n\n", 15, ConsoleOutput);
	ID = Exec("../test/testcase3");
	 Join(ID);
	Write("\n\n*** TWO ***\n\n", 15, ConsoleOutput);
	return 0;
}
