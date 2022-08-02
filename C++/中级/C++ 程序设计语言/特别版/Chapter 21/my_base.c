// Program to test integration of a virtual output function with stream I/O.

// pg 613, sec 21.2.3.1, Virtual Output Functions

// Also illustrates how we can achieve the effect of a function that is
// polymorphic on its second argument.

// No guarantees offered. Constructive comments to bs@research.att.com


#include<iostream>

using namespace std;

class My_base {
public:
	// ...

	virtual ostream& put(ostream& s) const = 0;	// write *this to s
};

ostream& operator<<(ostream& s, const My_base& r)
{
	return r.put(s);	// use the right put()
}


class Sometype : public My_base {
public:
	// ... 

	ostream& put(ostream& s) const;	// the real output function: override My_base::put()
};

void f(const My_base& r, Sometype& s)	// use << which calls the right put()
{
	cout << r << s;
}

class Some_other_type : public My_base {
public:
	// ... 

	ostream& put(ostream& s) const;
};

int main()
{
	Sometype s;
	Some_other_type s2;
	My_base& b = s;
	f(b,s);
	f(s2,s);

	return 0;	// redundant in ISO C++
}

ostream& Sometype::put(ostream& s) const
{
	return s << "Sometype\n";
}

ostream& Some_other_type::put(ostream& s) const
{
	return s << "Some_other_type\n";
}
