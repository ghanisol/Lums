#ifndef __LINKEDLIST_H
#define __LINKEDLIST_H
#include <cstdlib>

/* This class just holds a single data item. */

class Node {
	public:
	int data;
	Node* next;
};

/* This is the generic List class */

class LinkedList
{
	
	    

	public:
		Node *head;
		
		// Constructor
		LinkedList();
		
		// Copy Constructor
		LinkedList(const LinkedList& otherList);
		
		// Destructor
		~LinkedList();
		
		// Insertion Functions
		void insertAtHead(int item);
		void insertAtintail(int item);
		void insertAfter(int toInsert, int afterWhat);
		void insertSorted(int item);
		
		// Lookup Functions
		Node *getHead();
		Node *getintail();
		Node *searchFor(int item);
		
		// Deletion Functions
		void deleteElement(int item);
		void deleteHead();
		void deleteintail();
		
		// Utility Functions
		int length();
};

#endif
