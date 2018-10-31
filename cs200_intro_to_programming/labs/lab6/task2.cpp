#include <iostream>

using namespace std;

// prototype
int jumpit(int* ptrToArray, int total, int size, int i);

int main()
{
	int* ptrToArray;
	ptrToArray = new int[9];
	ptrToArray[0] = 0;
	ptrToArray[1] = 3;
	ptrToArray[2] = 80;
	ptrToArray[3] = 6;
	ptrToArray[4] = 57;
	ptrToArray[5] = 10;
	ptrToArray[6] = 21;
	ptrToArray[7] = 11;
	ptrToArray[8] = 1;
	
	int total = jumpit(ptrToArray, 0, 9, 1);
	cout << total;
	
	
}

int jumpit(int* ptrToArray, int total, int size, int i)
{
	if (i >= size)
	{
		return total; 
	}
	else if (i >= size - 1)
	{
		return total + ptrToArray[1];
	}
	else
	{
		int n1 = ptrToArray[1];
		int n2 = ptrToArray[2];
		
		if (n1 > n2)
		{
			total = total + n2;
			ptrToArray = ptrToArray + 2;
			i = i+2;
			jumpit(ptrToArray, total, size, i);
		}
		else
		{
			total = total + n1;
			ptrToArray++;
			i++;
			jumpit(ptrToArray, total, size, i);
		}
	}
}
