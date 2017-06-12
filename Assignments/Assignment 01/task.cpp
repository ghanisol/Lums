#include "bst.cpp"
#include "avl.cpp"
#include <vector>
#include <fstream>
#include "time.h"

using namespace std;

// prototype
int chooseDS();
int displayMenu();

//	For BST
void run(bst<long>* tree);
void loadTree(bst<long>* tree);
void insertPair(bst<long>* tree);
void searchValue(bst<long>* tree);
void deletePair(bst<long>* tree);
void updateKey(bst<long>* tree);
void currentHeight(bst<long>* tree);

// For AvL
void run(AvL<long>* tree);
void loadTree(AvL<long>* tree);
void insertPair(AvL<long>* tree);
void searchValue(AvL<long>* tree);
void deletePair(AvL<long>* tree);
void updateKey(AvL<long>* tree);
void currentHeight(AvL<long>* tree);

int main()
{
	int DS = chooseDS();
	
	if (DS == 1)
	{
		bst<long>* tree=new bst<long>();
		loadTree(tree);
		run(tree);
	}
	else if (DS == 2)
	{
		AvL<long>* tree = new AvL<long>();
		loadTree(tree);
		run(tree);
	}
}

int chooseDS()
{
	cout << "\nPlease Choose Data Structure\n"
		<< "1) BST\n"
		<< "2) AVL\n\n";
	
	int option = 0;
	cin >> option;
	return option;
}

void loadTree(bst<long>* tree)
{
	cout << "Please enter a filename:\n > ";
	string filename;
	cin >> filename;
	
	ifstream in_file;
	in_file.open(filename.c_str());
	
	if (in_file.fail())
	{
		cout << "Error : Reading file. \n";
		exit(1);
	}
	
	long key;
	string value;
	
	startTimer();	// starts the timer
	
	long count;
	while (!in_file.eof())
	{
		getline(in_file, value, '~');
		in_file >> key;
		tree->insert(value, key);
		count++;
	}
	
	cout << "\nFile loaded successfuly. " << count << " key/value pairs loaded. ";
	
	stopTimer();	// stops the timer
	in_file.close();
}

void loadTree(AvL<long>* tree)
{
	cout << "Please enter a filename:\n > ";
	string filename;
	cin >> filename;
	
	ifstream in_file;
	in_file.open(filename.c_str());
	
	if (in_file.fail())
	{
		cout << "Error : Reading file. \n";
		exit(1);
	}
	
	long key;
	string value;
	
	startTimer();	// starts the timer
	
	long count;
	while (!in_file.eof())
	{
		getline(in_file, value, '~');
		in_file >> key;
		cout << value << endl;
		tree->insert(value, key);
		count++;
	}
	
	cout << "\nFile loaded successfuly. " << count << " key/value pairs loaded. ";
	
	stopTimer();	// stops the timer
	in_file.close();
}

int displayMenu()
{
	cout << "\n\nPress 1 to Insert another key/value Pair\n"
		<< "Press 2 to search for a value using its key\n"
		<< "Press 3 to delete a key/value pair\n"
		<< "Press 4 to update the key of an existing value\n"
		<< "Press 5 go see the current height of the Tree\n";
	
	int option = 0;
	cin >> option;
	return option;
}

void run(bst<long>* tree)
{
	while (true)
	{
		int op = displayMenu();
	
		switch(op)
		{
			case 1:
				insertPair(tree);
				break;
			case 2:
				searchValue(tree);
				break;
			case 3:
				deletePair(tree);
				break;
			case 4:
				updateKey(tree);
				break;
			case 5:
				currentHeight(tree);
				break;
		}
	}
}

void run(AvL<long>* tree)
{
	while (true)
	{
		int op = displayMenu();
	
		switch(op)
		{
			case 1:
				insertPair(tree);
				break;
			case 2:
				searchValue(tree);
				break;
			case 3:
				deletePair(tree);
				break;
			case 4:
				updateKey(tree);
				break;
			case 5:
				currentHeight(tree);
				break;
		}
	}
}

void insertPair(bst<long>* tree)
{
	cout << "\n\nPlease enter the key/value pair for insertion.\n"
		<< "Key : ";
	long key;
	cin >> key;
	cin.get();
	
	cout << "Value : ";
	string value;
	getline(cin, value, '\n');
	
	startTimer();	// starts the timer
	
	tree->insert(value, key);
	
	stopTimer();	// stops the timer
}

void insertPair(AvL<long>* tree)
{
	cout << "\n\nPlease enter the key/value pair for insertion.\n"
		<< "Key : ";
	long key;
	cin >> key;
	cin.get();
	
	cout << "Value : ";
	string value;
	getline(cin, value, '\n');
	
	startTimer();	// starts the timer
	
	tree->insert(value, key);
	
	stopTimer();	// stops the timer
}

void searchValue(bst<long>* tree)
{
	cout << "\nPlease enter the key to search.\n"
		<< "Key : ";
		
	long key;
	cin >> key;
	
	startTimer();	// starts the timer
	
	bst_node<long>* temp = tree->search(key);
	
	stopTimer();	// stops the timer
	
	if (temp != NULL)
	{
		string value = temp->value;
		cout << "\nThe value corresponding to your key is :\n\n";
		cout << value;
	}
	else
	{
		cout << "\nKey does not exist!\n";
	}
	
}

void searchValue(AvL<long>* tree)
{
	cout << "\nPlease enter the key to search.\n"
		<< "Key : ";
		
	long key;
	cin >> key;
	
	startTimer();	// starts the timer
	
	AvLNode<long>* temp = tree->search(key);
	
	stopTimer();	// stops the timer
	
	if (temp != NULL)
	{
		string value = temp->value;
		cout << "\nThe value corresponding to your key is :\n\n";
		cout << value;
	}
	else
	{
		cout << "\nKey does not exist!\n";
	}
}

void deletePair(bst<long>* tree)
{
	cout << "\nPlease enter the key to delete.\n"
		<< "Key : ";
		
	long key;
	cin >> key;
	
	startTimer();	// starts the timer
	
	if (tree->search(key) != NULL)
	{
		tree->delete_node(key);
		cout << "\nKey/Value pair Successfully Deleted.\n\n";
		stopTimer();	// stops the timer
	}
	else
	{
		cout << "\nKey doesn't exist!!\n\n";
	}
}

void deletePair(AvL<long>* tree)
{
	
}

void updateKey(bst<long>* tree)
{
	long old_key;
	long new_key;
	
	cout << "\nPlease enter the keys to update.\n"
		<< "Old Key : ";
	cin >> old_key;
	cout << "New Key : ";
	cin >> new_key;
	
	startTimer();	// start the timer
	
	tree->replace(old_key, new_key);
	
	cout << "\nKey Successfully Replaced!\n\n";
	stopTimer();	// stops the timer
}

void updateKey(AvL<long>* tree)
{
	
}

void currentHeight(bst<long>* tree)
{
	startTimer();	// starts the timer
	
	int h = tree->height(tree->getroot());
	
	cout << "\nThe current height is : " << h << endl << endl;
	stopTimer();	// stops the timer
}

void currentHeight(AvL<long>* tree)
{
	startTimer();	// starts the timer
	
	int h = tree->nodeHeight(tree->getRoot());
	
	cout << "\nThe current height is : " << h << endl << endl;
	stopTimer();	// stops the timer
}
