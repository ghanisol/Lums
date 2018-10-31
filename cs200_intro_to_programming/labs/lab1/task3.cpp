#include <iostream>
using namespace std;

int main()
{
	int sub_1 = 0, sub_2 = 0, sub_3 = 0;
	double avg = 0;
	
	cout << "Number in subject 1 : ";
	cin >> sub_1;
	cout << "Number in subject 2 : ";
	cin >> sub_2;
	cout << "Number in subject 3: ";
	cin >> sub_3;
	
	avg = (sub_1 + sub_2 + sub_3) / 3;
	
	if ((sub_1 >= 90) && (sub_2 >= 90) && (sub_3 >= 90))
	{
		cout << "Grade : A" << endl;
	}
	else if (avg > 90)
	{
		cout << "Grade : B" << endl;
	}
	else if (((sub_1 > 70) && (sub_2 > 70) && (sub_3 > 70)) && ((sub_1 >= 80) || (sub_2 >= 80) || (sub_3 >= 80)))
	{
		cout << "Grade : C" << endl;
	}
	else if (((sub_1 < 50) && (sub_2 > 50) && (sub_3 > 50)) || ((sub_1 > 50) && (sub_2 < 50) && (sub_3 > 50)) || ((sub_1 > 50) && (sub_2 > 50) && (sub_3 < 
	50)) && (avg > 60)) 
	{
		cout << "Grade : D" << endl;
	}
	else if (avg > 50)
	{
		cout << "Grade : E" << endl;
	}
	else if (avg < 50)
	{
		cout << "Grade : F" << endl;
	}
	else 
	{
		cout << "Grade : U" << endl;
	}
}
