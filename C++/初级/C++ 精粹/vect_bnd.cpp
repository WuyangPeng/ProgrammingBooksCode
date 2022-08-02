/*********************************************************************

  Filename:  vect_bnd.cpp
  Section:   12     Inheritance
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

 //Implementation of a safe array type vect

#include  <iostream.h>
#include  <stdlib.h>      //for exit
#include  <assert.h>

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
protected:
	int*  p;     //base pointer
	int   size;  //number of elements
};

//default constructor
vect::vect(int n) : size(n)
{
	if (n <= 0) {
		cerr << "illegal vect size: " << n << endl;
		exit(1);
	}
	p = new int[size];
	assert (p != 0);//assert checks error
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
	if (n <= 0) {
		cerr << "illegal vect size: " << n << endl;
		exit(1);
	}
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


class vect_bnd : public vect {
public:
   vect_bnd(int = 0, int = 9);  //default 10 array
   vect_bnd(vect_bnd& v);       //copy constructor
   vect_bnd(vect& v);           //conversion constructor
   vect_bnd(const int a[], int ne, int lb = 0);
   int&  operator[](int) const;
   int  ub() const { return (u_bnd); }
   int  lb() const { return (l_bnd); }
   vect_bnd& operator=(const vect_bnd& v);
private:
   int  l_bnd, u_bnd;
};

//default constructor
vect_bnd::vect_bnd(int lb, int ub) :
          vect(ub - lb + 1), l_bnd(lb), u_bnd(ub) { }

//conversion constructor
vect_bnd::vect_bnd(vect& v) :
          vect(v), l_bnd(0), u_bnd(size - 1) { }

//copy constructor
vect_bnd::vect_bnd(vect_bnd& v) :
          vect(v), l_bnd(v.l_bnd), u_bnd(v.u_bnd) { }

//construct it from array, set lower and upper bounds
//init from array, start at element 0 of array for ne elements
//use lb as lower bound or 0 if not specified
vect_bnd::vect_bnd(const int a[], int n, int lb) :
          vect(a, n), l_bnd(lb), u_bnd(lb + n) { }

//overloaded assignment statement - not inherited from base vect
vect_bnd& vect_bnd::operator=(const vect_bnd& v)
{
 	vect::operator=(v);
	return (*this);
}

//efficient use of bounds - access directly
int& vect_bnd::operator [](int i) const
{
	 if (i < l_bnd || u_bnd < i) {
		 cerr << "index out of range" << endl;
		 exit(1);
	 };
	 return (p[i - l_bnd]);
}

void init_vect(vect_bnd& v, int start, int incr)
{
	for (int i = v.lb(); i <= v.ub(); ++i) {
		v[i] = start;
		start += incr;
	}
}


main()
{
	int       array[6] = { 5, 10, 15, 20, 25, 30 };
	vect_bnd  v1;               //use default constructor
	vect_bnd  v2(5,9);          //construct vect bounds 5 to 9
	vect_bnd  v3 (array, 5, 2); //use construct and init from 1st 5 elements array
	vect_bnd  v4 (v3);          //use copy constructor

	init_vect(v1, 1, 1);
	init_vect(v2, 0, 2);
	cout << "\nvector v1 (" << v1.lb() << ", " << v1.ub() << ") is \t" << v1;
	cout << "\nvector v2 (" << v2.lb() << ", " << v2.ub() << ") is \t" << v2;
	cout << "\nvector v3 (" << v3.lb() << ", " << v3.ub() << ") is \t" << v3;
	cout << "\nvector v4 (" << v4.lb() << ", " << v4.ub() << ") is \t" << v4;

	v4 = v3 + v2;//test overloaded operator =  +
	cout << "\nvector v4 (" << v4.lb() << ", " << v4.ub() << ") is \t" << v4;
}


