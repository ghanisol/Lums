#ifndef OPENADD_CPP
#define OPENADD_CPP

#include "openAddress.h"

OpenAddress::OpenAddress(int A)
{
	a = A;
	collisions = 0;
	tableSize = 1000;
	size = 0;
	hashTable = new string[tableSize];
	
	for (int i = 0; i < tableSize; i++)
	{
		hashTable[i] = "NULL";
	}
}

void OpenAddress::Load(char* file)
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
		insertItem(temp);
	}
	
	in_file.close();
}

int OpenAddress::hash(string str)
{
	int len = str.length();
	unsigned long long hash = 0;
	
	for (int i = len; i > 0; i--)
	{
		hash += pow(a, i-1) * int(str[len - i]);
	}
	return hash % tableSize;
}

long OpenAddress::getSize()
{
	return size;
}

void OpenAddress::resize()
{
	if (size == tableSize - 1)
	{
		string *temp = new string[tableSize];
		for (int i = 0; i < size; i++)
		{
			temp[i] = hashTable[i];
		}
		
		tableSize *= 2;
		hashTable = new string[tableSize];	
		for (int i = 0; i < tableSize; i++)
		{
			hashTable[i] = "NULL";
		}
		
		for (int i = 0; i < size; i++)
		{
			if (temp[i] != "NULL")
			{
				insertItem(temp[i]);
				size--;	
			}
		}
		delete [] temp;
	}
}

void OpenAddress::insertItem(string Word)
{
	cout << tableSize << " " << size << " ";
	resize();
	cout << tableSize << endl;
	long index = hash(Word);
	while (hashTable[index] != "NULL")
	{		
		if (index == tableSize - 1)
		{
			index = 0;
		}
		collisions++;
		index++;
	}
	
	hashTable[index] = Word;
	size++;
}

string OpenAddress::lookUp(string Word)
{
	long index = hash(Word);
	
	while (hashTable[index] != Word)
	{
		if (index == tableSize - 1)
		{
			index = 0;
		}
		index++;
	}

	return hashTable[index];
}

int OpenAddress::Collisions()
{
	return collisions;
}

#endif
