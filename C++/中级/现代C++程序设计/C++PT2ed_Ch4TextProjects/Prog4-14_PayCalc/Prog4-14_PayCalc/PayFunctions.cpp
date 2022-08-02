//File: PayFunctions.cpp
//This file contains the function definitions
//for the functions declared in PayFunctions.h

#include <iostream>
#include <sstream>		//for stringstream
using namespace std;

//manager: week's pay = salary/52 weeks
float CalcPay(float salary)
{
	float weekPay;
	weekPay = salary/static_cast<float>(52.0);
	return weekPay;
}

//salesperson: week's pay = base + comm*totalSales				
float CalcPay(float basePay, float totalSales, float comm)
{

	//assume commission comes is as percentage, i.e. 15%
	float weekPay;
	weekPay = basePay + totalSales*comm/100.0;
	return weekPay;
}

//staff: hrs*salary + 1.5*rate for overtime
float CalcPay(float hrsWorked, float hrRate)
{
	float weekPay;
	if(hrsWorked <= 40.0)
	{
		weekPay = hrsWorked*hrRate;
	}
	else
	{
		float OT = hrsWorked-40;
		weekPay = 40.0*hrRate + OT*hrRate*1.5;
	}
	return weekPay;
}
