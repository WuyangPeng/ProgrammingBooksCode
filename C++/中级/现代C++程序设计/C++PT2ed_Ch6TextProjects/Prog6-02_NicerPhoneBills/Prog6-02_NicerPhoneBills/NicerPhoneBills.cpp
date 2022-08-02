//A program to calculate phone bill average for
//the year. It uses an array of C++ string objects
//to hold the month names.

#include <iostream>
#include <string>
using namespace std;

int main()
{
	// Declare an array of 12 floats
	float phone_bills[12];       
	float sum, ave;

	//Declare and initialize the names of the months:
	string month[12] = {"Jan", "Feb", "Mar", "Apr",
					"May", "June", "July", "Aug",
					"Sept", "Oct", "Nov", "Dec" };

	int i;		     //i is our loop index 

	cout << "A program that determines yearly total"
		<< "\nand average monthly phone bill.\n";

	// Obtain monthly billing information 
	for(i = 0; i < 12; ++i) 
	{
		cout << "Enter bill for month " << month[i] << " $";
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
