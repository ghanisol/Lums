#include <iostream>

using namespace std;

int main()
{
	/*Initialization*/
	int quantity = 0, price = 0, total_expense = 0, discount = 0, c = 1;
	
	/*Loop until the user don't want to continue*/
	while (c != 0)
	{
		cout << "Please Enter the Quantity and Price per Item. \n";
		cout << "Quantity: ";
		cin >> quantity;
		cout << "Price: ";
		cin >> price;
		
		total_expense = total_expense + (price * quantity);
		
		/*Check if the user is eligible for a discount*/
		if (total_expense > 5000)
		{
			discount = total_expense * 0.1;
			cout << "\nCongrats!!! You got a 10% discount on your shopping.\n";
			cout << "\nTotal Expense : " << total_expense - discount << endl;
		}
		else 
		{
			cout << "\nTotal Expense : " << total_expense << endl;
			cout << "\nGet a 10% discount on spending more than 5000 bucks.\n";
		}
		
		cout << "\nDo you want to buy more items?\n"
			<<"\nEnter 1 to continue shopping, or enter 0 if you are done!\n";
		cin >> c;
		
	}
	
	cout << endl << "Thank You for shopping with us. Take Care!\n";
	
}
