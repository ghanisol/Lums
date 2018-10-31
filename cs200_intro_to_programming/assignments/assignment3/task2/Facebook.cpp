#include <iostream>
#include <vector>
#include <conio.h>
#include <fstream>
#include "Facebook.h"

using namespace std;

// prototype
void DisplayMenu(void);
int getOption(void);
void import(Facebook& BookOfLife);
void exportFile(Facebook& BookOfLife);

int main()
{
	Facebook BookOfLife;
	import (BookOfLife);
	while (true)
	{
		DisplayMenu();
		int option = getOption();
		
		if (option == 1)
		{
			BookOfLife.signIn();
		}
		else if (option == 2)
		{	
			BookOfLife.signUp();
		}
		else if (option == 3)
		{
			exportFile(BookOfLife);
			return 0;
		}
	}
}

/* Main Function */
void DisplayMenu(void)
{
	cout << "\n-----------------------------------\n"
		<< "Welcome to Facebook (Changing Lives)\n\n"
		<< "1. Sign in\n"
		<< "2. Sign up\n"
		<< "3. Exit\n"
		<< "-----------------------------------\n\n";
}

int getOption(void)
{
	int temp;
	cin >> temp;
	return temp;	
}

ostream& operator <<(ostream& outs, const Person& temp)
{	
	outs << "\nName = " << temp.Name
		 << "\nUsername = " << temp.username
		 << "\nAge = " << temp.Age;
		 
	return outs;
}

bool isFriend(Person& temp1, Person& temp2)
{
	for (int i = 0; i < temp1.friends.size(); i++)
	{
		if (temp2.getUsername() == temp1.friends[i].getUsername())
		{
			return true;
		}
	}
	return false;
}

void mutualFriends(Person& temp1, Person& temp2)
{
	for (int i = 0; i < temp1.friends.size(); i++ )
	{
		if (isFriend(temp2, temp1.friends[i]))
		{
			cout << temp1.friends[i] << endl << endl;
		}
	}
	return;
}

void import(Facebook& BookOfLife)
{
	ifstream file_members;
	file_members.open("members.txt");
	int i = 0;
	while (!file_members.eof())
	{
		Person temp;
		string line;
		int age;
		bool is_ad;
	
		file_members >> line;
		temp.setName(line);
		
		file_members >> line;
		temp.setUsername(line);
		
		file_members >> line;
		temp.setPassword(line);
		
		file_members >> age;
		temp.setAge(age);
		
		file_members >> is_ad;
		temp.setisAdmin(is_ad);
		
		BookOfLife.members.push_back(temp);
		i++;
	}
	file_members.close();
	
	ifstream file_friends;
	file_friends.open("friends.txt");
	int j = 0;
	string line;
	file_friends >> line;
	while (!file_friends.eof())
	{
		string user = line;
		file_friends >> line;
		while (line != "*")
		{
			Person temp = BookOfLife.getPerson(line);
			BookOfLife.members[j].friends.push_back(temp);
			file_friends >> line;
		}
		j++;
		file_friends >> line;
	}
	file_friends.close();
}

void exportFile(Facebook& BookOfLife)
{
	ofstream file_members;
	file_members.open("members.txt");
	
	for (int i = 0; i < BookOfLife.members.size(); i++)
	{
		file_members << BookOfLife.members[i].getName() << endl;
		file_members << BookOfLife.members[i].getUsername() << endl;
		file_members << BookOfLife.members[i].getPassword() << endl;
		file_members << BookOfLife.members[i].getAge() << endl;
		file_members << BookOfLife.members[i].getisAdmin() << endl;
		file_members << endl;
	}
	
	file_members.close();
	
	ofstream file_friends;
	file_friends.open("friends.txt");
	
	for (int i = 0; i < BookOfLife.members.size(); i++)
	{
		file_friends << BookOfLife.members[i].getUsername() << endl;
		for (int j = 0; j < BookOfLife.members[i].friends.size(); j++)
		{
			file_friends << BookOfLife.members[i].friends[j].getUsername() << endl;
		}
		file_friends << "*" << endl;
	}
	
	file_friends.close();
}

/* Person's Class Member Functions */

Person::Person()
{
	
}

Person::Person(string n, string user, string pass, int age)
{
	Name = n;
	username = user;
	password = pass;
	isAdmin = false;
	Age = age;
}

