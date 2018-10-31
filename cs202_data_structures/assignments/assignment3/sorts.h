#ifndef __SORTS_H
#define __SORTS_H

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "list.cpp"

using namespace std;

vector<long> InsertionSort(vector<long> nums);
vector<long> MergeSort(vector<long> nums);
vector<long> QuickSortArray(vector<long> nums);
vector<long> QuickSortList(vector<long> nums);
vector<long> HeapSort(vector<long> nums);
vector<long> BucketSort(vector<long> nums, int max);

// Merge Sort Helper Functions
List<long> mergeSort(List<long> sort_list);
List<long> merger(List<long> left, List<long> right);

// Quick Sort Helper Functions
long *quickSortArray(long numbers[], int size);
List<long> quickSortList(List<long> numbers);

// Heap Sort Helper Functions
void heapify(long *numbers, int array_size, int index);
void buildHeapify(long *numbers, int index);
#endif

