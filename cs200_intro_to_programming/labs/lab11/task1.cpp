#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class vehicle
{
	protected:
		string model;
		string make;
		int year;
		string regNo;
	public:
		vehicle();
		vehicle(string model_temp, string make_temp, int year_temp, string regNo_temp);
		virtual void print();
		virtual int income()
		{
			return 0;
		}
		virtual int size()
		{
			return 3*sizeof(string) + sizeof(int); 
		}
};

class cars : public vehicle
{
	protected:
		double engineCapacity;
		int SeatingCapacity;
		double HourlyRent;
		double MonthlyCost;
	public:
		cars();
	cars(string model_temp, string make_temp, int year_temp,string regNo_temp, double e_cap_temp, int s_cap_temp, double h_rent_temp, double m_cost_temp);
                virtual void print();
                virtual int income()
                {
                	return HourlyRent*2*365;
                }
                virtual int size()
                {
                	return 3*sizeof(string) + 3*sizeof(double) + 2*sizeof(int);
                }
};

class SportsCars : public cars
{
	protected:
		double topSpeed;
		double zero2hundredtime;
	public:
		SportsCars();
	SportsCars(string model_temp,string make_temp,int year_temp,string regNo_temp,double e_cap, int s_cap, double h_rent, double m_cost, double top_s, double z2h);
                virtual void print();
                virtual int income()
                {
                	return HourlyRent*2*365;
                }
                virtual int size()
                {
              		 return 3*sizeof(string) + 5*sizeof(double) + 2*sizeof(int);
              		 
                }
};

class LargeCar : public cars
{
	protected:
		bool isOffRoad;
		double CargoCapacity;
	public:
		LargeCar();
	LargeCar(string model_temp,string make_temp,int year_temp,string regNo_temp, double e_cap, int s_cap, double h_rent, double m_cost, bool is_off, double c_cap);
                virtual void print();
                virtual int income()
                {
                	return HourlyRent*2*365;
                }
                virtual int size()
                {
                	return 3*sizeof(string) + 4*sizeof(double) + 2*sizeof(int) + sizeof(bool);
                }
};

class Trucks : public vehicle
{
	protected:
		double CargoCapacity;
		double DailyRent;
		double YearlyCost;
	public:
		Trucks();
		Trucks(string model_temp, string make_temp, int year_temp, string regNo_temp, double c_cap, double d_rent, double y_cost);
                virtual void print();
                virtual int income()
                {
                	return DailyRent*365;
                }
                virtual int size()
                {
                	return 3*sizeof(string) + 3*sizeof(double) + 1*sizeof(int);
                }
};

class LightTruck : public Trucks
{
	protected:
		bool hasRefrigerator;
		string NameofLogoPrinted;
	public:
		LightTruck();
	LightTruck(string model_temp, string make_temp, int year_temp, string regNo_temp, double c_cap, double d_rent, double y_cost, bool has_r, string logo);
                virtual void print();
                virtual int income()
                {
                	return DailyRent*365;
                }
                virtual int size()
                {
                	return 4*sizeof(string) + 3*sizeof(double) + 1*sizeof(int) + 1*sizeof(bool);
                }
};

class HeavyTruck : public Trucks
{
	protected:
		bool hasCrane;
		int CrewCapacity;
	public:
		HeavyTruck();
	HeavyTruck(string model_temp, string make_temp, int year_temp, string regNo_temp, double c_cap, double d_rent, double y_cost, bool has_c, int crew_cap);
                virtual void print();
                virtual int income()
                {
                	return DailyRent*365;
                }
                virtual int size()
                {
                	return 3*sizeof(string) + 3*sizeof(double) + 2*sizeof(int) + 1*sizeof(bool);
                }
		
};

