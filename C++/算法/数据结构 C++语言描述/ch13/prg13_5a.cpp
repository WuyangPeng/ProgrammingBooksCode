// File: prg13_5a.cpp
// the program demonstrates the need for a virtual destructor
// in the base class. the base class, baseCL, does not declare
// a virtual destructor, and the derived class, dynDerived,
// allocates dynamic memory. after allocating a dynDerived object
// and storing the pointer in a baseCL pointer, the program calls
// delete which causes only the base class destructor to execute. the
// dynamic memory allocated by the derived object is not removed,
// causing a memory leak

#include <iostream>

using namespace std;

class baseCL
{
	public:
		baseCL()
		{	cout << "baseCL constructor - no action" << endl;}

		~baseCL()		// not a virtual destructor
		{ cout << "baseCL destructor - no action" << endl; }
};

class dynDerived: public baseCL
{
 	public:
		dynDerived() : baseCL()
		{
      	cout << "dynDerived constructor - allocate 4-element array"
				  << endl;
			dArr = new int [4];
		}

		~dynDerived()
		{
      	cout << "dynDerived destructor - deallocate 4-element array"
		        << endl;
      	delete [] dArr;
      }
	private:
		int *dArr; 				// pointer to derived class dynamic array
};

int main()
{
	baseCL *basePtr = new dynDerived;

   delete basePtr;
	
	return 0;
}

/*
Run: (baseCL destructor is not virtual):

In baseCL constructor - no action
In dynDerived constructor - allocate 4-element array
In baseCL destructor - no action
*/
