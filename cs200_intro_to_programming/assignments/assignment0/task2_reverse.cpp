#include <iostream>

using namespace std;

int reverse (int zip);

int main ()
{
	int zip = 0, reverse_zip = 0, digit = 0;
	
	cout << "Please Enter the Zip Code : ";
	cin >> zip;
	
	reverse_zip = reverse(zip);
	
	while (reverse_zip != 0)
	{
		digit = reverse_zip % 10;
		
		if (digit == 0)
		{
			cout << "||...";
		}
		else if (digit == 1)
		{
			cout << "...||";
		}
		else if (digit == 2)
		{
			cout << "..|.|";
		}
		else if (digit == 3)
		{
			cout << "..||.";
		}
		else if (digit == 4)
		{
			cout << ".|..|";
		}
		else if (digit == 5)
		{
			cout << ".|.|.";
		}
		else if (digit == 6)
		{
			cout << ".||..";
		}
		else if (digit == 7)
		{
			cout << "|...|";
		}
		else if (digit == 8)
		{
			cout << "|..|.";
		}
		else if (digit == 9)
		{
			cout << "|.|..";
		}
			
		reverse_zip /= 10;
	}
	
}


int reverse (int zip)
{
	int reverse = 0;
	
	while (zip != 0)
	{
		reverse = (reverse * 10) + (zip % 10);
		zip /= 10;
	}
	
	return reverse;
}
