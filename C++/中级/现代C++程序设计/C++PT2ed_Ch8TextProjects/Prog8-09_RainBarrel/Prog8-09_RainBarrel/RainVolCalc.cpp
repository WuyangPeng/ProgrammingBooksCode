//File: RainVolCalc.cpp

#include "RainVolCalc.h"
#include <sstream>
#include <string>
using namespace std;

RainVolCalc::RainVolCalc()
{
	sqFeet = 0;
	inches = 0;
}

void RainVolCalc::CalculateGallons()
{
	//calculate sq inches coverage
	int sqInches = sqFeet * 144;

	//mult by depth to get cubic in vol
	int cubicIn = inches * sqInches;

	//231 cubic in = 1 gallon
	gallons = cubicIn/231.0;
}

float RainVolCalc::GetGallons()
{
	CalculateGallons();
	return gallons;
}

string RainVolCalc::GetVolumeString()
{
	CalculateGallons();
	stringstream ss;
	ss << "" << inches <<  " \" of rain over " 
		<< sqFeet << " sq feet is " << gallons 
		<< " gallons. ";

	return ss.str();
}
