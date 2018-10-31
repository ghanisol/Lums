#include <iostream>
#include <vector>

using namespace std;

vector<int> merge(vector<int> a, vector<int> b);
int big (int a_l,int b_l);
int sm(int a_l, int b_l);
int main()
{
	vector<int> a;
	vector<int> b;
	
	int first[] = {1, 4, 9, 16, 5, 2, 1};
	int second[] = {9, 7, 4, 9, 11};
	
	for (int i = 0; i < 7; i++)
	{
		a.push_back(first[i]);
	}
	
	for (int i = 0; i < 5; i++)
	{
		b.push_back(second[i]);	
	}
	
	vector<int> c = merge(a, b);
	
	for (int i = 0; i < c.size(); i++)
	{
		cout << c[i] << " ";
	}	
	cout << endl;
	
	
}

vector<int> merge(vector<int> a, vector<int> b)
{
	int a_l = a.size();
	int b_l = b.size();
	
	int len = big(a_l, b_l);
	vector<int> c;
	
	if (a_l < b_l)
	{

		for (int i = 0; i < len; i++)
		{
			if (i < a_l)
			{
				c.push_back(a[i]);
				c.push_back(b[i]);
			}	
			else
			{
				c.push_back(b[i]);
			}
		}
	}
	else 
	{
		for (int i = 0; i < len; i++)
		{
			if (i < b_l)
			{
				c.push_back(a[i]);
				c.push_back(b[i]);
			}
			else
			{
				c.push_back(a[i]);
			}
		
		}
	}

	return c;
}

int big(int a_l, int b_l)
{

	if (a_l < b_l)
	{
		return b_l;
	}
	else
	{
		return a_l;
	}	
}