void Person::setName(string n)
{
	Name = n;
	return;
}

void Person::setPassword(string pass)
{
	password = pass;
	return;	
}

void Person::setUsername(string user)
{
	username = user;
}

void Person::setisAdmin(bool is_ad)
{
	isAdmin = is_ad;
	return;
}

void Person::setAge(int a)
{
	Age = a;
	return;
}

string Person::getName()
{
	return Name;
}

string Person::getPassword()
{
	return password;
}

string Person::getUsername()
{
	return username;
}

bool Person::getisAdmin()
{
	return isAdmin;
}

int Person::getAge()
{
	return Age;
}

void Person::viewAllFriends(void)
{
	for (int i = 0; i < friends.size(); i++)
	{
		cout << friends[i] << endl;
	}
	return;
}

void Facebook::addAFriend(Person& _person)
{
	string user;
	bool isMember = false;
	cout << "\nUsername : ";
	cin >> user;
	int temp = isAMember(user);
	
	if (temp != -1 && members[temp].getUsername() != _person.getUsername())
	{
		for (int i = 0; i < members[temp].friendRequestSent.size(); i++)
		{
			if (_person.getUsername() == members[temp].friendRequestSent[i].getUsername())
			{
				_person.friends.push_back(members[temp]);
				members[temp].friends.push_back(_person);
				members[temp].friendRequestSent.erase(members[temp].friendRequestSent.begin() + i);
				cout << "\nFriend Added!\n\n";
				isMember = true;
			}
		}
		
		if (isMember == false)
		{
			_person.friendRequestSent.push_back(members[temp]);
			cout << "\nFriend Request Sent\n\n";
				
		}
		return;
	}
	else
	{
		cout << "\nMember Not Found!\n";
		return;
	}
}

void Facebook::viewAFriend(Person& temp)
{
	string user;
	bool isMember = false;
	cout << "\nUsername : ";
	cin >> user;

	for (int i = 0; i < temp.friends.size(); i++)
	{
		if (user == temp.friends[i].getUsername())
		{
			cout << temp.friends[i] << endl;
			cout << "\nMutual Friends\n\n";
			mutualFriends(temp, temp.friends[i]);
			cout << "\n\nFriends\n\n";
			temp.friends[i].viewAllFriends();
			isMember = true;
			break;
		}
	}
	
	if (isMember == false)
	{
		cout << "\nFriend Not Found!\n\n";
	}
	return;
}
	
void Person::viewFriendRequestsSent(void)
{
	
	for (int i = 0; i < friendRequestSent.size(); i++)
	{
		cout << friendRequestSent[i] << endl << endl;
	}
	
	return;
}
		
/* Facebook's Class Member Functions */

Facebook::Facebook()
{
	
}

void Facebook::signIn(void)
{
	//clrscr();
	string user;
	string pass;
	cout << "\n*******************\n"
		<< "Login Screen\n"
		<< "*******************\n\n";
	cout << "\nUsername : ";
	cin >> user;
	cout << "Password : ";
	cin >> pass;
	if (user == "admin" && pass == "rider007")
	{
		adminMenu();
		return;	
	}
	
	for (int i = 0; i < members.size(); i++)
	{
		if (members[i].getUsername() == user && members[i].getPassword() == pass)
		{
			if (members[i].getisAdmin() == true)
			{
				adminMenu(members[i]);
				return;
			}
			else
			{
				userMenu(members[i]);
				return;
			}
			break;
		}
	}
	
	cout << "\nUsername or Password is invalid\n";
	return;
	
}

void Facebook::signUp(void)
{
	//clrscr();
	string name;
	string user;
	string pass;
	int age;
	bool isUnique = true;
	
	cout << "\n*******************\n"
		<< "SignUp Screen\n"
		<< "*******************\n\n";
	do
	{
		cout << "\nName : ";
		cin >> name;
		cout << "Username : ";
		cin >> user;
		cout << "Password : ";
		cin >> pass;
		cout << "Age : ";
		cin >> age;
		
		for (int i = 0; i < members.size(); i++)
		{
			if (members[i].getUsername() == user)
			{
				isUnique = false;
				cout << "\n\n Username Already Exists \n\n";
				break;
			}
		}
		
	} while (isUnique == false);
	
	Person temp(name, user, pass, age);
	members.push_back(temp);
	return;
	
}

