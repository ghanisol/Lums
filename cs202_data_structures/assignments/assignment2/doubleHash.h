#include <string.h>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

class DoubleHash
{
	private:
		long tableSize;
		string *hashTable;				// Include your linked list class for this!
		int a;							// input to the hash function
		int collisions;
		long size;
	public:
		DoubleHash(int A);
		void Load(char* file);
		long getSize();
		void resize();
		void insertItem(string Word);	// Takes a hash of 'Word' and inserts it into hashTable accordingly
		int hash1(string);
		int hash2(string);
		string lookUp(string Word);		// Looks for 'Word' and if found, returns it
		int Collisions(); // Return number of collisions in hashTable.
};
