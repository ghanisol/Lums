#include <iostream>
using namespace std;
int main()
{
	int length = 50, width = 40;
	int area = length * width;
	int piece_length = 7, piece_width = 3;
	int piece_area = piece_length * piece_width;
	int max_pieces = area / piece_area;

	cout << "Max Pieces = " << max_pieces;

	return 0;
}
