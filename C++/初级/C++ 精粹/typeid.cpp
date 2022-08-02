/*********************************************************************

  Filename:  typeid.cpp
  Section:   15.3   Run-Time Type Indentification
  Compiler:  Borland C++     Version 5.0       Summer 1996
  C++ Distilled: Descriptions, Prescriptions and Style  By Ira Pohl

*********************************************************************/

#include <iostream.h>
#include <typeinfo.h>

class Base {
public:
	Base():hide(0){}
	void mutate(int i){ hide = i;}
	void print()const {cout << "hide in Base = "
									 << hide << endl;}
private:
	int hide;
};


class One: public Base {
public:
	One():Base(),data(0) {}
	void mutate(int i){ data = i;}
	void print()const {cout << "data in One = "
	                         << data << endl;}
private:
	int data;
};

int main ()
{
	Base* bptr; One* Derived;
   //print type name of what ptr points at
   cout << typeid(bptr).name() << endl;
   cout << typeid(Derived).name() << endl;
   if (typeid(bptr) == typeid(Derived))
      cout << "type bprt & Derived same" << endl;
}
