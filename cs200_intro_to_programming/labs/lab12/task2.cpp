#include <iostream>
#include <string>

using namespace std;

string getMonth(int month);
bool isRight(int day, int month);

class MonthError
{

};

class DayError
{

};

int main()
{
 char done = 'y';
 while (done == 'y')
	{
	try
	{
		int month = 0;
		int day;
		char useless = 0;
		cout << "Enter date in numeric format:\n";
		cin >> month >> useless >> day;
		if (month < 1 || month > 12)
			throw MonthError();
		if (day < 0 || day > 31 || isRight(day, month) == false)
			throw DayError();
			
		
		string newMonth = getMonth(month);

		cout << "That is the same as\n"
			<< newMonth << " " << day << endl;
			
		cout << "Again? (y/n)";
		cin >> done;
		
	}
	catch(MonthError n)
	{
		cout << "Month Error!\n";
	}
	catch(DayError d)
	{
		cout << "Day Error!\n";
	}
 }
}

string getMonth(int month)
{
	if (month == 1)
		return "January";
	else if (month == 2)
		return "Feburary";
	else if (month == 3)
		return "March";
	else if (month == 4)
		return "April";
	else if (month == 5)
		return "May";
	else if (month == 6)
		return "June";
	else if (month == 7)
		return "July";
	else if (month == 8)
		return "Augest";
	else if (month == 9)
		return "September";
	else if (month == 10)
		return "Octobor";
	else if (month == 11)
		return "November";
	else if (month == 12)
		return "December";
}

bool isRight(int day, int month)
{
	if (month == 2)
	{
		if (day < 29)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (month < 8)
	{
		if (month % 2 == 0)
		{
			if (day < 31)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (day < 32)
			{
				return true;
			}
			else 
			{
				return false;
			}
		}
	}
	else 
	{
		if (month % 2 == 0)
		{
			if (day < 32)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (day < 31)
			{
				return true;
			}
			else 
			{
				return false;
			}
		}
	}
}
