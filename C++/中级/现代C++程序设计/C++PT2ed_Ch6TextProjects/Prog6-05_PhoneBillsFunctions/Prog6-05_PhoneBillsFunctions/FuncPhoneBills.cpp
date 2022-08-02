//A program to calculate phone bill average for
//the year. It uses two functions, one to fill the
//array, one to sum and calculate the average.

#include <iostream>
#include <string>
using namespace std;

//Function declarations use [] to indicate arrays
void AskBillData(string month[], float bills[]);

//return the average, use a reference for the sum
float CalcBillTotalandAve(float bills[], float &rSum);

int main()
{
	// Declare an array of 12 floats
	float phone_bills[12];       

	//Declare and initialize the names of the months:
	string month[12] = {"Jan", "Feb", "Mar", "Apr",
					"May", "June", "July", "Aug",
					"Sept", "Oct", "Nov", "Dec" };

	cout << "\n A program that determines yearly total"
		<< "\n and average monthly phone bill.\n\n";

	//use array names in call statements 
	//(arrays addresses are actually passed to functions)
	AskBillData(month,phone_bills);


	float ave, sum;
	ave = CalcBillTotalandAve(phone_bills, sum);

	cout.precision(2);
	cout.setf(ios::fixed);
	cout << "\n Total yearly phone cost is $" << sum
		<< "\n Average monthly phone bill is $"
		<< ave << endl;

	return 0;
}

//Function to ask for monthly bill data.
void AskBillData(string month[], float bills[])
{
	// Obtain monthly billing information 
	for(int i = 0; i < 12; ++i) 
	{
		cout << " Enter bill for month " << month[i] << " $";
		cin >> bills[i];
	}
}

//Function that determines bill average,
//given the yearly sum.
float CalcBillTotalandAve(float bills[], float &rSum)
{
	rSum = 0.0;
	for(int i = 0; i < 12; ++i)  
	{
		rSum = rSum + bills[i];
	}

	return rSum/12.0;
}


