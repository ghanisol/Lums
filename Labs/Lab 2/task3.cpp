#include <iostream>

using namespace std;

int main()
{
	int n = 0;
	cout << "Enter the number : ";
	cin >> n;
	cout << endl;
	
	for (int z = 0; z < n; z++)
	{	
		for (int i = 0; i < (z + 1); i++)
		{
			for (int j = 0; j < ((z + 1)-i); j++)
			{
				cout << " ";
			}
			for (int j = 0; j < i + 1; j++)
			{
				cout << "* ";
			}
			cout << endl;
		}
		
		cout << " " << z + 1;
		cout << endl;
	}
}
