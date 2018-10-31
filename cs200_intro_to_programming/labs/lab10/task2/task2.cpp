#include <iostream>
using namespace std;  

class twoD
{
	protected: 
        	double x, y;
     	public:       
     		twoD();
       		twoD(double i, double j); 
       		void setX(double NewX); 
       		void setY(double NewY);
        	double getX();
          	double getY();
 };
   
class threeD:public twoD
{    
	private:  
		double z;       
        public: 
        	threeD(double i, double j, double k);
                void setZ(double NewZ);
               	double getZ();
};
                     
int main() 
{
  	twoD Obj2(1, 1);
    	threeD Obj3(1, 2, 3);
      	cout << "Coordinates for the 3d object are: " <<endl;
       	cout << Obj3.getX() << ", " << Obj3.getY() <<", " << Obj3.getZ()<< endl;
        
        return 0;
} 

twoD::twoD() : x(0),y(0)
{

}

twoD::twoD(double i, double j)
{
	x = i;
	y = j;
}

void twoD::setX(double NewX)
{
	x = NewX;
	return;
}

void twoD::setY(double NewY)
{
	y = NewY;
	return;
} 

double twoD::getX()
{
	return x;
}

double twoD::getY()
{
	return y;
}

threeD::threeD(double i, double j, double k)
{
	x = i;
	y = j;
	z = k;
}

void threeD::setZ(double NewZ)
{
	z = NewZ;
	return;
}

double threeD::getZ()
{
	return z;
}
                                                
