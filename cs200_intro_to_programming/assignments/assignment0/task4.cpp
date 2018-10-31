#include <iostream>

using namespace std;

int main()
{
	/*Initialization*/
	char type = 0, initial_1 = 0, final_1 = 0;
	int initial_2 = 0, final_2 = 0;
	
	cout << "Welcome to Chess Mania!!!!\n\n";
	
	//Taking input from the user
	cout << "Enter the type of your piece\n"
		<< "Enter P for Pawn, K for King, Q for Queen, B for Bishop, N for Knight\n";
	cin >> type;
	
	//initial_1 for the character part & initial_2 for the integer part
	cout << "\nEnter the initial Position i.e \"e 6\". Mind the space in between!\n";
	cin >> initial_1 >> initial_2;
	
	//final_1 for the character part & final_2 for the integer part
	cout << "\nEnter the final Position i.e \"f 7\". Mind the space in between!\n";
	cin >> final_1 >> final_2;
	
	//Checking if the user has input the right positions
	if ((initial_1 >= 'a' && initial_1 <= 'h') && (final_1 >= 1 && final_2 <= 8))
	{
		cout << "Initial_1 : " << initial_1 << endl;
		cout << "Initial_2 : " << initial_2 << endl;
		cout << "Final_1 : " << final_1 << endl;
		cout << "Final_2 : " << final_2 << endl;
		cout << "Type : " << type << endl << endl;
		
		// For Pawn
		if (type == 'P')
		{
			if (initial_1 == final_1)
			{
				if ((final_2 > initial_2) && (final_2 - initial_2 == 1))
				{
					cout << "Good move!\n";
				}
				else
				{
					cout << "Tumharey piece se na ho paye ga";
				}
			}
			else
			{
				cout << "Tumharey piece se na ho paye ga";
			}
		}
		// For King
		else if (type == 'K')
		{
			if (initial_1 == final_1)
			{
				if ((final_2 > initial_2) && (final_2 - initial_2 == 1))
				{
					cout << "Good move!\n";
				} 
				else if ((final_2 < initial_2) && (initial_2 - final_2 == 1))
				{
					cout << "Good move!\n";
				}
				else
				{
					cout << "Tumharey piece se na ho paye ga";
				}
			}
			else if ((final_1 - initial_1 == 1) || (initial_1 - final_1 == 1))
			{
				if ((final_2 > initial_2) && (final_2 - initial_2 == 1))
				{
					cout << "Good move!\n";
				}
				else if ((final_2 < initial_2) && (initial_2 - final_2 == 1))
				{
					cout << "Good move!\n";
				}
				else if (final_2 == initial_2)
				{
					cout << "Good move!\n";
				}
				else
				{
					cout << "Tumharey piece se na ho paye ga";
				}
			}
			else
			{
				cout << "Tumharey piece se na ho paye ga";
			}
		}
		// For Queen
		else if (type == 'Q')
		{
			if (initial_1 == final_1)
			{
				if (final_2 != initial_2)
				{
					cout << "Good move!\n";
				}
				else
				{
					cout << "Tumharey piece se na ho paye ga";
				}
			}
			else if (final_1 > initial_1)
			{
				if (final_2 == initial_2)
				{
					cout << "Good move!\n";
				}
				else if (final_2 > initial_2)
				{
					for (int j = initial_2 + 1, i = initial_1 + 1; (i <= 'h') && (j <= 8); i++, j++)
					{
						if ((final_1 == i) && (final_2 == j))
						{
							cout << "Good move\n";
							break;
						}
					}
				}
				else if (final_2 < initial_2)
				{
					for (int j = initial_2 - 1, i = initial_1 + 1; (i <= 'h') && (j >= 1); i++, j--)
					{
						if ((final_1 == i) && (final_2 == j))
						{
							cout << "Good move\n";
							break;
						}
					}
				}
				else
				{
					cout << "Tumharey piece se na ho paye ga";
				}
			}
			else if (final_1 < initial_1)
			{
				if (final_2 == initial_2)
				{
					cout << "Good move!\n";
				}
				else if (final_2 > initial_2)
				{
					for (int j = initial_2 + 1, i = initial_1 - 1; (i >= 'a') && (j <= 8); i--, j++)
					{
						if ((final_1 == i) && (final_2 == j))
						{
							cout << "Good move\n";
							break;
						}
					}
				}
				else if (final_2 < initial_2)
				{
					for (int j = initial_2 - 1, i = initial_1 - 1; (i >= 'a') && (j >= 1); i--, j--)
					{
						if ((final_1 == i) && (final_2 == j))
						{
							cout << "Good move\n";
							break;
						}
					}
				}
				else
				{
					cout << "Tumharey piece se na ho paye ga";
				}		
			}
			else
			{
				cout << "Tumharey piece se na ho paye ga";
			}
		}
		// For Bishop
		else if (type == 'B')
		{
			if (final_1 > initial_1)
			{
				if (final_2 > initial_2)
				{
					for (int j = initial_2 + 1, i = initial_1 + 1; (i <= 'h') && (j <= 8); i++, j++)
					{
						if ((final_1 == i) && (final_2 == j))
						{
							cout << "Good move\n";
							break;
						}
					}
				}
				else if (final_2 < initial_2)
				{
					for (int j = initial_2 - 1, i = initial_1 + 1; (i <= 'h') && (j >= 1); i++, j--)
					{
						if ((final_1 == i) && (final_2 == j))
						{
							cout << "Good move\n";
							break;
						}
					}
				}
				else
				{
					cout << "Tumharey piece se na ho paye ga";
				}
			}
			else if (final_1 < initial_1)
			{
				if (final_2 > initial_2)
				{
					for (int j = initial_2 + 1, i = initial_1 - 1; (i >= 'a') && (j <= 8); i--, j++)
					{
						if ((final_1 == i) && (final_2 == j))
						{
							cout << "Good move\n";
							break;
						}
					}
				}
				else if (final_2 < initial_2)
				{
					for (int j = initial_2 - 1, i = initial_1 - 1; (i >= 'a') && (j >= 1); i--, j--)
					{
						if ((final_1 == i) && (final_2 == j))
						{
							cout << "Good move\n";
							break;
						}
					}
				}
				else
				{
					cout << "Tumharey piece se na ho paye ga";
				}		
			}
			else
			{
				cout << "Tumharey piece se na ho paye ga";
			}	
		}
		// For Knight
		else if (type == 'N')
		{
			if (final_1 > initial_1)
			{
				if ((final_1 - initial_1 == 1) && ((final_2 - initial_2 == 2) || (initial_2 - final_2 == 2)))
				{
					cout << "Good move!\n";
				}
				else if ((final_1 - initial_1 == 2) && ((final_2 - initial_2 == 1) || (initial_2 - final_2 == 1)))
				{
					cout << "Good move!\n";
				}
				else
				{
					cout << "Tumharey piece se na ho paye ga";
				}
			}
			else if (final_1 < initial_1)
			{
				if ((initial_1 - final_1 == 1) && ((final_2 - initial_2 == 2) || (initial_2 - final_2 == 2)))
				{
					cout << "Good move!\n";
				}
				else if ((initial_1 - final_1 == 2) && ((final_2 - initial_2 == 1) || (initial_2 - final_2 == 1)))
				{
					cout << "Good move!\n";
				}
				else
				{
					cout << "Tumharey piece se na ho paye ga";
				}
			}
			else
			{
				cout << "Tumharey piece se na ho paye ga";
			}
		}
		else 
		{
			cout << "What type is this? Bhai kidhr se aye ho? Kon si chess he ye!\n";
		}
	}
	else
	{
		cout << "The details you have entered are incorrect! Kindly enter the correct detail!\n";
	}
	
}
