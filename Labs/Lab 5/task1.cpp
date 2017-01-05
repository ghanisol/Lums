#include <iostream>


using namespace std;

//prototype
string* addEntry(string* dynamicArray, int &size, string newEntry, int position);
string* deleteEntry(string* dynamicArray, int &size, string entryToDelete);
string* reverseArray(string* dynamicArray, int size);
void display(string* dynamicArray, int size);

int main()
{
	int array_size = 5;
	string* name_array;
	name_array = new string[array_size];
	name_array[0] = "Ghani";
	name_array[1] = "Faizan";
	name_array[2] = "Hamza";
	name_array[3] = "Talha";
	name_array[4] = "Mohsin";
	
	cout << "Add Entry" << endl;
	name_array = addEntry(name_array, array_size, "Hashaam", 2);
	display(name_array, array_size);
	
	cout << "Delete Entry" << endl;
	name_array = deleteEntry(name_array, array_size, "Hamza");
	display(name_array, array_size);
	
	cout << "Reverse" << endl;
	name_array = reverseArray(name_array, array_size);
	display(name_array, array_size);
	
	

}

string* addEntry(string* dynamicArray, int &size, string newEntry, int position)
{
	
	size++;
	string* new_array;
	new_array = new string[size];
	
	for (int i = 0, j = 0; i < size; i++)
	{
		if (i == position)
		{
			new_array[i] = newEntry;
		}
		else
		{
			new_array[i] = dynamicArray[j];
			j++;
		} 
	}
	delete[] dynamicArray;
	return new_array;
}

string* deleteEntry(string* dynamicArray, int &size, string entryToDelete)
{
	int pos = 0;
	
	for (int i = 0; i < size; i++)
	{
		if (dynamicArray[i] == entryToDelete)
		{
			pos = i;
		}
	}
	
	if (pos != 0)
	{
		size--;
		string *new_array;
		new_array = new string[size];
		
		for (int i = 0, j = 0; j < size + 1; j++)
		{
			if (j != pos)
			{
				new_array[i] = dynamicArray[j];
				i++;
			}
		} 
		delete[] dynamicArray;
		return new_array;
	}
	else
	{
		return dynamicArray;
	}
}

string* reverseArray(string* dynamicArray, int size)
{
	for (int i = 0, j = size - 1; i < j; i++, j--)
	{
		string temp = *(dynamicArray + i);
		*(dynamicArray + i) = *(dynamicArray + j);
		*(dynamicArray + j) = temp;
	}
	return dynamicArray;
}

void display(string* dynamicArray, int size)
{
	cout << "Names:" << endl;
	for (int i = 0; i < size; i++)
	{
		cout << dynamicArray[i] << endl;
	}
}

