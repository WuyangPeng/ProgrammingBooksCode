//Program to calculate the number of gallons in
//a cowboy's stock tank

#include <iostream>		//for cout, cin, getline
#include <cmath>		//for power
#include <string>		//for string object

using namespace std;

#define PI 3.14159265

int main()
{
	//declare variables
	double tankDia, tankHeight;
	double fillAmount;

	cout << "Hi Cowboy! Welcome to the "
			<< "\nC++ Circular Stock Tank Capacity Calculator";

	cout << "\nPlease enter your tanks's diameter in inches: ";
	cin >> tankDia;
	
	cout << "Please enter the tank's height in inches: ";
	cin >>  tankHeight;

	cout << "Please enter fill percentage"
			<< "\n100 for 100%, \n50 for 50%, \n25 for 25%, etc.  ";
	cin >> fillAmount;

	//Now calculate volume of the tank
	//Use the cylinder formula vol = pi*r*r*h
	double tankVol, tankRadius;
	
	tankRadius = tankDia/2.0;
	tankVol = PI * pow(tankRadius,2) * tankHeight;


	//next calculate convert to gallons 
	double tankGallons = tankVol/231.0;
	
	double desiredFillGal = tankGallons * (fillAmount)/100.0;
	//write output
	cout.precision(1);
	cout.setf(ios::fixed | ios::showpoint);

	cout << "\nResults "
			<< "\nStock tank capacity = " << tankGallons << " gallons";

	cout << "\nFilled to " << fillAmount << " % " << " requires "
			<< desiredFillGal << " gallons " << endl;
	
	return 0;
}




