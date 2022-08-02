//File:  WaterDriver.cpp

//This file contains the main function for
//the C++ Farm Irrigation program.

#include "Functions.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	WriteGreeting();

	string results;
	float acreage, irrigationRate;
	int depth;

	depth = AskDepthOfWater();
	acreage = AskFieldSize();

	irrigationRate = AskIrrigationRate();

	results = CalculateTimeAndGallons(depth, irrigationRate,acreage);

	cout << endl << results << endl;

	return 0;
}
