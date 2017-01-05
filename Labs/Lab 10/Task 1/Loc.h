#include <iostream>

using namespace std;

class Loc
{
	int longitude;
	int latitude;
	public:
    		Loc();
    		Loc(int lg, int lt);
		Loc(const Loc& loc1);
		
		friend ostream& operator <<(ostream& outs, const Loc& loc1); 
		friend istream& operator >>(istream& ins, Loc& loc1);
		friend Loc operator +(const Loc& loc1, const Loc& loc2);
		friend Loc operator +(const Loc& loc1, int x);
		friend Loc operator +(int x, const Loc& loc1);
		void operator ++(int);
		void operator ++();
		
};
