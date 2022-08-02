//Program to illustrate division results using 
//integers and doubles.

#include <iostream>
using namespace std;


int main()
{
	int resInt;
	double resDouble;

	//First we'll do integer division.
	//Remember that 16 and 3 are integers in C++.
	resInt = 16/3;
	resDouble = 16/3;

	//Tell cout to write 14 decimal places for our doubles.
	cout.setf(ios::fixed | ios::showpoint);
	cout.precision(14);

	cout<< "Integer division is 16/3 ";
	cout << "\nResult assigned to an int:  " << resInt;
	cout << "\nResult assigned to a double: " << resDouble << "\n";

	//Second, we'll do the same division but with doubles.
	//By writing 15.0 and 3.0, C++ regards them as doubles.
	resInt = 16.0/3.0;
	resDouble = 16/3.0; 

	cout<< "\nDouble division is 16.0/3.0 ";
	cout << "\nResult assigned to an int:  " << resInt;
	cout << "\nResult assigned to a double: " << resDouble << "\n";
	
	return 0;
}


	