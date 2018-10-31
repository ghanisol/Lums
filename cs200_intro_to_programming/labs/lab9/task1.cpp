#include <iostream>

using namespace std;

// classes
class cashRegister
{
	private:
		int cashOnHand;
	public:
		cashRegister();
		cashRegister(int c);
		int getCurrentBalance(void);
		void acceptAmount(int c);
		
};

class dispenserType
{
	private:
		int numberOfItems;
		int cost;
	public:
		dispenserType();
		dispenserType(int n, int c);
		int getNoOfItems(void);
		int getCost(void);
		void makeSale(void);	
};

// prototype
void showSelection(void);
void sellProduct(cashRegister& hand, dispenserType& item); 
void printSale(void);

int main()
{
	cashRegister hand(50);
	dispenserType Candy(2, 50), Chips, Gum, Cookies;
	while (true)
	{
		showSelection();
		int item;
		cin >> item;
		if (item == 1)
		{
			sellProduct(hand, Candy);
		}
		else if (item == 2)
		{
			sellProduct(hand, Chips);
		} 
		else if (item == 3)
		{
			sellProduct(hand, Gum);
		}
		else if (item == 4)
		{
			sellProduct(hand, Cookies);
		}
		else
		{
			return 0;
		}
		
	}
	
}


// Class CashRegister
cashRegister::cashRegister() : cashOnHand(500)
{

}

cashRegister::cashRegister(int c)
{
	cashOnHand = c;
}

int cashRegister::getCurrentBalance(void)
{
	return cashOnHand;
}

void cashRegister::acceptAmount(int c)
{
	cashOnHand += c;
}


// Class Dispenser Type
dispenserType::dispenserType(): numberOfItems(50), cost(50)
{
	
}

dispenserType::dispenserType(int n, int c)
{
	numberOfItems = n;
	cost = c;
}

int dispenserType::getNoOfItems(void)
{
	return numberOfItems;
}

int dispenserType::getCost(void)
{
	return cost;
}

void dispenserType::makeSale(void)
{
	numberOfItems--;
}

void showSelection(void)
{
	cout << "*** Welcome to Candy Shop ***\n"
		<< "To select an item, enter\n"
		<< "1 for Candy\n"
		<< "2 for Chips\n"
		<< "3 for Gum\n"
		<< "4 for Cookies\n"
		<< "5 to exit\n";
}

void sellProduct(cashRegister& hand, dispenserType& item)
{
	int cost = item.getCost();
	if (item.getNoOfItems() == 0)
	{
		cout << "Sorry, this item is sold out\n";
	}
	else
	{
		cout << "Please deposit " << cost << " cents\n";
		int cus_hand = 0;
		int d_cash;
		cin >> d_cash;
		cus_hand += d_cash; 	
		while (cus_hand < cost)
		{
			cout << "Please deposit another  "<< cost - cus_hand<< " cents\n";
			cin >> d_cash;
			cus_hand += d_cash; 
		}
		printSale();
		item.makeSale();
		hand.acceptAmount(cost);
		
	}
}

void printSale(void)
{
	cout << "Collect your item at the bottom and enjoy.\n"
		<< "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*\n";
}

