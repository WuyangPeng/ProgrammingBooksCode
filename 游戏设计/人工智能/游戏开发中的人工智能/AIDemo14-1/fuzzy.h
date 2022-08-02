#ifndef _FUZZY
#define _FUZZY

#include "mymath.h"


double	FuzzyGrade(double value, double x0, double x1);
double  FuzzyReverseGrade(double value, double x0, double x1);
double	FuzzyTriangle(double value, double x0, double x1, double x2);
double	FuzzyTrapezoid(double value, double x0, double x1, double x2, double x3);
double	FuzzyAND(double A, double B);
double	FuzzyOR(double A, double B);
double	FuzzyNOT(double A);


#endif  // _FUZZY