#include <iostream>
#include "HashC.cpp"
#include "openAddress.cpp"
#include "doubleHash.cpp"
#include "time.h"

using namespace std;

int main()
{
	int A = 0;
	cout << "Please enter the value of A : ";
	cin >> A;
	
	HashC H_chain(A);
	OpenAddress H_openAdd(A);
	
	startTimer();
	H_chain.Load("names.txt");
	stopTimer();
	
	startTimer();
	H_openAdd.Load("names.txt");
	stopTimer();
	string name;
	do 
	{
		cout << "Please enter the name to search the student : ";
		
		cin >> name;
		
		string result;
		
		startTimer();
		ListItem<string>* temp = H_chain.lookup(name);
		cout << "Chaining : " << temp->value;
		stopTimer();
		
		startTimer();
		result = H_openAdd.lookUp(name);
		cout << "Linear Probing : " << result;
		stopTimer();
		
	} while (name != "quit");
	
	
}
