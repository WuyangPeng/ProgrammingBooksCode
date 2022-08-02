/*********************************************************************

  Filename:  vect_ast.cpp
  Section:   11.1   Constructors and Destructors
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

 //Implementation of a safe array type vect
 // Has assertions instead of check with message on
 // constructors and destructors

#include  <iostream.h>
#include  <stdlib.h>      //for exit
#include  <assert.h>      //for assert

class vect {
public:
	//constructors and destructor
	explicit vect(int n = 10);      //default constructor
	vect(const vect& v);   //copy constructor
	vect(const int a[], int n);  //initialization by array
	~vect() { delete [] p; }
	int   ub() const { return (size - 1); }  //upper bound
	int&  operator[](int i) const;           //range checked
	vect& operator=(const vect& v);          //not inherited
	vect  operator+(const vect& v);
	friend ostream& operator <<(ostream& out, const vect& v);
private:
	int*  p;     //base pointer
	int   size;  //number of elements
};

//default constructor
vect::vect(int n) : size(n)
{
   assert(n > 0);
   p = new int[size];
   assert (p != 0);            //allocation error
}

//copy constructor
vect::vect(const vect& v) : size(v.size)
{
	p = new int[size];
	assert (p != 0);
	for (int i = 0; i < size; ++i)
		p[i] = v.p[i];
}

//constructor for initializing vect from an array
vect::vect(const int a[], int n) : size(n)
{
   assert(n > 0);
	p = new int[size];
	assert (p != 0);
	for (int i = 0; i < size; ++i)
		p[i] = a[i];
}

//overloaded subscript operator
int& vect::operator [](int i) const
{
	if (i < 0 || i > (size - 1) ) {
		cerr << "illegal vect index: " << i << endl;
		exit(1);
	}
	return (p[i]);
}

//overloaded output operator
ostream& operator <<(ostream& out, const vect& v)
{
	for (int i = 0; i <= (v.size-1); ++i)
		out << v.p[i] << '\t';
	return (out << endl);
}




vect& vect::operator=(const vect& v)
{
	if (this != &v) {    //check for assign to self
		int  s = (size < v.size) ? size : v.size;

		if (v.size != size)
			cerr << "copying different size arrays "
				  << size << " and " << v.size << endl;
		for (int i = 0; i < s; ++i)
			 p[i] = v.p[i];
	}
	return (*this);
}

vect vect::operator+(const vect& v)
{
	int   s = (size < v.size) ? size : v.size;
	vect  sum(s);

	if (v.size != size)
		cerr << "adding different size arrays "
			  << size << " and " << v.size << endl;
	for (int i = 0; i < s; ++i)
		sum.p[i] = p[i] + v.p[i];
   return sum;
}

void init_vect(vect& v, int start, int incr)
{
	for (int i = 0; i <= v.ub(); ++i) {
		v[i] = start;
		start += incr;
	}
}


main()
{
	int    array[6] = { 5, 10, 15, 20, 25, 30 };
	vect   v1, v2(5);       //use default constructor
	vect   v3 (array, 5);   //use construct and init from 1st 5 elements array
	vect   v4 (v3);         //use copy constructor

	init_vect(v1, 1, 1);
	cout << "\nvector v1 is " << v1;

	init_vect(v2, 0, 2);
	cout << "\nvector v2 is " << v2;
	cout << "\nvector v3 is " << v3;
	cout << "\nvector v4 is " << v4;

	v4 = v3 + v2;              //test overloaded operator =  +
	cout << "\nvector v4 is " << v4;
}

