//Program to demonstrate operator precedence.

#include <iostream>		//for cout
#include <iomanip>		//for setw()
using namespace std;

int main()
{
	double X, Y, Z, Q;

	cout << "This program demonstrates how operator precedence "
			<< "\nand () can give different arithmetic results "
			<< "\nwith the same numeric values. \n" ;

	//Perform four calculations and just vary the ()s.
	X =  2 + 5.0  * 4 - 6.0 * 7/2;
	Y = (2 + 5.0) * 4 - (6.0 * 7/2);
	Z =  2 + (5.0 * 4 - 6.0) * 7/2;
	Q =  2 + 5.0  * (4 - 6.0 * 7)/2;

	//Write results to 3 places of precision.
	cout.setf(ios::fixed | ios::showpoint);
	cout.precision(3);

	//We'll use setw() to have C++ write the values in 8 spaces.
	//This allows us to line up the output values. 
	cout << "\nX = " << setw(8) << X;
	cout << "\nY = " << setw(8) << Y;
	cout << "\nZ = " << setw(8) << Z;
	cout << "\nQ = " << setw(8) << Q << "\n";

	return 0;
}
