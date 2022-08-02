//File: SnowVolCalc.cpp

#include "SnowVolCalc.h"
#include <sstream>
using namespace std;

SnowVolCalc::SnowVolCalc()
{
	//default to powder
	type = "powder";
	density = 0.12;
}
	
string SnowVolCalc::GetVolumeString()
{
	//This calls SnowVolCalc's 
	CalculateGallons();

	stringstream ss;
	ss << "" << inches << " \" of " << type 
		<< " over " << sqFeet
		<< " sq feet yields " << gallons
		<< " gallons. ";

	return ss.str();
}

void SnowVolCalc::CalculateGallons()
{
	//this calcs gallons of rain
	RainVolCalc::CalculateGallons();

	//reduces gallons by type of snow
	gallons = gallons * density;
}

float SnowVolCalc::GetGallons()
{
	//this calls SnowVolCalc's function
	CalculateGallons();

	return gallons;
}

void SnowVolCalc::SetType(string t)
{
	type = t;
	
	//set density value according to type
	//if unknown type, set to powder
	if(type == "powder") 
		density = 0.12;
	else if(type == "packed") 
		density = 0.33;
	else if(type == "sleet")
		density = 0.50;
	else
		density = 0.12;
}


