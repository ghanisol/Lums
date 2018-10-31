#include <iostream>

using namespace std;

int main()
{
	int year = 0;
	int done = 0;	
	
	while(done == 0)
	{
		do {
			cout << "Please Enter the year : ";
			cin >> year;
			
		}while (year <= 1000 || year >= 3000);
	

		int a = 0;
		a = year - (year % 1000);
		
		if ( a == 1000)
		{
			cout << "M";
		} 
		else 
		{
			cout << "MM";
		}

		year = year - a;
		a = year - (year % 100);
		
		if (a > 500 && a < 1000)
		{
			if (a >= 700)
			{
				for (int i = 1000; i > a; i = i - 100)
				{
					cout << "C";
				}
				cout << "M";
			} 
			else
			{
				cout << "DC";  
			}
		}
		else if (a < 500 && a > 100)
		{
			if (a >= 200)
			{
				for (int i = 500; i > a; i = i - 100)
				{
					cout << "C";
				}
				cout << "D";
			}
			else
			{
				cout << "C";
			}
		}
		else if (a == 500)
		{
			cout << "D";
		}

		year = year - a;
		a = year - (year % 10);
		
		if (a > 50 && a < 100)
		{
			if (a >= 70)
			{
				for (int i = 100; i > a; i = i - 10)
				{	
					cout << "X";
				} 
				cout << "C";
			}
			else
			{
				cout << "LX";
			}
		}	
		else if (a < 50 && a > 10)
		{
			if (a >= 20)
			{
				for (int i = 50; i > a; i = i - 10)
				{
					cout << "X";
				}
				cout << "L";
			}
			else
			{
				cout << "X";
			}
		}
		else if (a == 50)
		{
			cout << "L";
		}
		
		year = year - a;
		a = year;
		
		if (a > 5 && a < 10)
		{
			if (a >= 7)
			{
				for (int i = 10; i > a; i--)
				{
					cout << "I";
				}
				cout << "X";
			}
			else 
			{
				cout << "VI";
			}
		}	
		else if (a < 5 && a > 0)
		{
			if (a >= 2)
			{
				for (int i = 5; i < a; i--)
				{
					cout << "I";
				}
				cout << "V";
			}
			else
			{
				cout << "I";
			}
		}
		else if (a == 5)
		{
			cout << "V";
		}
	}
}

