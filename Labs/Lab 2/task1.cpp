#include <iostream>

using namespace std;

int main()
{
	int temp_cel = 0, temp_fahr = 0;
	
	for (temp_cel = 100; temp_cel != temp_fahr; temp_cel--)
	{
		temp_fahr = ((9 * temp_cel) / 5) + 32;
		
		if(temp_cel == temp_fahr)
		{
			break;
		}
	}

	cout << "The temp is " << temp_cel;
}
