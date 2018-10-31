#include <iostream>
#include <cstring>

using namespace std;

bool isvowel (char a);

int main()
{
	string first;
	string last;
	cout << "Enter the first name : ";
	cin >> first;
	cout << "Enter the last name : ";
	cin >> last;
	
	string newfirst;
	string newlast;
	if (isvowel(first[0]))
	{
		
		newfirst = first + "way" ;
	}
	else
	{	
		char temp = first[0];
		for (int i = 0; i < first.length() - 1; i++)
		{
			first[i] = first[i+1];
		}
	
		first[first.length() - 1] = temp; 
		newfirst = first + "ay";
	}
	
	if (isvowel(last[0]))
	{
		newlast = last + "way"; 
	}
	else
	{
		char temp = last[0];
		for (int i = 0; i < last.length() - 1; i++)
		{
			last[i] = last[i+1];
		}
		
		last[last.length() - 1] = temp;
		newlast = last + "ay";
	}
	
	cout << newfirst << " " << newlast << endl;
	
	
}

bool isvowel (char a)
{
	if (a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u')
	{
		return true;
	}
	else 
	{
		return false;
	}
}
