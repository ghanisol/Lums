#include <iostream>
#include <typeinfo>
#include <vector>
#include "header.cpp"

using namespace std;

// prototype
void displayMenu();
int getOption();
void import(zambeel& Geeks);
void exportFile(zambeel& Geeks);

int main()
{
	zambeel Geeks;
	student* s1 = new student("ghani", "ghani", "CS", 3.0);
	student* s2 = new student("usman", "usman", "CS", 1.9);
	instructor* i1 = new instructor("arif", "arif", "CS");
	course* c1 = new course("Intro to Programming", "CS200", 25, "arif");
	course* c2 = new course("Data Structure", "CS202", 12, "arif");
	Geeks.courses.push_back(c1);
	Geeks.courses.push_back(c2);
	Geeks.users.push_back(s1);
	Geeks.users.push_back(s2);
	Geeks.users.push_back(i1);
	
	while (true)
	{
		displayMenu();
		int option = getOption();
		
		if (option == 1)
		{
			Geeks.signIn();
		}
		else if (option == 2)
		{	
			Geeks.signUp();
		}
		else if (option == 3)
		{
			return 0;
		}
	}
	
}

void displayMenu()
{
	cout << "\n-----------------------------------\n"
		<< "Welcome to Zambeel (Screwing Lives)\n\n"
		<< "1. Sign in\n"
		<< "2. Sign up\n"
		<< "3. Exit\n"
		<< "-----------------------------------\n\n";
}

int getOption()
{
	int temp;
	cin >> temp;
	return temp;
}


