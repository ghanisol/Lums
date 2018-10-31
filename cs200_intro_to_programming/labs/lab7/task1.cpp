#include <iostream>

using namespace std;

struct Point {
	double x;
	double y;
};

struct Rectangle {
	double x;
	double y;
	double height;
	double width;
};

// prototype
int Point_In_Rect(const Point& pt, const Rectangle& r);
int Equal_Points(const Point& p1, const Point& p2);
void Add_Point(const Point& p1, const Point& p2, Point& res);
Point MidPoint(const Point& p1, const Point& p2);
int ZeroRect(const Rectangle& r);

int main()
{
	
	// Point pt
	Point pt;
	pt.x = 0;
	pt.y = 1;
	
	// Rectangle
	Rectangle r;
	r.x = 1;
	r.y = 3;
	r.height = 2;
	r.width = 3;	;
	
	// func. 1
	cout << Point_In_Rect(pt, r) << endl;

	// Point p1
	Point p1;
	p1.x = 2;
	p1.y = 3;
	
	// Point p2
	Point p2;
	p2.x = 2;
	p2.y = 3;
	
	// func. 2
	cout << Equal_Points(p1, p2) << endl;

	// Point res
	Point res;
	
	// func. 3
	Add_Point(p1, p2, res);
	cout << res.x << endl << res.y << endl;

	// Point Midpoint
	Point Midpoint;
	
	// func. 4
	Midpoint = MidPoint(p1, p2);
	cout << Midpoint.x << endl << Midpoint.y << endl;

	// func. 5
	cout << ZeroRect(r) << endl;
}

int Point_In_Rect(const Point& pt, const Rectangle& r)
{
	if ((pt.x >= r.x && pt.x <= r.x + r.width) && (pt.y <= r.y && pt.y >= r.y - r.height))
	{
		return 1;
	}
	else
	{
		return 0;
	} 
}

int Equal_Points(const Point& p1, const Point& p2)
{
	if ((p1.x == p2.x) && (p1.y == p2.y))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void Add_Point(const Point& p1, const Point& p2, Point& res)
{
	res.x = p1.x + p2.x;
	res.y = p1.y + p2.y;
}

Point MidPoint(const Point& p1, const Point& p2)
{
	Point temp;
	temp.x = (p1.x + p2.x) / 2;
	temp.y = (p1.y + p2.y) /2;
	
	return temp;
}

int ZeroRect(const Rectangle& r)
{
	if (r.height == 0 && r.width == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

