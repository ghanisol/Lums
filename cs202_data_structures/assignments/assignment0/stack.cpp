#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

template <class T>
Stack<T>::Stack()
{
	
}
    
template <class T>
Stack<T>::Stack(const Stack<T>& otherStack)
{
	int len = otherStack.list.length();
	ListItem<T> *ptr = otherStack.list.getHead();
	for (int i = 0; i < len; i++)
	{
		list.insertAtTail(ptr->value);
		ptr = ptr->next;
	}
}

template <class T>
Stack<T>::~Stack()
{
	
}

template <class T>
void Stack<T>::push(T item)
{
	list.insertAtHead(item);
}

template <class T>
T Stack<T>::top()
{
	return list.getHead()->value;
}

template <class T>
T Stack<T>::pop()
{
	T temp = list.getHead()->value;
	list.deleteHead();
	return temp;
}

template <class T>
int Stack<T>::length()
{
	return list.length();
}

template <class T>
bool Stack<T>::isEmpty()
{
	if (list.length() == 0)
	{
		return true;
	}
	return false;
}

#endif
