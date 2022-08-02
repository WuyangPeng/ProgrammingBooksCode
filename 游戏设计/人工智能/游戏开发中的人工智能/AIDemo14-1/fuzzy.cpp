#include "fuzzy.h"

#define MIN(x, y) (x<y) ? x:y
#define MAX(x, y) (x>y) ? x:y;

double	FuzzyGrade(double value, double x0, double x1)
{
	double result = 0;
	double x = value;

	if(x <= x0)
		result = 0;
	else if(x >= x1)
		result = 1;
	else
		result = (x/(x1-x0))-(x0/(x1-x0));

	return result;
}

double  FuzzyReverseGrade(double value, double x0, double x1)
{
	double result = 0;
	double x = value;

	if(x <= x0)
		result = 1;
	else if(x >= x1)
		result = 0;
	else
		result = (-x/(x1-x0))+(x1/(x1-x0));

	return result;
}

double	FuzzyTriangle(double value, double x0, double x1, double x2)
{
	double result = 0;
	double x = value;

	if(x <= x0)
		result = 0;
	else if(x == x1)
		result = 1;
	else if((x>x0) && (x<x1))
		result = (x/(x1-x0))-(x0/(x1-x0));
	else
		result = (-x/(x2-x1))+(x2/(x2-x1));

	return result;
}

double	FuzzyTrapezoid(double value, double x0, double x1, double x2, double x3)
{
	double result = 0;
	double x = value;

	if(x <= x0)
		result = 0;
	else if((x>=x1) && (x<=x2))
		result = 1;
	else if((x>x0) && (x<x1))
		result = (x/(x1-x0))-(x0/(x1-x0));
	else
		result = (-x/(x3-x2))+(x3/(x3-x2));

	return result;
}

double FuzzyAND(double A, double B)
{
	return MIN(A, B);
}

double FuzzyOR(double A, double B)
{
	return MAX(A, B);
}

double FuzzyNOT(double A)
{
	return 1.0 - A;
}



///////////////////////////////
/*
mClose = FuzzyTriangle(25, -30, 0, 30);
mMedium = FuzzyTrapezoid(25, 10, 30, 50, 70);
mFar = FuzzyGrade(25, 50, 70);

mTiny = FuzzyTriangle(8, -10, 0, 10);
mSmall = FuzzyTrapezoid(8, 2.5, 10, 15, 20);
mModerate = FuzzyTrapezoid(8, 15, 20, 25, 30);
mLarge = FuzzyGrade(8, 25, 30);

mLow = 

mMedium

mHigh
*/


