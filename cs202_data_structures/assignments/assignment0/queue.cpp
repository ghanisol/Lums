#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

#include <iostream>
using namespace std;

template <class T>
Queue<T>::Queue()
{
	vipCount = 0;
}
    
template <class T>
Queue<T>::Queue(const Queue<T>& otherQueue)
{
	vipCount = otherQueue.vipCount;
	int len = otherQueue.list.length();
	ListItem<T> *ptr = otherQueue.list.getHead();
	for (int i = 0; i < len; i++)
	{
		list.insertAtTail(ptr->value);
		ptr = ptr->next;
	}
}

template <class T>
Queue<T>::~Queue()
{

}

template <class T>
void Queue<T>::enqueue(T item)
{
	list.insertAtTail(item);
}

template <class T>
T Queue<T>::front()
{
	return list.getHead()->value;
}

template <class T>
T Queue<T>::dequeue()
{
	if (vipCount > 0)
	{
		vipCount--;
	}
	T temp = list.getHead()->value;
	list.deleteHead();
	return temp;
}

template <class T>
int Queue<T>::length()
{
	return list.length();
}

template <class T>
bool Queue<T>::isEmpty()
{
	if (list.length() == 0)
	{
		return true;
	}
	return false;
}

template <class T>
void Queue<T>::AddVip(T item)
{
	ListItem<T> *ptr = list.getHead();
	if (vipCount == 0)
	{
		list.insertAtHead(item);
	}
	else
	{
		for (int i = 1; i < vipCount; i++)
		{
			ptr = ptr->next;
		}
		
		list.insertAfter(item, ptr->value);
	}
	vipCount++;
	
}


#endif
