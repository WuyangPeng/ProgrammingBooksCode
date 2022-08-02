//File: RainBarrelEst.h


#ifndef _RB_EST_H
#define _RB_EST_H

#include "RainVolCalc.h"
#include "SnowVolCalc.h"

#include <string>
using namespace std;

class RainBarrelEst
{
private:
	RainVolCalc rainy;
	SnowVolCalc snowy;
	float sqFootage, rainInches, snowInches;
	string desc, typeOfSnow, timeframe;

	float barrelCapacity;

public:
	RainBarrelEst();

	void AskForData();
	void WriteData();

};

#endif
