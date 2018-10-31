#include "Loc.h"

Loc::Loc(){}
Loc::Loc(int lg, int lt){
    longitude=lg;
    latitude=lt;
}
Loc::Loc(const Loc& loc1)
{
	longitude = loc1.longitude;
	latitude = loc1.latitude;
}


ostream& operator <<(ostream& outs, const Loc& loc1)
{
	int lg = loc1.longitude;
	int lt = loc1.latitude;
	
	outs << "Lon = " << lg << " " << "Lat = " << lt;
	
	return outs;
}

istream& operator >> (istream& ins, Loc& loc1)
{
	int lg, lt;
	char temp;
	ins >> lg >> temp >> lt;
	loc1.longitude = lg;
	loc1.latitude = lt;
	
	return ins;
}

Loc operator +(const Loc& loc1, const Loc& loc2)
{
	Loc temp;
	temp.longitude = loc1.longitude + loc2.longitude;
	temp.latitude = loc1.latitude + loc2.latitude;
	
	return temp;
}

Loc operator +(int x, const Loc& loc1)
{
	Loc temp;
	temp.latitude = loc1.latitude + x;
	temp.longitude = loc1.longitude;
	return temp;
}

Loc operator +(const Loc& loc1, int x)
{
	Loc temp;
	temp.longitude = loc1.longitude + x;
	temp.latitude = loc1.latitude;
	return temp;
}
                
 
void Loc::operator ++(int)
{
	longitude++;
	return;
}


void Loc::operator ++(void)
{
	latitude++;
	return;
}
                
