/*File: SnowStorm.h

Snow types:
powder, freshly, uncompacted snow 
packed, coarse, granular wet snow 
sleet, ice pellets formed when snowflakes 
		 thaw, then refreeze  

water densities (equivalents values of snow)
new powder 12% water 
1 inch powder = 0.12 inches of rain

packed snow 33% water
1 inch packed = 0.33 inches of water

sleet or late spring snow pack 50% 
1 in sleet = 0.50 inches of water

*/

#ifndef _SNOW_VC_H
#define _SNOW_VC_H

#include "RainVolCalc.h"

class SnowVolCalc : public RainVolCalc
{
private:
	string type;	//powder, packed or sleet
	double density;	//% of water

	void CalculateGallons(); //have to know what type
public:
	SnowVolCalc();	
	void SetType(string t);
	string GetVolumeString();
	float GetGallons();
};

#endif

