#include <iostream>

using namespace std;

struct PolyItem
{
    int coff;
    int exp;
    PolyItem *next;
    PolyItem *prev;

    PolyItem(int coffVal, int expVal)
    {
        this->coff = coffVal;
        this->exp = expVal;
        this->next = NULL;
        this->prev = NULL;
    }
};

class Poly
{
	
	public :
		PolyItem *head;
		PolyItem *tail;
		
		// Constructor
		Poly();
		
		// Utility Func.
		void p_append(int c, int e);
		void p_display();
		
		// Other
		friend Poly p_add(Poly &poly1, Poly &poly2);
		friend Poly p_sub(Poly &poly1, Poly &poly2);
		
};

int main()
{
	Poly p1;
	p1.p_append ( 4, 5 ) ;
	p1.p_append ( 2, 4 ) ;
	p1.p_append ( 1, 2 ) ;
	p1.p_append ( 9, 1 ) ;
	p1.p_append ( 12, 0 ) ;	
	p1.p_display();
	cout << endl;
	Poly p2;
	p2.p_append ( 16, 3 ) ;
	p2.p_append ( 11, 2 ) ;
	p2.p_append ( 3, 1 ) ;	
	p2.p_display();
	cout << endl;
	Poly p3 = p_sub(p1, p2);
	p3.p_display();
}


Poly::Poly()
{
	head = NULL;
	tail = NULL;
}

void Poly::p_append(int c, int e)
{
	PolyItem *temp = new PolyItem(c, e);
	if (tail)
	{
		temp->prev = tail;
		tail->next = temp;
		tail = temp;
	}
	else
	{
		head = temp;
		tail = temp;
	}
}

void Poly::p_display()
{
	PolyItem *ptr = head;
	
	while (ptr != NULL)
	{
		if (ptr != head)
		{
			if (ptr->coff >= 0)
			{
				cout << " + ";
			}
			else
			{
				cout << " ";
			}
		}
		
		if (ptr->exp != 0)
		{
			if (ptr->coff != 0)
			{
				cout << ptr->coff << "x^" << ptr->exp;
			}
		}
		else
		{
			if (ptr->coff != 0)
			{
				cout << ptr->coff;
			}
		}
		ptr = ptr->next;
	}
}

Poly p_add(Poly &poly1, Poly &poly2)
{
	Poly result;
	
	PolyItem *ptr1 = poly1.head;
	PolyItem *ptr2 = poly2.head;
	
	while (ptr1 != NULL && ptr2 != NULL)
	{
		if (ptr1->exp < ptr2->exp)
		{
			result.p_append(ptr2->coff, ptr2->exp);
			ptr2 = ptr2->next;
		}
		else if (ptr1->exp > ptr2->exp)
		{
			result.p_append(ptr1->coff, ptr1->exp);
			ptr1 = ptr1->next;
		}
		else
		{
			result.p_append(ptr1->coff + ptr2->coff, ptr1->exp);
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}
	}
	
	while (ptr1 != NULL)
	{
		result.p_append(ptr1->coff, ptr1->exp);
		ptr1 = ptr1->next;
	}
	
	while (ptr2 != NULL)
	{
		result.p_append(ptr2->coff, ptr2->exp);
		ptr2 = ptr2->next;
	}
	
	return result;
	
}

Poly p_sub(Poly &poly1, Poly &poly2)
{
	Poly result;
	
	PolyItem *ptr1 = poly1.head;
	PolyItem *ptr2 = poly2.head;
	
	while (ptr1 != NULL && ptr2 != NULL)
	{
		if (ptr1->exp < ptr2->exp)
		{
			result.p_append(ptr2->coff, ptr2->exp);
			ptr2 = ptr2->next;
		}
		else if (ptr1->exp > ptr2->exp)
		{
			result.p_append(ptr1->coff, ptr1->exp);
			ptr1 = ptr1->next;
		}
		else
		{
			result.p_append(ptr1->coff - ptr2->coff, ptr1->exp);
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}
	}
	
	while (ptr1 != NULL)
	{
		result.p_append(ptr1->coff, ptr1->exp);
		ptr1 = ptr1->next;
	}
	
	while (ptr2 != NULL)
	{
		result.p_append(ptr2->coff, ptr2->exp);
		ptr2 = ptr2->next;
	}
	
	return result;
	
}

