#include <map>
#include <stdio.h>

std::map<char*, int> instructions;

void count_inst(char* inst_name, int inst_code)
{ 
    //printf("%s\t%i\n",inst_name, inst_code);
    instructions[inst_name]++;
}

void print_info()
{
	int tot = 0;

    for (std::map<char*, int>::iterator it = instructions.begin(); it != instructions.end(); it++)
    {
    	tot += it->second;
    	printf("%s\t%i\n",it->first,it->second);
    }
    printf("TOTAL\t%i\n", tot);
}
