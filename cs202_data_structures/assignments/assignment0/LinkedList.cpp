#ifndef __LIST_CPP
#define __LIST_CPP
#include <cstdlib>
#include "LinkedList.h"

template <class T>
LinkedList<T>::LinkedList()
{
	head = NULL;
	tail = NULL;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{	
	head = NULL;
	tail = NULL;
	
	ListItem<T> *ptr_otherL = otherLinkedList.head;
	while (ptr_otherL)
	{
		insertAtTail(ptr_otherL->value);
		ptr_otherL = ptr_otherL->next;
	}
}

template <class T>
LinkedList<T>::~LinkedList()
{
	/*while (head->next != NULL)
	{
		deleteHead();
	}
	delete head;
	*/
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
	ListItem<T> *temp = new ListItem<T>(item);
	if (head)
	{
		temp->next = head;
		head->prev = temp;
		head = temp;
	}
	else
	{
		head = temp;
		tail = temp;
	}
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
	ListItem<T> *temp = new ListItem<T>(item);
	if (tail)
	{
		temp->prev = tail;
		tail->next = temp;
		tail = temp;
	}
	else
	{
		head = temp;
		tail = temp;
	}
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
	ListItem<T> *ptr = searchFor(afterWhat);
	
	if (ptr)
	{
		if (!ptr->next)
		{
			insertAtTail(toInsert);
		}
		else
		{
			ListItem<T> *temp = new ListItem<T>(toInsert);
			temp->next = ptr->next;
			temp->prev = ptr;
			ptr->next->prev = temp;
			ptr->next = temp;
		}
	}
}


template <class T>
void LinkedList<T>::insertSorted(T item)
{
	ListItem<T> *ptr = head;
	bool isFound = false;
	while (ptr)
	{
		if (ptr->value >= item)
		{
			isFound = true;
			break;
		}
		ptr = ptr->next;
	}
	
	if (isFound)
	{
		if (!ptr->prev)
		{
			insertAtHead(item);
		}
		else
		{
			ListItem<T> *temp = new ListItem<T>(item);
			temp->next = ptr;
			temp->prev = ptr->prev;
			temp->prev->next = temp;
			ptr->prev = temp;
		} 
	}
	else
	{
		insertAtTail(item);
	}
}

template <class T>
ListItem<T>* LinkedList<T>::getHead() const
{
	return head;
}

template <class T>
ListItem<T>* LinkedList<T>::getTail()
{
	return tail;
}

template <class T>
ListItem<T> *LinkedList<T>::searchFor(T item)
{
	ListItem<T>* ptr = head;
	while (ptr)
	{
		if (ptr->value == item)
		{
			return ptr;
		}
		ptr = ptr->next;
	}
	return NULL;
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
	ListItem<T> *ptr = searchFor(item);
	if (ptr)
	{
		if (!ptr->next)
		{
			deleteTail();
		}
		else if (!ptr->prev)
		{
			deleteHead();
		}
		else 
		{
			ptr->prev->next = ptr->next;
			ptr->next->prev = ptr->prev;
			delete ptr;
		}
	}
	
}

template <class T>
void LinkedList<T>::deleteHead()
{
	ListItem<T> *ptr = head;
	if (ptr)
	{
		if (ptr != tail)
		{
			head = head->next;
			head->prev = NULL;
			delete ptr;
		}
		else
		{
			head = head->next;
			tail = NULL;
			delete ptr;
		}	
	}
}

template <class T>
void LinkedList<T>::deleteTail()
{
	ListItem<T> *ptr = tail;
	if (ptr)
	{
		if (ptr != head)
		{
			tail = tail->prev;
			tail->next = NULL;
			delete ptr;
		}
		else
		{
			tail = tail->prev;
			head = NULL;
			delete ptr;
		}
		
	}
	
}

template <class T>
int LinkedList<T>::length() const
{
	ListItem<T> *ptr = head;
	int len = 0;
	
	while (ptr)
	{
		len++;
		ptr = ptr->next;
	}
	return len;
}

template <class T>
void LinkedList<T>::reverse()
{
	tail = head;
	while (head)
	{
		ListItem<T> *temp = head->prev;
		head->prev = head->next;
		head->next = temp;
		if (head->prev)		// if not 'if condition', then head is lost!
		{
			head = head->prev;	
		}
		else
		{
			break;
		}
	}
}

template <class T>
void LinkedList<T>::parityArrangement()
{
	ListItem<T> *ptr = head;
	
	for(int i = 1; i <= length(); i++)
	{
		if (i % 2 == 0)
		{
			insertAtTail(ptr->value);
			ListItem<T> *del_ptr = ptr;
			ptr = ptr->next;
			deleteElement(del_ptr->value);
		}
		else
		{
			ptr = ptr->next;
		}
	}
}

#endif
