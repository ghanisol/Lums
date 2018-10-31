#include <iostream>

using namespace std;

class Odometer
{
	public:
		Odometer();
		void set_efficiency(double eff);
		void Reset_To_Zero();
		void Total_Miles(double miles);
		double No_of_Gallons();		
	private:
		double miles_driven;
		double efficiency;
};

int main()
{
	Odometer car;
	car.set_efficiency(2.5);
	car.Total_Miles(120);
	cout << car.No_of_Gallons() << endl;
	car.Reset_To_Zero();
	car.set_efficiency(3.4);
	car.Total_Miles(1200);
	cout << car.No_of_Gallons() << endl;
	car.Reset_To_Zero();
	                                  
}

Odometer::Odometer() : miles_driven(0), efficiency(0)
{

}

void Odometer::Reset_To_Zero()
{
	miles_driven = 0;
}

void Odometer::set_efficiency(double eff)
{
	efficiency = eff;
}

void Odometer::Total_Miles(double miles)
{
	miles_driven = miles_driven + miles;
}


double Odometer::No_of_Gallons()
{
	double temp = miles_driven / efficiency;
	return temp;
}
