//File:  CalcDriver.cpp
//This program uses a VolumeCalc object
//to compute them volume of a box and sphere.

#include "VolumeCalc.h"
#include <iostream>
using namespace std;

int main()
{
	cout <<"The Volume Calculator Program"
		<< "\nCalculates the volume of a "
		<< "box or a sphere." << endl;

	VolumeCalc Bob;		//make a VolumeCalc object

	//we'll have Bob do the calculations for us. :-)

	//local vars for user to input data
	double len, wid, hgt, rad;

	cout << "\nBox: Enter the length width "
		"and height  \n  ";
	cin >> len >> wid >> hgt;

	cout << "\nSphere: Enter the radius  ";
	cin >> rad;

	//Now give Bob the box and sphere dimensions.
	//We set the data into the object. 
	Bob.SetBoxDim(len,wid,hgt);

	Bob.SetSphRadius(rad);

	//Now we ask Bob to give us the volumes.
	//We use the get functions.
	double sphereV = Bob.GetSphVol();
	double boxV = Bob.GetBoxVol();

	cout.setf(ios::fixed);
	cout.precision(3);

	cout << "  Box Volume:  " << boxV
		<< "\nSphere Volume:  " << sphereV;

	cout << "\nThanks to Bob, our VolumeCalc object!\n";

	return 0;
}