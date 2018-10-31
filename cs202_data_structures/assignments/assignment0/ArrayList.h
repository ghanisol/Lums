#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H
#include <cstdlib>
#include <iostream>

/* This is the generic List class */
template <class T>
class ArrayList
{
    T *array;
    int size;

public:
    int capacity;

    // Constructor
    ArrayList() {
        size = 0;
        capacity = 4;
        array = new T[capacity];
    }

    // Copy Constructor
    ArrayList(const ArrayList<T>& otherList);

    // Destructor
    ~ArrayList();

    // Insertion Functions
    void insertAtHead(T item);
    void insertAtTail(T item);
    void insertAfter(T toInsert, T afterWhat);
    void insertSorted(T item);

    // Lookup Functions
    int searchFor(T item);
    T getAt(int i) const;

    // Deletion Functions
    void deleteElement(T item);
    void deleteAt(int i);
    void deleteHead();
    void deleteTail();

    // Utility Functions
    void resize();
    int length() const;
    T* getArray();
    void reverse();
};

#endif
