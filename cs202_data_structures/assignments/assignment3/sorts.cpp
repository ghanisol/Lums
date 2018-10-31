#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"

//=====================================================================================
vector<long> InsertionSort(vector<long> nums)
{
	int size = nums.size();
	long numbers[size];
	
	for (int i = 0; i < size; i++)
	{
		numbers[i] = nums[i];
	}
	
	for (int i = 0; i < size; i++)
	{
		int j = i;
		
		while (j > 0 && numbers[j-1] > numbers[j])
		{
			long temp = numbers[j-1];
			numbers[j-1] = numbers[j];
			numbers[j] = temp;
			j--;
		}	
	}
	
	vector<long> result;
	for (int i = 0; i < size; i++)
	{
		result.push_back(numbers[i]);
	}
	
	return result;
}

//=====================================================================================
vector<long> MergeSort(vector<long> nums)
{
	List<long> numbers;
	int len = nums.size();
	for (int i = 0; i < len; i++)
	{
		numbers.insertAtTail(nums[i]);
	}
	
	List<long> sorted_list = mergeSort(numbers);
	
	vector<long> result;
	ListItem<long> *ptr = sorted_list.getHead();
	while (ptr != NULL)
	{
		result.push_back(ptr->value);
		ptr = ptr->next;
	}

	return result;
}

/* Merge Sort Helper Functions */
//=====================================================================================

List<long> mergeSort(List<long> sort_list)
{
	if (sort_list.length() == 0 || sort_list.length() == 1)
	{
		return sort_list;
	}
	else
	{
		ListItem<long> *left, *right;
		
		// Split List //
		ListItem<long> *ptr = sort_list.getHead();
		left = ptr;
		for (int i = 0; i < (sort_list.length() / 2) -1 ; i++)
		{
			ptr = ptr->next;
		}
		right = ptr->next;
		ptr->next = NULL;
		// ......... //
		
		List<long> left_list, right_list;
		left_list.head = left;
		right_list.head = right;
		return merger(mergeSort(left_list), mergeSort(right_list));
	}
}

List<long> merger(List<long> left, List<long> right)
{
	List<long> temp;
	ListItem<long> *ptr1 = left.getHead();
	while (ptr1 != NULL)
	{
		temp.insertSorted(ptr1->value);
		ptr1 = ptr1->next;
	}
	ptr1 = right.getHead();
	while (ptr1 != NULL)
	{
		temp.insertSorted(ptr1->value);
		ptr1 = ptr1->next;
	}
	return temp;
}

//=====================================================================================
vector<long> QuickSortArray(vector<long> nums)
{
	int size = nums.size();
	long numbers[size];
	
	for (int i = 0; i < size; i++)
	{
		numbers[i] = nums[i];
	}
	
	long *sorted_numbers = quickSortArray(numbers, size);
	
	vector<long> result;
	for (int i = 0; i < size; i++)
	{
		result.push_back(sorted_numbers[i]);
	}
	
	return result;
}

// ====================================================================================//
long *quickSortArray(long *numbers, int size)
{
	if (size <= 1)
	{
		return numbers;
	}
	else
	{
		long pivot = numbers[size/2-1];
		int g_size = 0, l_size = 0, e_size = 0;
		for (int i = 0; i < size; i++)
		{
			if (numbers[i] < pivot)
			{
				l_size++;
			}
			else if (numbers[i] > pivot)
			{
				g_size++;
			}
			else
			{
				e_size++;
			}
		}
		
	 	long greaterThan[g_size], lowerThan[l_size], equal[e_size];
		
		for (int i = 0, l_index = 0, g_index = 0, e_index = 0; i < size; i++)
		{
			if (numbers[i] < pivot)
			{
				lowerThan[l_index] = numbers[i];
				l_index++;
			}
			else if (numbers[i] > pivot)
			{
				greaterThan[g_index] = numbers[i];
				g_index++;
			}
			else
			{
				equal[e_index] = numbers[i];
				e_index++;
			}
		}
		
		
		
		long *v_left = quickSortArray(lowerThan, l_size);
		long *v_right = quickSortArray(greaterThan, g_size);
		
		long array_left[l_size];
		long array_right[g_size];
		for (int i = 0 ; i < l_size; i++)
		{
			array_left[i] = v_left[i];
		}
		for (int i = 0 ; i < g_size; i++)
		{
			array_right[i] = v_right[i];
		}
		
		long *result = new long[size];
		int index = 0;
		for (int i = 0; i < l_size; i++, index++)
		{
			result[index] = array_left[i];
		}
		for (int i = 0; i < e_size; i++, index++)
		{
			result[index] = equal[i];
		}
		for (int i = 0; i < g_size; i++, index++)
		{
			result[index] = array_right[i];
		}
		
		return result;
	}
}
//=====================================================================================//
vector<long> QuickSortList(vector<long> nums)
{
	List<long> numbers;
	int len = nums.size();
	for (int i = 0; i < len; i++)
	{
		numbers.insertAtTail(nums[i]);
	}
	
	List<long> sorted_list = quickSortList(numbers);
	
	vector<long> result;
	ListItem<long> *ptr = sorted_list.getHead();
	while (ptr != NULL)
	{
		result.push_back(ptr->value);
		ptr = ptr->next;
	}

	return result;
}

