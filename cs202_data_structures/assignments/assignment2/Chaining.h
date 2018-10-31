#ifndef CHAINING__H
#define CHAINING__H
#include <iostream>
#include "LinkedList.cpp" // Your Own Implementation
#include <cstring>
#include <fstream>
#include <cmath>

using namespace std;

class HashC
{
	protected:
		long tableSize;
		int collisions; 
		int a; 
		LinkedList<string>* hashTable;
	
	public:
		HashC(int _a);
		void Load(char* file); // Load a file of Strings into your Hash table
		int hash(string); // Given a String, return its hash
		void insert(string word); // Takes a hash of 'word' and inserts it into hashTable accordingly
		ListItem<string>* lookup(string);
		int Collisions(); // Return number of collisions in hashTable
};
#endif
