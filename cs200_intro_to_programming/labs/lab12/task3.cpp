#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

class Player
{
	public:
	Player()
	{
	
	}
	
	virtual int getGuess()
	{
		return 0;
	}
};

class HumanPlayer : public Player
{
	public:
	HumanPlayer()
	{
	
	}
	
	virtual int getGuess()
	{
		int guess = 0;
		cin >> guess;
		return guess;
	}
};

class ComputerPlayer : public Player
{
	public:
	ComputerPlayer()
	{
	
	}
	
	virtual int getGuess()
	{
		srand(time(NULL));
		return rand() % 100;
	}
};

// prototype
bool checkForWin(int guess, int answer);
void play(Player &player1, Player & player2);


int main()
{
	HumanPlayer hplayer1, hplayer2;
	ComputerPlayer cplayer1, cplayer2;
	
	// Human vs Human
	cout << "Human vs Human\n\n";
	play(hplayer1, hplayer2);
	
	// Human vs Comp
	cout << "Human vs Comp\n\n";
	play(hplayer1, cplayer1);
	
	// Comp vs Comp
	cout << "Comp vs Comp\n\n";
	play(cplayer1, cplayer2);
}

bool checkForWin(int guess, int answer)
{
	cout << "You guessed " << guess << ".\n";
	if (answer == guess)
	{
		cout << "You're right! You win!\n" << endl;
		return true;
	}
	else if (answer < guess)
	{
		cout << "Your guess is too high.\n" << endl;
	}
	else
	{
		cout << "Your guess is too low.\n" << endl;
	}
	return false;
}

void play (Player &player1, Player &player2)
{
	int answer = 0, guess = 0;
	answer = rand() % 100;
	bool win = false;
	
	while (!win)
	{
		cout << "Player 1's turn to guess." << endl;
		guess = player1.getGuess();
		win = checkForWin(guess, answer);
		
		if (win)
		{
			return;
		}
		cout << "\nPlayer 2's turn to guess." << endl;
		guess = player2.getGuess();
		win = checkForWin(guess, answer);
	}
}
