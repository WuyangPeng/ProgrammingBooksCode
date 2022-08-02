//A complete program for determining the average
//monthly phone bill over one year.

#include <iostream>
using namespace std;

int main()
{
	// Declare an array of 12 floats
	float phone_bills[12];       
	float sum, ave;

	int i;		     //i is our loop index 

	cout << "A program that determines yearly total"
		<< "\nand average monthly phone bill.\n";

	// Obtain monthly billing information 
	for(i = 0; i < 12; ++i) 
	{
		cout << "Enter bill for month # " << i+1 << " $";
		cin >> phone_bills[i];
	}

	// Now calculate the average value.
	sum = 0.0;
	for(i = 0; i < 12; ++i)  
	{
		sum = sum + phone_bills[i];
	}

	ave = sum/12;
	cout.precision(2);
	cout.setf(ios::fixed);
	cout << "Total yearly phone cost is $" << sum
		<< "\nAverage monthly phone bill is $"
		 << ave << endl;

	return 0;
}
