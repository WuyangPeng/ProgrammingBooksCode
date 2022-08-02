#ifdef __BORLANDC__
// suppress the warning message that argument two is never used
// in function demo()
#pragma warn -8057
#endif	// __BORLANDC__

// File: prg5_2.cpp
// the program arranges for the dynamicClass constructor,
// destructor, copy constructor, and overloaded assignment
// operator to be called in a variety of circumstances.
// output from the function calls traces their order of
// execution

#include <iostream>

#include "d_dynam.h"

using namespace std;

template <typename T>
dynamicClass<T> demo(dynamicClass<T> one,
							dynamicClass<T>& two, const T& m);

int main()
{
	/*	objA(3,5) calls the constructor (member1=3, *member2=5)

		objB = objA calls copy constructor to initialize object objB
		from object objA. (member1=3, *member2=5)

		object objC calls the constructor (member1=0, *member2=0)
	*/
	dynamicClass<int> objA(3,5), objB = objA, objC(0,0);

	/*	call the function demo(). the copy constructor creates
		the value argument one (member1=3, *member2=5) by copying
		object objA. argument two is passed by reference, so the copy
		constructor is not called. upon return, a copy is made
		of the local object obj. this copy is assigned to object objC
	*/
	objC = demo(objA,objB,5);

	// all remaining objects are destroyed upon program exit.
	return 0;
}

template <typename T>
dynamicClass<int> demo(dynamicClass<T> one, dynamicClass<T>& two, const T& m)
{
	// calls the constructor (member1 = m, *member2 = m)
	dynamicClass<T> obj(m,m);

	// a copy of obj is made and returned as the
	// value of the function
	return obj;

	// the temporary object one is destroyed upon
	// return from demo()
}

/*
Run:

Constructor: 3/5
Copy Constructor:  3/5
Constructor: 0/0
Copy Constructor:  3/5
Constructor: 5/5
Copy Constructor:  5/5
Destructor: 5/5
Destructor: 3/5
Assignment Operator: 5/5
Destructor: 5/5
Destructor: 5/5
Destructor: 3/5
Destructor: 3/5
*/
