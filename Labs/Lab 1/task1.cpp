#include <iostream>
using namespace std;

int main()
{
	int n = 0, num = 0, max = -100, min = 100;
	
	while(n < 10)
	{
		cout << "Please enter number " << n + 1 << endl;
		cin >> num;
		
		if ((num <= 100) && (num >= -100))
		{
			if (num > max)
			{
				max = num;
			}
			if (num < min)
			{
				min = num;
			}
			n++;
		}
		else
		{
			cout << "Brother the number you just entered is out of range" << endl;
		}
	}

	cout << "The maximum number is : " << max << endl;
	cout << "The minimum number is : " << min << endl;
	
}
