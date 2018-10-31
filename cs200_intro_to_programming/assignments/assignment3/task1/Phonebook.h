#include <iostream>
#include <vector>

using namespace std;

/* Contact Class */
class Contact
{
	private:
		string Name;
		double Number;
		string Relation;
		int Phonebook_number;
		
	public:
		Contact();
		Contact(string n, double num, string r, int p_num);
		void setName(string n);
		void setNumber(double num);
		void setRelation(string r);
		void setPhonebook(int p_num);
		string getName(void);
		double getNumber(void);
		string getRelation(void);
		int getPhonebook(void);	
		friend ostream& operator <<(ostream& outs, const Contact& temp);
	
};

/* Phonebook Class */
class Phonebook
{
	private:
		string Name;	
		vector <Contact> Contacts;	// vector to store contacts
		int totalContactCount;
	
	public:
		Phonebook();
		Phonebook(string name, vector<Contact>& c, int tot_count);
		int getTotalContacts(void);	
		void AddContact(int p_num);
		void AddContact(const Contact temp);
		void ViewAContact(double num);
		void DeleteAContact(double num);
		void ViewAllContacts(void);
		Contact searchContact(double num);
		friend ostream& operator <<(ostream& outs, const Contact& temp);
		
};


