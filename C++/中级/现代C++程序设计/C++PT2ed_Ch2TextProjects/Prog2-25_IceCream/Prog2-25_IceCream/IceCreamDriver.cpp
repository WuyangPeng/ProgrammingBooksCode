//Ice cream volume calculation program
#include <iostream>		//for cout, cin, getline
#include <cmath>		//for power
#include <string>		//for string object

using namespace std;

//Practice using a #define to set PI's value
#define PI 3.14159265

int main()
{
	//Note: the ice cream cone and scoop have the same diamter.
	double diameter, coneHeight;

	string flavor;

	cout << "Welcome to the C++ Single Scoop Ice Cream Parlor";

	cout << "\nPlease enter your desired flavor: ";
	getline(cin,flavor);
	
	cout << "Please enter the cone height (inches): ";
	cin >>  coneHeight;

	cout << "Please enter the cone diameter (inches): ";
	cin >> diameter;

	//Now calculate volume of ice cream
	//First calculate the cone volume
	double coneVol, radius;
	
	radius = diameter/2.0;
	coneVol = (PI * pow(radius,2) * coneHeight)/3.0;


	//next calculate the volume of the scoop 
	double scoopVol = 4.0/3.0 * PI * pow(radius,3);

	//total volume is entire cone plus 1/2 the scoop
	double totalIceCream = coneVol + scoopVol/2.0;

	//write output
	cout.precision(1);
	cout.setf(ios::fixed | ios::showpoint);

	cout << "Results \nYour desired flavor is " << flavor;
	cout << "\nCone size " << diameter << " by " << coneHeight;
	cout.precision(3);
	cout << "\nTotal volume of " << flavor <<
		" ice cream is " << totalIceCream << " cubic inches " << endl;

	return 0;
}




