//File: StockTankCalc.h

#ifndef _STCalc_H
#define _STCalc_H

#include <string>
using namespace std;

class STCalc
{
private:
	int tankL, tankW, tankH;
	double tankGallons, tankPercent;
	string tankShape;
	
	void CalcCapacity();

public:
	STCalc();

	void setShape(string shape){tankShape = shape;}

	void setCircTankDims(int height, int width);
	void setRectTankDims(int height, int width, int length);
	void setOvalTankDims(int height, int width, int length);

	double getPercent(int per);
	double getTotalCapacity();

	void WriteTankData();
};

#endif