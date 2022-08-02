//File: Functions.cpp
//This file contains the function definitions
//for the functions declared in Functions.h

#include <iostream>
#include <string>
#include <sstream>		//for stringstream
using namespace std;

//display a program greeting
void WriteGreeting()
{
	cout << "C++ Farm Irrigation Calculation Program"
		<< "\nGiven the number of acres, "
		<< " desired depth of water (inches),\nand flow rate"
		<< " from the turn-out gate, \nthis program finds the time"
		<< " and gallons needed\nto irrigate the C++ Farm's field. \n";
}

//ask user for size of field in acres
float AskFieldSize()
{
	float acres;
	
	cout << "What is the size of your field in acres? ==> ";
	cin >> acres;
	cin.ignore();

	return acres;
}

//ask user for depth of water desired in the field
float AskIrrigationRate()
{
	float gallonsPerMinute;
	
	cout << "\nWhat is the gate's flow rate of water "
		<< "\n(in gallons per minute)? ==> ";
	cin >> gallonsPerMinute;
	cin.ignore();

	return gallonsPerMinute;
}


//ask user for flow rate from the irrigation gate
int AskDepthOfWater()
{
	int depth;
	
	cout << "\nHow deep do you wish to flood your field? ==> ";
	cin >> depth;
	cin.ignore();

	return depth;
}

//calculate the time and gallon usage
string CalculateTimeAndGallons(int depth, float rate, float acres)
{
	int sqFeetInAcre = 43560;

	int totalSqFeet = sqFeetInAcre * acres;

	//convert field size to total square inches
	//a square foot is 12 x 12 = 144 square inches

	int totalSqInches = totalSqFeet * 144;

	//now multiply by desired inch depth
	int fieldVolume = totalSqInches * depth;

	//now convert to gallons, divide by 231 cubic in/gal
	float gallons = fieldVolume/231.0;

	//flow rate is gallons/minute
	float irrigTime = gallons/rate;

	//now put it all together in a summary string
	//use a stringstream object to help
	stringstream ssObj;

	ssObj   << "A " << acres << " acre field "
			<< "flooded to " << depth << " inches"
			<< "\nrequires " << gallons << " total gallons of water.";

	ssObj << "\n\nIrrigation gate flow rate: " <<  rate 
			<< " gallons/minute" << "\nit will take " 
			<< irrigTime << " minutes to irrigate this field. ";

	return ssObj.str();
}
