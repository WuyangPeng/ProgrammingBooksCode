// Program to test user-define output operator.

// pg 612, sec 21.2.3, Output of User-Defined Type

// No guarantees offered. Constructive comments to bs@research.att.com


#include<iostream>

using namespace std;


// Note: my "complex"; not the one from the standard library

class complex {
public:
	complex(double r =0, double i =0) : re(r), im(i) { }

	double real() const { return re; }
	double imag() const { return im; }
	// ...
private:
	double re, im;
};

ostream& operator<<(ostream&s, const complex& z)
{
	return s << '(' << z.real() << ',' << z.imag() << ')';
}

int main()
{
	complex x(1,2);
	cout << "x = " << x << '\n';

	return 0;	// redundant in ISO C++
}
