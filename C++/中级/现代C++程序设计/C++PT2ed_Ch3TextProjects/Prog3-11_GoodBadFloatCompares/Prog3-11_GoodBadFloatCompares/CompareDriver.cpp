//Program that shows the right way and wrong way to
//compare floats and doubles for exact value.

#include <iostream>		//for cout
#include <cmath>		//for fabs function
using namespace std;

int main()
{

	float sum = static_cast<float>(0.0);
	float nickel = static_cast<float>(0.05);
	float dollar = static_cast<float>(1.00);

	//add 20 nickels, result should be 1.00
	for(int i = 0; i < 20; ++i)
	{
		sum = sum + nickel;
	}


	//Here is the wrong way to check a float value.
	if(sum == dollar)
	{
		cout << "First check: Sum is $1.00 ";
	}
	else
	{
		cout << "First check: Sum is not $1.00 ";
	}


	//Here is the right way to check a float value.
	//Check to see that the absolute value of the 
	//difference is a small value. This works!

	if( fabs(sum - dollar) < 0.00001)
	{
		cout << "\nSecond check: Sum is $1.00 " << endl;
	}
	else
	{
		cout << "\nSecond check: Sum is not $1.00 " << endl;
	}

	return 0;

}