void Facebook::adminMenu(void)
{
	cout << "\n*******************\n"
		<< "Admin Area\n"
		<< "*******************\n\n";
	
	while (true)
	{
		cout << "\n1. View All Member\n"
			<< "2. Delete A Member\n"
			<< "3. Make Another Admin\n"
			<< "4. Logout\n\n";
		
		int option;
		cin >> option;
		
		if (option == 1)
		{
			viewAllMembers();
		}
		else if (option == 2)
		{
			deleteMember();
		}
		else if (option == 3)
		{
			makeAdmin();
		}
		else if (option == 4)
		{
			return;
		}
		else 
		{
			cout << "\nInvalid Option\n\n";
		}
	}
}

void Facebook::adminMenu(Person& temp)
{
	cout << "\n*******************\n"
		<< "Welcome " << temp.getName() << " | Admin Area\n"
		<< "*******************\n\n";
	
	while (true)
	{
		cout << "\n1. View All Member\n"
			<< "2. Delete A Member\n"
			<< "3. Make Another Admin\n"
			<< "4. View All Friends\n"
			<< "5. Add A Friend\n"
			<< "6. View A Friend\n"
			<< "7. View Friend Requests Sent\n"
			<< "8. Logout\n\n";
		
		int option;
		cin >> option;
		
		if (option == 1)
		{
			viewAllMembers();
		}
		else if (option == 2)
		{
			deleteMember();
		}
		else if (option == 3)
		{
			makeAdmin();
		}
		else if (option == 4)
		{
			temp.viewAllFriends();
		}
		else if (option == 5)
		{
			addAFriend(temp);
		}
		else if (option == 6)
		{
			viewAFriend(temp);
		}
		else if (option == 7)
		{
			temp.viewFriendRequestsSent();
		}
		else if (option == 8)
		{
			return;
		}
		else 
		{
			cout << "\nInvalid Option\n\n";
		}
	}
	
}

void Facebook::userMenu(Person& temp)
{
	cout << "\n*******************\n"
		<< "Welcome " << temp.getName() << endl 
		<< "*******************\n\n";
	
	while (true)
	{
		cout << "\n1. View All Friends\n"
			<< "2. Add A Friend\n"
			<< "3. View A Friend\n"
			<< "4. View Friend Requests Sent\n"
			<< "5. View All Members on the Book Of Life\n"
			<< "6. Logout\n\n";
		
		int option;
		cin >> option;
		
		if (option == 1)
		{
			temp.viewAllFriends();
		}
		else if (option == 2)
		{
			addAFriend(temp);
		}
		else if (option == 3)
		{
			viewAFriend(temp);
		}
		else if (option == 4)
		{
			temp.viewFriendRequestsSent();
		}
		else if (option == 5)
		{
			viewAllMembers();
		}
		else if (option == 6)
		{
			return;
		}
		else 
		{
			cout << "\nInvalid Option\n\n";
		}
	}
}

void Facebook::viewAllMembers(void)
{
	for (int i = 0; i < members.size(); i++)
	{
		cout << members[i] << endl << endl;
	}
	return;
}

void Facebook::deleteMember(void)
{
	string user;
	bool isMember = false;
	cout << "\nUsername : ";
	cin >> user;
	
	for (int i = 0; i < members.size(); i++)
	{
		if (members[i].getUsername() == user)
		{
			members.erase(members.begin() + i);
			isMember = true;
			break;
		}
	}
	
	if (isMember == false)
	{
		cout << "\nMember Not Found!\n\n";
	}
	return;
}

void Facebook::makeAdmin(void)
{
	string user;
	bool isMember = false;
	cout << "\nUsername : ";
	cin >> user;
	
	for (int i = 0; i < members.size(); i++)
	{
		if (members[i].getUsername() == user)
		{
			members[i].setisAdmin(true);
			isMember = true;
			break;
		}
	}
	
	if (isMember == false)
	{
		cout << "\nMember Not Found!\n\n";
	}
	return;
	
}

int Facebook::isAMember(string username)
{
	for (int i = 0; i < members.size(); i++)
	{
		if (members[i].getUsername() == username)
		{
			return i;
			break;
		}
	}
	
	return -1;
}

Person Facebook::getPerson(string user)
{
	for (int i = 0; i < members.size(); i++)
	{
		if (members[i].getUsername() == user)
		{
			return members[i];
		}
	}
}
