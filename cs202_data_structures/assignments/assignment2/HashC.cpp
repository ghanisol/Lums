#ifndef HashC_CPP
#define HashC_CPP

#include "Chaining.h"

HashC::HashC(int _a)
{
	a = _a;
	tableSize = 30000;
	collisions = 0;
	hashTable = new LinkedList<string>[tableSize];
}

void HashC::Load(char* file)
{
	ifstream in_file;
	in_file.open(file);
	
	if (in_file.fail())
	{
		cout << "Error reading file.\n";
		return;
	}
	
	while (!in_file.eof())
	{
		string temp;
		in_file >> temp;
		insert(temp);
	}
	
	in_file.close();
}

int HashC::hash(string str)
{
	int len = str.length();
	unsigned long long hash = 0;
	
	for (int i = len; i > 0; i--)
	{
		hash += pow(a, i-1) * int(str[len - i]);
	}
	return hash % tableSize;
}

void HashC::insert(string word)
{
	long index = hash(word);
	
	if (hashTable[index].length() != 0)
	{
		collisions++;
	}
	
	hashTable[index].insertAtHead(word);
}

ListItem<string>* HashC::lookup(string word)
{
	int index = hash(word);
	return hashTable[index].searchFor(word);
}

int HashC::Collisions()
{
	return collisions;
}

#endif