int main()
{
	ifstream in;
	in.open("inputDetails.txt");
	vector <vehicle*> gari;
	while (!in.eof())
	{
		string type;
		in >> type;
		
		string model_temp, make_temp, regNo_temp, logo;
		int year_temp, s_cap, crew_cap;
		double e_cap,h_rent,m_cost,top_s,z2h,c_cap,d_rent,y_cost;
		bool is_off, has_r, has_c;
		
		
		if (type == "vehicle")
		{
			in >> model_temp >> make_temp >> year_temp >> regNo_temp;
			vehicle* temp = new vehicle(model_temp, make_temp, year_temp, regNo_temp);
			gari.push_back(temp);
		}
		else if (type == "heavytruck")
		{
			in >> model_temp >> make_temp >> year_temp >> regNo_temp >> c_cap >> d_rent >> y_cost >> has_c >> crew_cap;
			HeavyTruck* temp = new HeavyTruck(model_temp, make_temp, year_temp, regNo_temp, c_cap, d_rent, y_cost, has_c, crew_cap);
			gari.push_back(temp);
		}
		else if (type == "sportscar")
		{
			in >> model_temp >> make_temp >> year_temp >> regNo_temp >> e_cap >> s_cap >> h_rent >> m_cost >> top_s >> z2h;
			SportsCars* temp = new SportsCars(model_temp, make_temp, year_temp, regNo_temp, e_cap, s_cap, h_rent, m_cost, top_s, z2h);
			gari.push_back(temp);
		}
		else if (type == "car")
		{	
			in >> model_temp >> make_temp >> year_temp >> regNo_temp >> e_cap >> s_cap >> h_rent >> m_cost;
			cars* temp = new cars(model_temp, make_temp, year_temp, regNo_temp, e_cap, s_cap, h_rent, m_cost);
			gari.push_back(temp);
		}
		else if (type == "largecar")
		{
			in >> model_temp >> make_temp >> year_temp >> regNo_temp >> e_cap >> s_cap >> h_rent >> m_cost >> is_off >> c_cap;
			LargeCar* temp = new LargeCar(model_temp, make_temp, year_temp, regNo_temp, e_cap, s_cap, h_rent, m_cost, is_off, c_cap);
			gari.push_back(temp);
			 
		}
		else if (type == "lightTruck")
		{
			in >> model_temp >> make_temp >> year_temp >> regNo_temp >> c_cap >> d_rent >> y_cost >> has_r >> logo;
			LightTruck* temp = new LightTruck(model_temp, make_temp, year_temp, regNo_temp, c_cap, d_rent, y_cost, has_r, logo);
			gari.push_back(temp);
		}
		else if (type == "truck")
		{
			in >> model_temp >> make_temp >> year_temp >> regNo_temp >> c_cap >> d_rent >> y_cost; 
			Trucks* temp = new Trucks(model_temp, make_temp, year_temp, regNo_temp, c_cap, d_rent, y_cost);
			gari.push_back(temp);
		}
	}
	
	in.close();
	
	for (int i = 0; i < gari.size(); i++)
	{
		cout << "\n" << i << " \n";
		gari[i]->print();
		cout << "Average Size : " << gari[i]->size() << endl; 
	}
	
	long long income = 0;
	for (int i = 0; i < gari.size(); i++)
	{
		income += gari[i]->income();
	} 
	cout << "\n\nIncome : " << income << endl;
}

/* Vehicle Class Member Func. */

vehicle::vehicle()
{

}

vehicle::vehicle(string model_temp, string make_temp, int year_temp, string regNo_temp)
{
	model = model_temp;
	make = make_temp;
	year = year_temp;
	regNo = regNo_temp;
}

void vehicle::print()
{
cout << "Model : " << model;
cout << "\nMake : " << make;
cout << "\nYear : " << year;
cout << "\nRegNo : " << regNo << endl << endl;
}

/* Car class Member Func. */

cars::cars()
{
	
}

cars::cars(string model_temp, string make_temp, int year_temp, string regNo_temp, double e_cap_temp, int s_cap_temp, double h_rent_temp, double m_cost_temp)
{
	  model = model_temp;
	  make = make_temp;
          year = year_temp;
	  regNo = regNo_temp;
	  engineCapacity = e_cap_temp;
	  SeatingCapacity = s_cap_temp;
	  HourlyRent = h_rent_temp;
	  MonthlyCost = m_cost_temp;
	                          
}

void cars::print()
{	
cout << "Model : " << model;
cout << "\nMake : " << make;
cout << "\nYear : " << year;
cout << "\nRegNo : " << regNo;
cout << "\nengineCapacity : " << engineCapacity;
cout << "\nSeatingCapacity : " << SeatingCapacity;
cout << "\nHourlyRent : " << HourlyRent;
cout << "\nMonthlyCost : " << MonthlyCost << endl << endl;
}

/* SportsCars class Member Func. */

SportsCars::SportsCars()
{

}

SportsCars::SportsCars(string model_temp,string make_temp,int year_temp,string regNo_temp,double e_cap,int s_cap,double h_rent, double m_cost, double top_s, double z2h)
{
	model = model_temp;
	make = make_temp;
	year = year_temp;
	regNo = regNo_temp;
	engineCapacity = e_cap;
	SeatingCapacity = s_cap;
	HourlyRent = h_rent;
	MonthlyCost = m_cost;
	topSpeed = top_s;
	zero2hundredtime = z2h;
	
}

