//Ice cream volume calculation program
#include <iostream>		//for cout, cin, getline
#include <cmath>		//for power
#include <string>		//for string object

using namespace std;

//Practice using a #define to set PI's value
#define PI 3.14159265

void AskConeInfo(double *pDia, double *coneHt, string *pFlavor);
double CalculateIceCreamVol(double diameter, double coneHeight);

int main()
{
	//Note: the ice cream cone and scoop have the same diamter.
	double diameter, coneHeight;
	double totalIceCream;

	string flavor;

	cout << "Welcome to the C++ Single Scoop Ice Cream Parlor";

	AskConeInfo(&diameter, &coneHeight, &flavor);
	totalIceCream = CalculateIceCreamVol(diameter, coneHeight);

	//write output
	cout.precision(1);
	cout.setf(ios::fixed | ios::showpoint);

	cout << "\nResults \nYour desired flavor is " << flavor;
	cout << "\nCone size " << diameter << " by " << coneHeight;
	cout.precision(3);
	cout << "\nTotal volume of " << flavor <<
		" ice cream is " << totalIceCream << " cubic inches " << endl;

	return 0;
}


double CalculateIceCreamVol(double diameter, double coneHeight)
{
	//Now calculate volume of ice cream
	//First calculate the cone volume
	double coneVol, radius;
	
	radius = diameter/2.0;
	coneVol = (PI * pow(radius,2) * coneHeight)/3.0;

	//next calculate the volume of the scoop 
	double scoopVol = 4.0/3.0 * PI * pow(radius,3);

	//total volume is entire cone plus 1/2 the scoop
	double totalIceCream = coneVol + scoopVol/2.0;

	return totalIceCream;
}

void AskConeInfo(double *pDia, double *pConeHt, string *pFlavor)
{
	cout << "\nPlease enter your desired flavor: ";
	getline(cin,*pFlavor);
	
	cout << "Please enter the cone height (inches): ";
	cin >>  *pConeHt;

	cout << "Please enter the cone diameter (inches): ";
	cin >> *pDia;
	cin.ignore();
}
