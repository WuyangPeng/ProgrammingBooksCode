// File: prg5_1.cpp
// dynamicClass objects are declared in the main program
// and in the function destroyDemo(). output indicates when
// the system calls the constructor and destructor for each
// object

#include <iostream>

#include "d_dynam.h"

using namespace std;

void destroyDemo(int m1, int m2);

int main()
{
	// create object Obj_1 with member1=1, *member2=100
	dynamicClass<int> obj1(1,100);
 
	// declare a pointer to an object
	dynamicClass<int> *ptrObj2;
 
	// allocate dynamic object pointed to by ptrObj2 with
	// member1 = 2 and *member2 = 200
	ptrObj2 = new dynamicClass<int> (2,200);
 
	// call function destroyObject() with arguments 3/300
	destroyDemo(3,300);
 
	// explicitly delete object pointed to by ptrObj2
	delete ptrObj2;
 
	cout << "Ready to exit program." << endl;

	return 0;
}



void destroyDemo(int m1, int m2)
{
	dynamicClass<int> obj(m1,m2);
}

/*
Run:

Constructor: 1/100
Constructor: 2/200
Constructor: 3/300
Destructor: 3/300
Destructor: 2/200
Ready to exit program.
Destructor: 1/100
*/
