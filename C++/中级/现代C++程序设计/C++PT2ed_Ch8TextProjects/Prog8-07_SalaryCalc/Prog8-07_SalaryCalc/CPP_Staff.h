//File:  CPP_Staff.h

// This class represents the admin staff
// who work at the C++ Auto Dealership

#ifndef  _CPP_STAFF_H
#define  _CPP_STAFF_H

#include "CPP_Employee.h"
#include <string>
using namespace std;

class CPP_Staff: public CPP_Employee
{
private:
	float hrsWorked, hrRate;

public:
	CPP_Staff();

	//define these for a staff person
	void CalculatePay();
	void AskForPayInfo();
	void WritePayInfo();
};

#endif