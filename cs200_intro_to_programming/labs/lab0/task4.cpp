
#include <iostream>
using namespace std;
int main()
{

	double tank_volume = 300 * 200 * 100;
	int max_cups = 0;
	double cup_volume = 0, cup_radius = 0, cup_height = 0;

	cout << "Please enter the cup radius in cm" << endl;
	cin >> cup_radius;
	cout << "Please enter the cup height in cm" << endl;
	cin >> cup_height;

	cup_volume = (22 / 7) * cup_height * cup_radius * cup_radius;

	max_cups = tank_volume / cup_volume;
	cout << "Max cups = " << max_cups << endl;

	return 0;
}
