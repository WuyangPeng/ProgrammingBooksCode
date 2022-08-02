#ifndef _VOLCALC_H
#define _VOLCALC_H

#include <string>
using namespace std;

class VolumeCalc
{
private:
	double sphRadius;
	double boxLength, boxWidth, boxHeight;
	double sphVolume, boxVolume;

	void CalcBoxVol();  //called from the set
	void CalcSphVol();	//functions 

public:
	VolumeCalc();		//constructor

	void SetSphRadius(double r);
	void SetBoxDim(double l, double w, double h);

	double GetSphVol(){ return sphVolume; }
	double GetBoxVol(){ return boxVolume; }

};

#endif



