#include <iostream>

using namespace std;

//prototypes
void printmenu(void);
void markslots(char teacher[4][4], int size);
void printhours(int i);
void printdays(int j);
int main()
{
	int done = 0;
	char anna[4][4];
	char jeff[4][4];
	int option = 0;
	int teacher = 0;
	
	// initialization
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			anna[i][j] = ' ';
			jeff[i][j] = ' ';
		}
	}	
	
	while (done == 0)
	{
	printmenu();
	cin >> option;
	
	if (option == 1)
	{
		cout << "Press 1 for Anna, and 2 for Jeff\n";
		cin >> teacher;
		if (teacher == 1)
		{
			markslots(anna, 4);
		}
		else if (teacher == 2)
		{
			markslots(jeff, 4);
		}
	}
	else if (option == 4)
	{
		cout << "Anna" << endl;
	
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				cout << anna[i][j];
			}
			cout << endl;
		}
		
		cout << endl;
		cout << "Jeff" << endl;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				cout << jeff[i][j];
			}
			cout << endl;
		}
	}
	else if (option == 2)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (anna[i][j] == ' ' || jeff[i][j] == ' ')
				{
					cout << anna[i][j];
				}
			}
			cout << endl;
		}
	}
	else if (option == 3)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
		}
	}
	
	cout << "Press 0 to continue, and 1 for exit" << endl;
	cin >> done;
	}
}


void printmenu(void)
{
	cout << "Please choose from the options below" << endl;
	cout << "1. Mark Slot for Teachers.\n"
		<<"2. Print available slots for single class.\n"
		<<"3. Print available slots for group session.\n"
		<<"4. Print Schedule.\n";	
}

void printdays(int j)
{
	cout << "Day : ";
	if (j == 0)
	{
		cout << "Monday";
	} 
	else if (j == 1)
	{
		cout << "Tuesday";
	}
	else if (j == 2)
	{
		cout << "Wednesday";
	}
	else if (j == 3)
	{
		cout << "Thursday";
	}
	cout << endl;
}

void printhours(int i)
{
	cout << "Hours : ";
	if (i == 0)
	{
		cout << "11-12";
	}
	else if (i == 1)
	{
		cout << "12-1";
	}
	else if (i == 2)
	{
		cout << "1-2";
	}
	else if (i == 3)
	{
		cout << "2-3";
	}
	cout << endl;
}

void markslots(char teacher[4][4], int size)
{
	int busy = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << "Enter the schedule for  the following day : \n";
			cout << "Enter 1 if busy, or 0 if not\n\n";
			printdays(j);
			printhours(i);
			cin >> busy;
			if (busy = 1)
			teacher[i][j] = 'X';
			else
			teacher[i][j] = ' ';
		}
	}

}
