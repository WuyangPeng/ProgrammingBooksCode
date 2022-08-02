// Practice using iomanipulator and iosflags
// We use the setw and scientific notation flag here.

#include <iostream>		//for cout
#include <iomanip>		//for endl

using namespace std;

int main()
{

	double pi = 3.141592653589793;
	double feet = 5280;
	double number = 123.456789;

	//The precision can be placed in the stream 
	
	cout<< "\nFirst write: set precision to 5"
			<< setprecision(5) 
			<< "\n    Pi = " << pi 
			<< "\n  Feet = " << feet 
			<< "\nNumber = " << number << endl;

	//fixed and precision, we get 5 decimal digits
	//cout still remembers that precision is set to 5
	cout<< "Second write: set fixed with precision of 5"
			<< setiosflags(ios::fixed) 
			<< "\n    Pi = " << pi 
			<< "\n  Feet = " << feet 
			<< "\nNumber = " << number << endl;

	//Data is automatically right-justified within
	//the setw() field width size
	cout<< "Third write: use setw(12)"
			<< "\n    Pi = " << setw(12) << pi  
			<< "\n  Feet = " << setw(12) << feet 
			<< "\nNumber = " << setw(12) << number << endl;

	//Now write the data in scientific notation. 
	//Need to unset the fixed flag to see sci notation.
	cout.unsetf(ios::fixed);
	cout<< "Fourth write: scientific notation" 
			<< setiosflags(ios::scientific) 
			<< "\n    Pi = " << setw(12) << pi 
			<< "\n  Feet = " << setw(12) << feet 
			<< "\nNumber = " << setw(12) << number << endl;

	return 0;
}