List<long> quickSortList(List<long> numbers)
{
	if (numbers.length() <= 1)
	{
		return numbers;
	}
	else
	{
		long pivot_index = numbers.length() / 2 -1;
		ListItem<long> *pivot = numbers.getHead();
		for (int i = 0; i < pivot_index; i++)
		{
			pivot = pivot->next;
		}

		List<long> greaterThan, lowerThan, equal;
		ListItem<long> *ptr = numbers.getHead();
		while (ptr != NULL)
		{
			if (ptr->value < pivot->value)
			{
				lowerThan.insertAtTail(ptr->value);
			}
			else if (ptr->value > pivot->value)
			{
				greaterThan.insertAtTail(ptr->value);
			}
			else
			{
				equal.insertAtTail(ptr->value);
			}
			ptr = ptr->next;
		}
		
		List<long> list_left = quickSortList(lowerThan);
		List<long> list_right = quickSortList(greaterThan);
		
		List<long> result;
		ListItem<long> *list_ptr;
		list_ptr = list_left.getHead();
		while (list_ptr != NULL)
		{
			result.insertAtTail(list_ptr->value);
			list_ptr = list_ptr->next;
		}
		list_ptr = equal.getHead();
		while (list_ptr != NULL)
		{
			result.insertAtTail(list_ptr->value);
			list_ptr = list_ptr->next;
		}
		list_ptr = list_right.getHead();
		while (list_ptr != NULL)
		{
			result.insertAtTail(list_ptr->value);
			list_ptr = list_ptr->next;
		}
		
		return result;
	}
}

//=====================================================================================
vector<long> HeapSort(vector<long> nums)
{
	int array_size = nums.size();
	long *numbers = new long[array_size];
	
	for (int i = 0; i < array_size; i++)
	{
		numbers[i] = nums[i];
		buildHeapify(numbers, i);
	}
	
	long *sorted_numbers = new long[array_size];
	
	for (int i = 0; i < nums.size(); i++)
	{
		sorted_numbers[i] = numbers[0];
		
		numbers[0] = numbers[array_size - 1];
		array_size--;
		heapify(numbers, array_size, 0);
		
	}
	
	vector<long> result;
	for (int i = 0; i < nums.size(); i++)
	{
		result.push_back(sorted_numbers[i]);
	}
	
	return result;
	
}

/*Heap Sort Helper Functions*/
//=====================================================================================
void heapify(long *numbers, int array_size, int index)
{
	if (index >= array_size - 1)
	{
		return;
	}
	else
	{
		int right = 2*index + 2;
		int left = 2*index + 1;
		
		if (right <= array_size - 1 && numbers[right] < numbers[index])
		{
			long temp = numbers[right];
			numbers[right] = numbers[index];
			numbers[index] = temp;
			heapify(numbers, array_size, right);			
		}	
		if (left <= array_size - 1 && numbers[left] < numbers[index])
		{
			long temp = numbers[left];
			numbers[left] = numbers[index];
			numbers[index] = temp;
			heapify(numbers, array_size, left);
		}
	}
}

void buildHeapify(long *numbers, int index)
{
	if (index == 0)
	{
		return;
	}
	else
	{
		int parent_index = (index - 1) / 2;
		if (numbers[parent_index] > numbers[index])
		{
			long temp = numbers[parent_index];
			numbers[parent_index] = numbers[index];
			numbers[index] = temp;
			buildHeapify(numbers, parent_index);
		}
	}
}
//=====================================================================================
vector<long> BucketSort(vector<long> nums, int max)
{
	int size = nums.size();
	List<long> *hashTable = new List<long>[max];
	
	long maxVal = nums[0];
	for (int i = 1; i < size; i++)
	{
		if (nums[i] > maxVal)
		{
			maxVal = nums[i];
		}
	}
	
	for (int i = 0; i < max; i++)
	{
		hashTable[i].head = NULL;	
	}
	
	for (int i = 0; i < size; i++)
	{
		int index = (nums[i] * max) / (maxVal + 1);
		hashTable[index].insertSorted(nums[i]); 
	}
	
	vector<long> result;
	for (int i = 0; i < max; i++)
	{
		ListItem<long> *ptr = hashTable[i].getHead();
		while (ptr != NULL)
		{
			result.push_back(ptr->value);
			ptr = ptr->next;
		}
	}
	
	return result;
}

#endif
