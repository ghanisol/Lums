#include "Loc.cpp"

using namespace std;

int main(){
Loc ob1(10,20), ob2;

Loc ob3 = ob1;

cout << "Enter a location coordinates (a,b) : " << endl;
cin >> ob2;

cout << "ob1 " << ob1 << endl;
cout << "ob2 " << ob2 << endl;
cout << "ob3 " << ob3 << endl;

++ob1; // incrementing latitude
cout << "ob1 " << ob1 << endl;

ob2++; // incrementing longitude
cout << "ob2 " << ob2 << endl;


Loc ob4 = ob2;
cout << "ob4 " << ob4 << endl;

ob4 = ob4 + 20; // adding to longitude
cout << "ob4 " << ob4 << endl;

ob3 = 30 + ob3; // adding to latitude
cout << "ob3 " << ob3 << endl;

ob3 = ob4 + ob2; // adding both locations
cout << "ob3 " << ob3 << endl;


}
