#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

struct CARD {
	int number;
	int suit;
};

// prototype
string card(int i, int j);
void CreateDeck(CARD deck[]);
void ShuffleDeck(CARD deck[], int deck_size);
void DealCards(CARD player1[], CARD computer[], CARD deck[]);
void print_player_cards(CARD player[], int player_size);
void remove_cards(CARD player[], int& player_size);
void player_won(void);
void player_lost(void);
void start(CARD player1[], int& player1_size, CARD computer[], int& computer_size);
void player_turn(CARD player1[], int& player_size, CARD computer[], int& computer_size);
void computer_turn(CARD player[], int& player_size, CARD computer[], int& computer_size);

int main()
{
	int done = 0;
	do
	{
		CARD deck[51];
		
		CreateDeck(deck); 
		ShuffleDeck(deck, 51);
			
		CARD player1[26];
		int player1_size = 26;
		
		CARD computer[25];
		int computer_size = 25;
		
		DealCards(player1, computer, deck);
		
		start(player1, player1_size, computer, computer_size);

		while(true)
		{
			
			player_turn(player1, player1_size, computer, computer_size);
			
			if (player1_size == 0)
			{	
				player_won();
				break;
			}
			else if (computer_size == 0)
			{
				player_lost();
				break;
			}
			
			computer_turn(player1, player1_size, computer, computer_size);
			
			if (player1_size == 0)
			{	
				player_won();
				break;
			}
			else if (computer_size == 0)
			{
				player_lost();
				break;
			}
		}
		
		cout << "Do you want to play again? \n";
		cout << "Enter 0 to continue, and 1 to exit...\n";
		cin >> done;
	} while (done == 0);
	
	
}


void start(CARD player1[], int& player1_size, CARD computer[], int& computer_size)
{
	// Start of the Game
		cout << "Let's Play Old Maid !\n\n"
		<< "Your instructions go here\n"
		<< "\t .\n"
		<< "\t .\n"
		<< "\t .\n\n";
		
		cout << "You were dealt : \n\n";
		print_player_cards(player1, player1_size);
		cout << endl;
		
		cout << "Discarding your pairs : \n";
		remove_cards(player1, player1_size);
		if (player1_size > 1)
		{
			ShuffleDeck(player1, player1_size);
		}
		
		cout << "Here is your hand : \n";
		print_player_cards(player1, player1_size);
		cout << endl;
		
		cout << "I'm discarding my pairs :\n";
		remove_cards(computer, computer_size);
		if (computer_size > 1)
		{
		ShuffleDeck(computer, computer_size);
		}
}

// Removes the pairs
void remove_cards(CARD player[], int& player_size)
{
	for (int i = 0; i < player_size - 1; i++)
	{
		for (int j = i+1; j < player_size; j++)
		{
			if (player[i].number == player[j].number)
			{
				cout << "Removing a pair: ";
				cout << card(player[i].number, player[i].suit) << endl;
				cout << card(player[j].number, player[j].suit) << endl << endl;
				player[j] = player[player_size - 1];
				player_size--;
				player[i] = player[player_size - 1];
				player_size--;
				i = 0;
				break;
			}
		}
	}	
	
}

// Deals the cards
void DealCards(CARD player1[], CARD computer[], CARD deck[])
{
	int x = 0, y = 0;
	for (int i = 0; i < 51;)
	{
		player1[x].number = deck[i].number;
		player1[x].suit = deck[i].suit;
		x++;
		i++;
		if(i < 51)
		{
			computer[y].number = deck[i].number;
			computer[y].suit = deck[i].suit;
			y++;
			i++;
		}
		
	}
}

// Creates the deck
void CreateDeck(CARD deck[])
{
	int z = 0;
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < ((i == 11) ? 3 : 4); j++)
		{
			deck[z].number = i;
			deck[z].suit = j;	
			z++;
		}	
	}	
}

// Shuffles the deck
void ShuffleDeck(CARD deck[], int deck_size)
{
	for (int i = 0; i < deck_size; i++)
	{
		srand(time(NULL) * i);
		int r = rand() % (deck_size - 1);
		if (r != i)
		{
			CARD temp = deck[i];
			deck[i] = deck[r];
			deck[r] = temp;
		}
	}
}

// Player Turn
void player_turn(CARD player[], int& player_size, CARD computer[], int& computer_size)
{
	cout << "\nI have " << computer_size << " cards.\n"
		<< "Which one do you choose ?\n"
		<< "Enter a number between 1 and " << computer_size << " : ";
			
	int r = 0;
	cin >> r;
	r = r - 1;
	
	player[player_size] = computer[r];
	player_size++;
	
	computer[r] = computer[computer_size - 1];
	computer_size--;
	
	remove_cards(player, player_size);
	if (player_size > 1)
	{
		ShuffleDeck(player, player_size);
	}
}

// Computer Turn
void computer_turn(CARD player[], int& player_size, CARD computer[], int& computer_size)
{
	cout << "You have : \n";
	print_player_cards(player, player_size);
	int random = 0;
	if (player_size == 1)
	{
		random = 0;
	}
	else
	{
		random = rand() % (player_size - 1);
	}
	
	cout << "\nI'll take card # " << random + 1 << endl;
	
	computer[computer_size] = player[random];
	computer_size++;
	
	player[random] = player[player_size - 1]; 
	player_size--;
	
	remove_cards(computer, computer_size);
	if (computer_size > 1)
	{
		ShuffleDeck(computer, computer_size);
	}
	cout << endl;
}
// Prints the cards for a given player
void print_player_cards(CARD player[], int player_size)
{
	for (int i = 0; i < player_size; i++)
	{
		cout << card(player[i].number, player[i].suit) << endl;
	}
}

// Simulates the Cards
string card(int i, int j)
{
	
	string number[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
	string suit[] = {"Spades", "Hearts", "Diamond", "Clubs"};
	string card = number[i] + " of " + suit[j];
	return card;
}

void player_won(void)
{
	cout << "Shit! I lost! Well i still got the queen though ;)\n\n";
}

void player_lost(void)
{
	cout << "Hahahaha Hahahaha Hahahaha, you took the queen, but still lost :p\n\n";
}