void SportsCars::print()
{
cout << "Model : " << model;
cout << "\nMake : " << make;
cout << "\nYear : " << year;
cout << "\nRegNo : " << regNo;
cout << "\nengineCapacity : " << engineCapacity;
cout << "\nSeatingCapacity : " << SeatingCapacity;
cout << "\nHourlyRent : " << HourlyRent;
cout << "\nMonthlyCost : " << MonthlyCost;
cout << "\ntopSpeed : " << topSpeed;
cout << "\nzero2hundredtime : " << zero2hundredtime << endl << endl;

}

/* LargeCar class Member Func. */

LargeCar::LargeCar()
{

}

LargeCar::LargeCar(string model_temp,string make_temp,int year_temp,string regNo_temp,double e_cap,int s_cap,double h_rent,double m_cost,bool is_off,double c_cap)
{
        make = make_temp;
        year = year_temp;
        regNo = regNo_temp;
        engineCapacity = e_cap;
        SeatingCapacity = s_cap;
        HourlyRent = h_rent;
        MonthlyCost = m_cost;
        isOffRoad = is_off;
        CargoCapacity = c_cap;
                
}

void LargeCar::print()
{
cout << "Model : " << model;
cout << "\nMake : " << make;
cout << "\nYear : " << year;
cout << "\nRegNo : " << regNo;
cout << "\nengineCapacity : " << engineCapacity;
cout << "\nSeatingCapacity : " << SeatingCapacity;
cout << "\nHourlyRent : " << HourlyRent;
cout << "\nMonthlyCost : " << MonthlyCost;
cout << "\nisOffRoad : " << isOffRoad;
cout << "\nCargoCapacity : " << CargoCapacity << endl << endl;cout << "Model : " << model;
}

/* Trucks class Member Func. */

Trucks::Trucks()
{

}

Trucks::Trucks(string model_temp, string make_temp, int year_temp, string regNo_temp, double c_cap, double d_rent, double y_cost)
{
 	model = model_temp;
   	make = make_temp;
       	year = year_temp;
	regNo = regNo_temp;
	CargoCapacity = c_cap;
	DailyRent = d_rent;
	YearlyCost = y_cost;
                         
}

void Trucks::print()
{
cout << "Model : " << model;
cout << "\nMake : " << make;
cout << "\nYear : " << year;
cout << "\nRegNo : " << regNo;
cout << "\nCargoCapacity : " << CargoCapacity;
cout << "\nDailyRent : " << DailyRent;
cout << "\nYearlyCost : " << YearlyCost << endl << endl;
}

/* LightTruck class Member Func. */

LightTruck::LightTruck()
{

}

LightTruck::LightTruck(string model_temp,string make_temp,int year_temp,string regNo_temp, double c_cap, double d_rent, double y_cost, bool has_r, string logo)
{
	model = model_temp;
	make = make_temp;
	year = year_temp;
	regNo = regNo_temp;
	CargoCapacity = c_cap;
	DailyRent = d_rent;
	YearlyCost = y_cost;
	hasRefrigerator = has_r;
	NameofLogoPrinted = logo;
        
}

void LightTruck::print()
{
cout << "Model : " << model;
cout << "\nMake : " << make;
cout << "\nYear : " << year;
cout << "\nRegNo : " << regNo;
cout << "\nCargoCapacity : " << CargoCapacity;
cout << "\nDailyRent : " << DailyRent;
cout << "\nYearlyCost : " << YearlyCost;
cout << "\nhasRefrigerator : " << hasRefrigerator;
cout << "\nNameofLogoPrinted : " << NameofLogoPrinted;
}

/* HeavyTruck class Member Func. */

HeavyTruck::HeavyTruck()
{

}

HeavyTruck::HeavyTruck(string model_temp,string make_temp,int year_temp,string regNo_temp, double c_cap, double d_rent, double y_cost, bool has_c, int crew_cap)	
{
	model = model_temp;
	make = make_temp;
	year = year_temp;
	regNo = regNo_temp;
	CargoCapacity = c_cap;
	DailyRent = d_rent;	
	YearlyCost = y_cost;
	hasCrane = has_c;
	CrewCapacity = crew_cap;
}

void HeavyTruck::print()
{
cout << "Model : " << model;
cout << "\nMake : " << make;
cout << "\nYear : " << year;
cout << "\nRegNo : " << regNo;
cout << "\nCargoCapacity : " << CargoCapacity;
cout << "\nDailyRent : " << DailyRent;
cout << "\nYearlyCost : " << YearlyCost;
cout << "\nhasCrane : " << hasCrane;
cout << "\nCrewCapacity : " << CrewCapacity << endl << endl;
}
