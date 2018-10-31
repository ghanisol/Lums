#include <iostream>
#include <vector>

using namespace std;

class Person
{
	private:
		string Name;
		string password;
		string username;
		bool isAdmin;
		int Age;
		
	public:	
		vector <Person> friends;
		vector <Person> friendRequestSent;
		Person();
		Person(string n, string user, string pass, int age);
		void setName(string n);
		void setPassword(string pass);
		void setUsername(string user);
		void setisAdmin(bool is_ad);
		void setAge(int a);
		string getName();
		string getPassword();
		string getUsername();
		bool getisAdmin();
		int getAge();
		void viewAllFriends(void);
		void viewFriendRequestsSent(void);
		friend ostream& operator <<(ostream& outs, const Person& temp);
		friend bool isFriend(Person& temp1, Person& temp2);
		friend void mutualFriends(Person& temp1, Person& temp2);
};

class Facebook
{
	private:
		vector <Person> members;
		
	public:
		Facebook();
		void signIn(void);
		void signUp(void);
		void adminMenu(void);
		void adminMenu(Person& temp);
		void userMenu(Person& temp);
		void viewAllMembers(void);
		void deleteMember(void);
		void makeAdmin(void);
		void addAFriend(Person& _person);
		int isAMember(string username);
		void viewAFriend(Person& temp);
		friend ostream& operator <<(ostream& outs, const Person& temp);
		friend void import(Facebook& BookOfLife);
		friend void exportFile(Facebook& BookOfLife);
		Person getPerson(string user);
		friend bool isFriend(Person& temp1, Person& temp2);
		friend void mutualFriends(Person& temp1, Person& temp2);
};

