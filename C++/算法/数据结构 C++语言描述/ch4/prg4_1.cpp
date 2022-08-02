// File: prg4_1.cpp
// the program uses the store class to create objects associated
// with int, double, and string types. using the overloaded <<
// operator, it outputs the value in each object. the program
// illustrates the member functions getValue() and setValue()
// for the store object with string data

#include <string>

#include "d_store.h"			// use store class

using namespace std;

int main()
{
	// declare three different types of store objects
	store<int> intStore(5);
	store<double> realStore(2.718);
	store<string> strStore("Template");
	
	cout << "The values stored by the objects are:" << endl;
	cout << intStore << endl;
	cout << realStore << endl;
	cout << strStore << endl;
	cout << endl;

	cout << "The concatenation of 'Template' in strStore and "
			  "'Class' is:" << endl;
	// access current value strStore and concatenate " Class"
	// update the value in strStore with the new string
	strStore.setValue( strStore.getValue() + " Class" );
	cout << strStore << endl;

	return 0;
}

/*
Run:

The values stored by the objects are:
Value = 5
Value = 2.718
Value = Template

The concatenation of 'Template' in strStore and 'Class' is:
Value = Template Class
*/
