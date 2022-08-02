/*********************************************************************

  Filename:  complexc.cpp
  Section:   11.3   Friend Functions
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

//overloading + for complex numbers
#include <iostream.h>

class complex {
private:
	double real, imag;
public:
	complex(double r, double i = 0) :
		real (r), imag (i) {}
	friend complex operator+ (complex a, complex b)
		{ return(complex(a.real + b.real, a.imag + b.imag));}
   void print() { cout << endl << real << "  " << imag << "i"; }
};

main()
{
   complex x(3, 5.5), y(4.2), z(0);
   double  t = 6.5;

   z = x + y;    //overloaded operator+ called
   z.print();
   z = z + t;    //t is converted to a complex first
   z.print();
}
