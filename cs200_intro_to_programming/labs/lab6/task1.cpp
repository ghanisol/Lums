#include <iostream>
#include <cstdlib>

using namespace std;

// prototype
int* create2DArray(int rows, int columns);
void set(int *arr, int rows, int columns, int desired_row, int desired_column, int val);
int get(int *arr, int rows, int columns, int desired_row, int desired_column);

int main()
{
	int rows = 2, columns = 3;
	int* ptrToArray = create2DArray(rows, columns);
	set(ptrToArray, rows, columns, 2, 1, 4);
	cout << get(ptrToArray, rows, columns, 4, 1);
	
}

int* create2DArray(int rows, int columns)
{
	int* ptrToArray;
	ptrToArray = new int[rows*columns];
	return ptrToArray;
}

void set(int *arr, int rows, int columns, int desired_row, int desired_column, int val)
{
	if (desired_row > rows || desired_column > columns)
	{
		cout << "The indexes you gave are invalid" << endl;
		exit(1);
	}
	
	int index = (desired_row - 1) * columns + (desired_column - 1);
	arr[index] = val;
}

int get(int *arr, int rows, int columns, int desired_row, int desired_column)
{
	if (desired_row > rows || desired_column > columns)
	{
		cout << "The indexes you gave are invalid" << endl;
		exit(1);
	}
	int index = (desired_row - 1) * columns + (desired_column - 1);
	return arr[index];
}
