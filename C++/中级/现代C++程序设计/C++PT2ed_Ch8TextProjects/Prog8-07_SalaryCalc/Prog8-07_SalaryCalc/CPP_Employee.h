//File: CPP_Employee.h

// This class represents all individuals
// who work at the C++ Auto Dealership

#ifndef  _CPP_EMP_H
#define  _CPP_EMP_H

#include <string>
#include <iostream>
using namespace std;

class CPP_Employee
{
protected:
	string name;
	float weeklyPay;
public:
	CPP_Employee(){ name = "", weeklyPay = 0;}

	//These virtual functions must be 
	//defined in the child classes.
	virtual void CalculatePay() = 0;
	virtual void WritePayInfo() = 0;

	//We write the Ask function here, as it
	//only asks for the Employee's name.
	virtual void AskForPayInfo()
	{
		cout << "\nPlease enter the employee's name: ";
		getline(cin,name);
	}
};

#endif