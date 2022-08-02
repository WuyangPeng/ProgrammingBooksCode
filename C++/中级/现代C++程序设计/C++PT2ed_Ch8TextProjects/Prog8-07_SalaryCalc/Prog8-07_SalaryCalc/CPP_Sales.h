//File:  CPP_Sales.h

// This class represents the sales staff
// who work at the C++ Auto Dealership

#ifndef  _CPP_SALES_H
#define  _CPP_SALES_H

#include "CPP_Employee.h"
#include <string>
using namespace std;

class CPP_Sales: public CPP_Employee
{
private:
	float commission, weeklySales;

public:
	CPP_Sales();

	//define these for a sales person
	void CalculatePay();
	void AskForPayInfo();
	void WritePayInfo();
};

#endif