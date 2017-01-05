#include <iostream>
#include <string>

using namespace std;

int main()
{
	string a;
	cout << "Please enter the whatever :" << endl;
	cin >> a;
	
	for (int i = 0, j =a.length()-1; i < a.length(); i++, j--)
	{
		for (int z = 0; z < a.length(); z++)
		{
			if (z == i)
			{
				cout << " ";
			}
			else if (z == j)
			{
				cout << " ";
			}
			else 
			{
				cout << a[z];
			}
		}
		cout << endl;
	}
}
