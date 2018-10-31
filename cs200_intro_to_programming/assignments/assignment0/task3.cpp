#include <iostream>

using namespace std;

int main()
{
	int n = 0;
	cout << "Enter the number : ";
	cin >> n;
	cout << endl;
		
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < (n-i); j++)
		{
			cout << " ";
		}
		for (int j = 0; j < i + 1; j++)
		{
			cout << "* ";
		}
		cout << endl;
	}
	
	for (int i = n - 1 ; i >= 0; i--)
	{
		for (int j = 0; j < (n-i); j++)
		{
			cout << " ";
		}
		for (int j = 0; j < i + 1; j++)
		{
			cout << "* ";
		}
		cout << endl;
	}
		
		
}
