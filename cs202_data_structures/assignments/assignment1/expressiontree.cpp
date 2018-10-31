#include "bst.cpp"

using namespace std;

int main()
{
	cout << "Expression Tree!!" << endl << endl;
	cout << "Please enter the expression in this form -> (3+(4*5)).\n"
		<< "P.S: Mind the brackets in the both ends.\n"
		<< "Enter the expression : ";
	
	string exp;
	getline(cin, exp);
	
	bst<int>* tree=new bst<int>();
	
	tree->buildExpTree(exp);
	
	cout << tree->execute(tree->getroot());
}

