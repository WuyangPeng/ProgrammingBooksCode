//File: VolumeCalc.cpp
//Contains some of the function definitions
//for the VolumeCalc class. 

#include "VolumeCalc.h"
#include <cmath>
using namespace std;

VolumeCalc::VolumeCalc()		//constructor
{
	boxHeight = boxWidth = boxLength = 0.0;
	sphRadius = 0.0;
	boxVolume = sphVolume = 0.0;
}


//Once the set functions has been passed data,
//they call the calculate functions.

void VolumeCalc::SetSphRadius(double r)
{
	sphRadius = r;
	CalcSphVol();
}

void VolumeCalc::SetBoxDim(double l, double w, double h)
{
	boxLength = l;
	boxWidth = w;
	boxHeight = h;
	CalcBoxVol();
}


//The calculate functions do their math and
//assign the results into the class variables.
//The get functions return them. 
void VolumeCalc::CalcBoxVol()
{
	boxVolume = boxLength * boxWidth * boxHeight;
}

void VolumeCalc::CalcSphVol()
{
	double PI = 3.14159265;
	sphVolume = 4.0/3.0*PI*pow(sphRadius,2);
}

