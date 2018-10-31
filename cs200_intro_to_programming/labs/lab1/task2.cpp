#include <iostream>
using namespace std;

int main()
{
	int num = 0, i = 1, sum = 0;
	
	cout << "Please enter the number" << endl;
	cin >> num;
	
	while (i <= num)
	{
		sum = sum + i;
		i = i + 2;
	}
	
	cout << "Sum : " << sum << endl;
}
