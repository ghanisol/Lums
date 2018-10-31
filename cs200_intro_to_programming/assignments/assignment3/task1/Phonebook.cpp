#include <iostream>
#include <vector>
#include "Phonebook.h"

using namespace std;

// prototype
void DisplayMenu(void);
int selectPhonebook(void);
double enterNumber(void);
int main()
{
	Phonebook office, home;

	while (true)
	{	
		DisplayMenu();
		int option;
		cin >> option;
		if (option == 1)
		{
			int p_book = selectPhonebook();
			if (p_book == 1)
			{
				office.AddContact(p_book);
			}
			else if (p_book == 2)
			{
				home.AddContact(p_book);
			}
			else
			{
				cout << "Error : Wrong Phonebook!\n";
				continue;
			}
		}
		else if (option == 2)
		{
			int p_book = selectPhonebook();
			int s_num = enterNumber();
			if (p_book == 1)
			{
				office.ViewAContact(s_num);
			}
			else if (p_book == 2)
			{
				home.ViewAContact(s_num);
			}
			else
			{
				cout << "Error : Wrong Phonebook!\n";
				continue;
			}
		}
		else if (option == 3)
		{
			int p_book = selectPhonebook();
			int s_num = enterNumber();
			if (p_book == 1)
			{
				office.DeleteAContact(s_num);
			}
			else if (p_book == 2)
			{
				home.DeleteAContact(s_num);
			}
			else
			{
				cout << "Error : Wrong Phonebook!\n";
				continue;
			}
		}
		else if (option == 4)
		{
			cout << "\n\nPhonebook -> Office\n\n";
			office.ViewAllContacts();
			cout << "\n\nPhonebook -> Home\n\n";
			home.ViewAllContacts();
		}
		else if (option == 5)
		{
			int p_book = selectPhonebook();
			if (p_book == 1)
			{
				cout << office.getTotalContacts() << endl;
			}
			else if (p_book == 2)
			{
				cout << home.getTotalContacts() << endl;
			}
			else
			{
				cout << "Error : Wrong Phonebook!\n";
				continue;
			}	
		}
		else if (option == 6)
		{
			int p_book = selectPhonebook();
			int s_num = enterNumber();
			if (p_book == 1)
			{
				Contact temp = office.searchContact(s_num);
				temp.setPhonebook(2);
				home.AddContact(temp);
					
			}
			else if (p_book == 2)
			{
				Contact temp = home.searchContact(s_num);
				temp.setPhonebook(1);
				office.AddContact(temp);
			}
		}
		else if (option == 7)
		{
			return 0;
		}
		else
		{
			cout << "\nWrong Option Selected! Try Again\n";
			continue;
		}
	}
}


/* Contact Class's Member Functions */

Contact::Contact()
{
	
}
  
Contact::Contact(string n, double num, string r, int p_num)
{
	Name = n;
	Number = num;
	Relation = r;
	Phonebook_number = p_num;
}

void Contact::setName(string n)
{
	Name = n;
	return;	
}

void Contact::setNumber(double num)
{
	Number = num;
	return;	
}

void Contact::setRelation(string r)
{
	Relation = r;
	return;
}

void Contact::setPhonebook(int p_num)
{
	Phonebook_number = p_num;
	return;
}

string Contact::getName(void)
{
	return Name;
}

double Contact::getNumber(void)
{
	return Number;
}

string Contact::getRelation(void)
{
	return Relation;
}

int Contact::getPhonebook(void)
{
	return Phonebook_number;
}

/* Phonebook Class's Member Functions */

Phonebook::Phonebook(): totalContactCount(0)
{
	
}

Phonebook::Phonebook(string name, vector<Contact>& c, int tot_count)
{
	Name = name;
	Contacts = c;
	totalContactCount = tot_count;
}

int Phonebook::getTotalContacts(void)
{
	return totalContactCount;	
}

void Phonebook::AddContact(int p_num)
{
	string name;
	double num;
	string rel;
	cout << "\nPlease enter Contact Details.\n"
		<< "Please enter the Name : ";
	cin >> name;
	cout << "Please enter the Number : ";
	cin >> num;
	cout << "Please enter the Relation : ";
	cin >> rel;
	Contact temp(name, num, rel, p_num);
	Contacts.push_back(temp);
	totalContactCount++;	
}

void Phonebook::ViewAContact(double num)
{
	for (int i = 0; i < totalContactCount; i++)
	{
		if (num == Contacts[i].getNumber())
		{
			cout << Contacts[i] << endl;
			break;
		}
	}
	return;
}

void Phonebook::DeleteAContact(double num)
{
	for (int i = 0; i < totalContactCount; i++)
	{
		if (num == Contacts[i].getNumber())
		{
			Contacts.erase(Contacts.begin() + i);
			totalContactCount--;
			return;
		}
	}
	cout << "Not Found\n\n";
	return;
}

void Phonebook::ViewAllContacts(void)
{
	for (int i = 0; i < totalContactCount; i++)
	{
		cout << i << endl;
		cout << Contacts[i] << endl << endl;
	}
	return;
}

Contact Phonebook::searchContact(double num)
{
	for (int i = 0; i < totalContactCount; i++)
	{
		if (num == Contacts[i].getNumber())
		{
			return Contacts[i];
		}
	}
}

void Phonebook::AddContact(const Contact temp)
{
	Contacts.push_back(temp);
	totalContactCount++;
}


/* Main Function */
void DisplayMenu(void)
{
	cout << "Select the desired option\n"
		<< "1. Add a new contact.\n"
		<< "2. View a contact.\n"
		<< "3. Delete all contacts.\n"
		<< "4. View all contacts.\n"
		<< "5. View the number of contacts in the phonebook.\n"
		<< "6. Clone a Contact\n"
		<< "7. Exit the system.\n";
}

int selectPhonebook(void)
{
	cout << "Select the PhoneBook.\n"
		<< "Enter 1 for Office, Enter 2 for Home.\n";
	int p_num;
	cin >> p_num;
	return p_num;
}

double enterNumber(void)
{
	cout << "Enter the Number : ";
	double num;
	cin >> num;
	return num;
}

ostream& operator <<(ostream& outs, const Contact& temp)
{	
	outs << "Name = " << temp.Name
		 << "\nNumber = " << temp.Number
		 << "\nRelation = " << temp.Relation
		 << "\nPhonebook No. = " << temp.Phonebook_number << endl;
	
	return outs;
}
