#include <iostream>
#include <string>

using namespace std;

class timeFM
{

};

int main()
{
 char done = 'y';
 while (done == 'y')
	{
	try
	{
		int hours = 0;
		string  min;
		char useless =0;
		cout << "Enter time in 24-hour notation:\n";
		cin >> hours >> useless >> min;
		int newHours = 0;
		string newMin;
		string time;
		
		if (hours < 0 || hours > 24)
			throw timeFM(); 
		
		if (hours < 13)
		{
			newHours = hours;
			newMin = min;
			time = "AM";
		}
		else
		{
			newHours = hours - 12;
			newMin = min;
			time = "PM";
		}
		cout << "That is the same as\n"
			<< newHours << useless << newMin << " " << time 
			<< endl;
		cout << "Again? (y/n)";
		cin >> done;
		
	}
	catch(timeFM)
	{
		cout << "Time Format Error\n";
	}
 }
}
