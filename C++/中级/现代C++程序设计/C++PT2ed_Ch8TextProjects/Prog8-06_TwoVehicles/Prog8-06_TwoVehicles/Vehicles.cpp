//File: Vehicles.cpp

#include <iostream>
using namespace std;
#include "Vehicles.h"

void Vehicle::AskInfo()
{
	cout << "\nEnter owner's name:  ";
	getline(cin, owner);

	cout << "Enter license plate such as NM JAM 099 :  ";
	getline(cin, license);
	
	cout << "Enter VIN :  ";
	getline(cin, VIN);
}

void Vehicle::WriteInfo()
{
	cout << "\n  Owner: " << owner
			<< "\nLicense: " << license
			<< "\n    VIN: " << VIN << endl;
}

void RV::AskInfo()
{
	cout << "\nEnter info for the RV.";

	Vehicle::AskInfo();	//call the base class AskInfo first

	cout << "Enter RV class  A, B, or C         ";
	cin >> category;
	cin.ignore();	// pull off enter key left by cin
}

void RV::WriteInfo()
{
	Vehicle::WriteInfo();
	cout << "This RV is a class " << category << endl;
}

void Semi::AskInfo()
{
	cout << "\nEnter info for the Semi Truck.";
	Vehicle::AskInfo();
	
	cout << "Enter the weight capacity ";
	cin >> weightCap;
	cin.ignore();
}

void Semi::WriteInfo()
{
	Vehicle::WriteInfo();
	cout << "This commercial vehicle has a "
		<< "weight capacity of " << weightCap 
		<< " pounds." << endl;
}
