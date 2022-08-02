//StockTankCalc.cpp
#include "StockTankCalc.h"
#include <string>
#include <iostream>
#include <cmath>		//for pow function

using namespace std;

STCalc::STCalc()
{
	//setting default tank to 
	//Circular 72 x 24 
	tankH = 24;
	tankW = 72;
	tankShape = "Circular";
	tankL = 0;
	CalcCapacity();
}

void STCalc::setCircTankDims(int height, int width)
{
	tankH = height;
	tankW = width;
}

void STCalc::setRectTankDims(int height, int width,
							 int length)
{
	tankH = height;
	tankW = width;
	tankL = length;
}

void STCalc::setOvalTankDims(int height, int width, 
							 int length)
{
	tankH = height;
	tankW = width;
	tankL = length;
}

double STCalc::getTotalCapacity()
{
	CalcCapacity();
	return tankGallons;
}

void STCalc::CalcCapacity()
{
	double PI = 3.14159265;

	if(tankShape =="Oval")
	{
		double endVol = (tankW/2) * (tankW/2)
						* PI*tankH;

		double rectVol = (tankL-tankW) * tankW
						*tankH;

		tankGallons = (endVol + rectVol)/231.0;
			      
	}
	else if(tankShape =="Rectangular")
	{
		tankGallons = (tankL * tankW * tankH)/231.0;
	}
	else if(tankShape == "Circular")
	{
		double tankArea = pow( (tankW/2.0), 2)*PI;
		tankGallons = tankArea*tankH/231.0;
	}
}

double STCalc::getPercent(int percentage)
{
	CalcCapacity();
	tankPercent = tankGallons*percentage*.01;

	return tankPercent;
}

void STCalc::WriteTankData()
{
	CalcCapacity();

	cout << "Shape:  " << tankShape;
	cout <<"Total capacity:  " 
		<< tankGallons << " gallons";

	cout << "\nWidth:  " << tankW
      << "\nHeight: " << tankH;

	if(tankShape != "Circular")
		cout<<"\nLength:  "<<tankL;

}