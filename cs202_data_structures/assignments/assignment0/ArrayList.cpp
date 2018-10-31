#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include "ArrayList.h"

template <class T>
ArrayList<T>::ArrayList(const ArrayList<T>& otherArrayList)
{
	size = otherArrayList.length();
	capacity = otherArrayList.capacity;
	array = new T[capacity];

	for (int i = 0; i < size; i++)
	{
		array[i] = otherArrayList.getAt(i);
	}
	
	resize();
}

template <class T>
ArrayList<T>::~ArrayList()
{
	delete []array;
}

template <class T>
void ArrayList<T>::insertAtHead(T item)
{
	for (int i = size; i > 0; i--)
	{
		array[i] = array[i-1];
	}
	array[0] = item;
	size++;
	
	resize();
}

template <class T>
void ArrayList<T>::insertAtTail(T item)
{
	array[size] = item;
	size++;
	resize();
}

template <class T>
void ArrayList<T>::insertAfter(T toInsert, T afterWhat)
{
	int j = searchFor(afterWhat);
	
	for (int i = size; i > j+1; i--)
	{
		array[i] = array[i-1];
	}
	array[j+1] = toInsert;
	size++;
	
	resize();
	
}

template <class T>
void ArrayList<T>::insertSorted(T item)
{	
	int j = size;
	for (int i = 0; i < size; i++)
	{
		if (array[i] > item)
		{
			j = i;
			break;
		}
	}
	insertAfter(item, array[j-1]);
	
}

template <class T>
T ArrayList<T>::getAt(int i) const
{
	return array[i];
}

template <class T>
int ArrayList<T>::searchFor(T item)
{
	for (int i = 0; i < size; i++)
	{
		if (array[i] == item)
		{
			return i;
		}
	}
	return NULL;
}

template <class T>
void ArrayList<T>::deleteElement(T item)
{
	int i = searchFor(item);
		
	deleteAt(i);
}

template <class T>
void ArrayList<T>::deleteAt(int i)
{
	for (int j = i; j < size-1; j++)
	{
		array[j] = array[j+1];
	}
	size--;
}

template <class T>
void ArrayList<T>::deleteHead()
{
	for (int i = 0; i < size-1; i++)
	{
		array[i] = array[i+1];
	}
	size--;
}

template <class T>
void ArrayList<T>::deleteTail()
{
	size--;
}

template <class T>
void ArrayList<T>::resize()
{
	if (size == capacity)
	{
		T *temp = new T[size*2];
		for (int i = 0; i < size; i++)
		{
			temp[i] = array[i];
		}
		array = temp;
		capacity *= 2;
	}
}

template <class T>
int ArrayList<T>::length() const
{
	return size;
}

template <class T>
void ArrayList<T>::reverse()
{	
	for (int i = 0, j = size-1; i < j; i++, j--)
	{
		T temp = array[i];
		array[i] = array[j];
		array[j] = temp;
	}
}

#endif
