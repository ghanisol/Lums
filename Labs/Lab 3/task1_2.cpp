#include <iostream>
#include <string>

using namespace std;

int main()
{
	string name = "Faizan";
	int length = name.length();
	int i = 0;
	char l = 0;
	while (i <= length)
	{
		cout << "Enter the letter\n";
		cin >> l;
		
		if (l == name[i])
		{
			cout << "The " << i << "number is :" << l << endl;
			i++;
		} 
	}
	
}
