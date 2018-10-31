#ifndef MAIN
#define MAIN

#include "HashC.cpp"
#include "assert.h"

int main()
{
	ofstream fout;
	fout.open("col.txt");
	char buf[256];
	HashC c(37);
	string* qs = new string[20000];
	
	c.Load("dict.txt");
	
	ifstream ifin;
	ifin.open("queries.txt");
	int n=0;
	
	while(!ifin.eof())
	{
		ifin.getline(buf,256,'\n');
		string str = buf;
		qs[n++] = str;
	}
	
	for(int i=0; i<n-1; i++)
	{
		assert(c.lookup(qs[i])->value == qs[i]);
	}
	cout << "Passed" << endl;
}

#endif
