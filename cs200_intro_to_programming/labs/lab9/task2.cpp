#include <iostream>

using namespace std;

class rational
{
	private:
		int n;
		int d;
	public:
		rational(int x, int y);
		rational(int x);
		rational add(rational& num2);
		rational sub(rational& num2);
		rational mul(rational& num2);
		rational div(rational& num2);
		bool less(rational& num2);
		rational neg();
};

int main()
{
	rational num1(2,5), num2(3,7);
	cout << "Num 1: 2/5\n";
	cout << "Num 2 : 3/7\n";
	
	// ADD
	cout << "\nADD\n";
	num1.add(num2);

	// SUB
	cout << "\nSub\n";
	num1.sub(num2);
	
	// MUL
	cout << "\nMul\n";
	num1.mul(num2);
	
	// DIV
	cout << "\nDiv\n";
	num1.div(num2);
	
	// Neg
	cout << "\nNeg\n";
	num1.neg();
	
	// Less
	cout << "\nLess\n";
	num1.less(num2);

}

rational::rational(int x, int y)
{
	n = x;
	d = y;
}

rational::rational(int x)
{
	n = x;
	d = 1;
}

rational rational::add(rational& num2)
{
	int x = (n*num2.d) + (d*num2.n);
	int y = d*num2.d;
	cout << x << "/" << y << endl;
	rational temp(x, y);
	return temp;
}

rational rational::sub(rational& num2)
{
	int x = (n*num2.d) - (d*num2.n);
	int y = d*num2.d;
	cout << x << "/" << y << endl;
	rational temp(x, y);
	return temp;
}

rational rational::mul(rational& num2)
{
	int x = n*num2.n;
	int y = d*num2.d;
	cout << x << "/" << y << endl;
	rational temp(x, y);
	return temp;
}

rational rational::div(rational& num2)
{
	int x = n*num2.d;
	int y = d*num2.n;
	cout << x << "/" << y << endl;
	rational temp(x, y);
	return temp;
}

bool rational::less(rational& num2)
{
	if ((n*num2.d) < (num2.n*d))
	{
		cout << "True\n";
		return true;
	}
	else
	{
		cout << "False\n";
		return false;
	}
}

rational rational::neg(void)
{
	int x = -n;
	int y = d;
	cout << x << "/" << y << endl;
	rational temp(x, y);
	return temp;
}
