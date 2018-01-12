#include <stdio.h>
#include <map>

std::map<char*, int> totalBranches;
std::map<char*, int> trueBranches;

void count_branch(char* func_name, int cond)
{
	totalBranches[func_name]++;
	if (cond)
	{
		trueBranches[func_name]++;
	}
}

void print_info()
{
	printf("%-40s%-15s%-15s%-15s\n", "Function", "Bias", "Taken", "Total");
	
    for (std::map<char*, int>::iterator it = totalBranches.begin(); it != totalBranches.end(); it++)
    {
    	char* func_name = it->first;
    	int tot = it->second;

    	int taken = trueBranches.count(func_name) == 0 ? 0 : trueBranches[func_name];
    	double bias = taken*1.0 / tot;
    	printf("%-40s%-15f%-15i%-15i\n", func_name, bias, taken, tot);
    }
} 
