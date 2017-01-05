#ifndef __LINKEDLIST_CPP
#define __LINKEDLIST_CPP
#include <iostream>
#include <cstdlib>
#include "LinkedList.h"

using namespace std;

int main()
{
	LinkedList list_1;
	
	// Insert At Head
	list_1.insertAtHead(82);
	list_1.insertAtHead(16);
	list_1.insertAtHead(12);
	
	// Insert After
	list_1.insertAfter(14, 12);
	list_1.insertAfter(15, 14);
	
	// Insert at Tail
	list_1.insertAtintail(99);

	// Display List
	Node* temp = list_1.head;
	while(true)
	{
		
		cout << temp->data << endl;
		if (temp->next == NULL)
		{
			break;
		}
		temp = temp->next; 
	}
	
	// Get Head
	Node* header = list_1.getHead();
	cout << "Header value : " << header->data << endl;
	
	// Get Tail
	Node* tail = list_1.getintail();
	cout << "Tail value : " << tail->data << endl;
	
	// Search
	Node* search1 = list_1.searchFor(14);
	cout << "Search for 14 : " << search1->data << endl;
	Node* search2 = list_1.searchFor(21);
	if (search2 == NULL)
	{
		cout << "Search for NULL : NULL" << endl;
	}
	
	
	// Delete Element
	list_1.deleteElement(14);
	
	// Display List
	Node* temp3 = list_1.head;
	while(true)
	{
		
		cout << temp3->data << endl;
		if (temp3->next == NULL)
		{
			break;
		}
		temp3 = temp3->next; 
	}
	
	// Insert Sorted
	list_1.insertSorted(22);
	
	// Display List
	cout << "Sorted List :\n";
	Node* temp9 = list_1.head;
	while(true)
	{
		
		cout << temp9->data << endl;
		if (temp9->next == NULL)
		{
			break;
		}
		temp9 = temp9->next; 
	}
	
	// Delete Head
	list_1.deleteHead();
	Node* temp4 = list_1.head;
	cout << "New Head value : " << temp4->data << endl;
	
	// Delete Tail
	list_1.deleteintail();
	
	// Display List
	Node* temp5 = list_1.head;
	cout << "New List : " << endl;
	while(true)
	{
		
		cout << temp5->data << endl;
		if (temp5->next == NULL)
		{
			break;
		}
		temp5 = temp5->next; 
	}
	
	// Length
	int length = list_1.length();
	cout << "len: " << length << endl;
}

LinkedList::LinkedList()
{
	head = NULL;
}


LinkedList::LinkedList(const LinkedList& otherLinkedList)
{
	
	head = otherLinkedList.head;
}


LinkedList::~LinkedList()
{
	Node *ptr1 = head;
    Node *ptr2 = ptr1->next;
    while(ptr2->next != NULL)
	{
		delete ptr1;
       	ptr1 = ptr2;
    	ptr2 = ptr2->next;
    }    
    delete ptr1;
    delete ptr2;
}


void LinkedList::insertAtHead(int item)
{
	Node *newNode = new Node;
	newNode->data = item;
	newNode->next = head;
	head = newNode; 
}


void LinkedList::insertAtintail(int item)
{
	Node *ptr = head;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;	
	}
	ptr->next = new Node;
	ptr = ptr->next;
	ptr->data = item;
	ptr->next = NULL;
}


void LinkedList::insertAfter(int toInsert, int afterWhat)
{
	Node *ptr = head;
	while (ptr->data != afterWhat)
	{
		ptr = ptr->next;
	}
	Node *temp = new Node;
	temp->data = toInsert;
	temp->next = ptr->next;
	ptr->next = temp;
}


void LinkedList::insertSorted(int item)
{
	Node *ptr1 = head;
	Node *ptr2 = head->next;
	while (ptr2->data < item)
	{
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
	}
	Node *temp = new Node;
	temp->data = item;
	temp->next = ptr1->next;
	ptr1->next = temp;
}


Node* LinkedList::getHead()
{
	return head;
}


Node* LinkedList::getintail()
{
	Node *ptr = head;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;	
	}
	return ptr;
}


Node *LinkedList::searchFor(int item)
{
	Node *ptr = head;
	while (ptr->next != NULL)
	{
		if (ptr->data == item)
		{
			return ptr;
		}
		ptr = ptr->next;
	}
	return NULL;
}


void LinkedList::deleteElement(int item)
{
	Node *ptr1 = head;
	Node *ptr2 = head->next;
	while (ptr2->next != NULL)
	{
		if ((ptr2->data) == item)
		{
			ptr1->next = ptr2->next;
			ptr2->next = NULL;
			return;
		}
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;
	}
}


void LinkedList::deleteHead()
{
	head = head->next;
}


void LinkedList::deleteintail()
{
	Node *ptr1 = head;
	Node *ptr2 = head->next;
	while (ptr2->next != NULL)
	{
		ptr1 = ptr1->next;
		ptr2 = ptr2->next;	
	}
	ptr1->next = NULL;
	
}


int LinkedList::length()
{
	Node *ptr = head;
	int len = 0;
	
	while (ptr != NULL)
	{
		len++;
		ptr = ptr->next;
	}
	return len;
}

#endif
