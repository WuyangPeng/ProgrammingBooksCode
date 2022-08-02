// Practice with iosflags
// We'll use the endl to flush the cout buffer.

#include <iostream>		//for cout
#include <iomanip>		//for endl

using namespace std;

int main()
{

	double pi = 3.141592653589793;
	double feet = 5280;
	double number = 123.456789;

	//first let's just write the values
	cout << "\nFirst write: not setting any flags"
			<< "\nPi = " << pi 
			<< "\nFeet = " << feet 
			<< "\nNumber " << number << endl;
	
	//if we just do precision, it fixes how many 
	//spaces are used to write values  
	cout.precision(5);	

	//showpoint says to write the decimal point
	//cout remembers that precision is set to 5
	cout.setf(ios::showpoint);
	cout<< "\nSecond write: set prec to 5 and showpoint"
			<< "\nPi = " << pi 
			<< "\nFeet = " << feet 
			<< "\nNumber = " << number << endl;

	//if you set fixed and precision, it sets decimal places
	cout.setf(ios::fixed);   
	cout<< "\nThird write: set fixed with precision of 5"
			<< "\nPi = " << pi 
			<< "\nFeet = " << feet 
			<< "\nNumber = " << number << endl;

	return 0;
}
