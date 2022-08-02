//File: RainVolCalc.h
//This class calculates the number of
//gallons of water that covers a given
//number of square feet. 

#ifndef _RAIN_VC_H
#define _RAIN_VC_H

#include <string>
using namespace std;

class RainVolCalc
{
protected:
	float inches;	//depth of rain
	int sqFeet;
	float gallons;
	void CalculateGallons();
public:
	RainVolCalc();
	void SetInches(float i){inches = i; }
	void SetSqFeet(int sf){sqFeet = sf; }
	float GetGallons();
	string GetVolumeString();
};

#endif
