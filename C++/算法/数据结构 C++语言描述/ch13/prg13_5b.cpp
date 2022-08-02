// File: prg13_5b.cpp
// the program demonstrates a virtual destructor in the base
// class. the base class, baseCL, declares a virtual destructor
// and the derived class, dynDerived, allocates dynamic memory.
// after allocating a dynDerived object and storing the pointer
// in a baseCL pointer, the program calls delete and causes the
// derived class destructor to execute, followed by the base class
// destructor. the dynamic memory allocated by the derived object
// is removed, preventing a memory leak

#include <iostream>

using namespace std;

class baseCL
{
	public:
		baseCL()
		{	cout << "baseCL constructor - no action" << endl;}

		virtual ~baseCL()		// virtual destructor
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

baseCL constructor - no action
dynDerived constructor - allocate 4-element array
dynDerived destructor - deallocate 4-element array
baseCL destructor - no action
*/
