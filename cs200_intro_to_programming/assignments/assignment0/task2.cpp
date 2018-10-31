#include <iostream>

using namespace std;

// prototype
void print_digit (int digit);

int main ()
{
	int zip = 0, digit = 0;
	
	cout << "Please Enter the Zip Code : ";
	cin >> zip;
	int a;
	
	for (int i = 10000; i > 0; i = i/10)
	{
		digit = zip / i;
		print_digit(digit);
		zip = zip % i;
	}
	
}

// function definition
//function to print the bars relative to the digits!
void print_digit (int digit)
{
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
		return;
}
