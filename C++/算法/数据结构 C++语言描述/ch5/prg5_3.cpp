// File: prg5_3.cpp
// the program illustrates the use of exceptions with the miniVector
// class. during execution, the underflowError and indexRangeError
// exceptions each occur once

#include <iostream>

#include "d_vector.h"

using namespace std;

int main()
{

	miniVector<int> v;

	// try block attempts to erase frok empty vector; catch block
	// catches underflowError exception from pop_back()
	try
	{
		v.pop_back();
	}
	catch (const underflowError& e)
	{
		cout << e.what() << endl;
		// store element in v[0]
		v.push_back(99);
	}

	cout << "The size of v = " << v.size() << endl;

	// try block enables index bound checking ; catch block catches
	// indexRangeError exception from operator[]
	try
	{
		cout << "v[0] = " << v[0] << endl;
		cout << "v[1] = " << v[1] << endl;
	}
	catch (const indexRangeError& e)
	{
		cout << e.what() << endl;
	}

	return 0;
}

/*
Run:

miniVector pop_back(): vector is empty
The size of v = 1
v[0] = 99
miniVector: index range error  index 1  size = 1
*/
