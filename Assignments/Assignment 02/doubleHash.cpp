#ifndef DOUBLEHASH_CPP
#define DOUBLEHASH_CPP

#include "doubleHash.h"

DoubleHash::DoubleHash(int A)
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

void DoubleHash::Load(char* file)
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

long DoubleHash::getSize()
{
	return size;
}

void DoubleHash::resize()
{
	if (size == tableSize)
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

void DoubleHash::insertItem(string Word)
{
	resize();
	int i = 0;
	long index = abs((hash1(Word) + i * hash2(Word)) % tableSize);
	while (hashTable[index] != "NULL")
	{
		if (i < 4)
		{
			i++;
			index = abs((hash1(Word) + i * hash2(Word)) % tableSize);
			collisions++;	
		}
		else
		{
			index++;
			collisions++;
		}
	}
	
	hashTable[index] = Word;
	size++;
}

int DoubleHash::hash1(string str)
{
	unsigned long long hash = 0;
	for (int i = 0; i < str.length(); i++)
	{
		hash = pow(hash, (hash << 5) + (hash >> 2) + str[i]);
	}
	
	return abs(hash);
}

int DoubleHash::hash2(string str)
{
	int len = str.length();
	unsigned long long hash = 0;
	
	for (int i = len; i > 0; i--)
	{
		hash += pow(a, i-1) * int(str[len - i]);
	}
	return abs(hash);
}

string DoubleHash::lookUp(string Word)
{
	int i = 0;
	long index = abs((hash1(Word) + i * hash2(Word)) % tableSize);
	
	while (hashTable[index] != Word)
	{
		if (i < 4)
		{
			i++;
			index = abs((hash1(Word) + i * hash2(Word)) % tableSize);	
		}
		else
		{
			index++;
		}
	}
	
	return hashTable[index];
}

int DoubleHash::Collisions()
{
	return collisions;
}


#endif
