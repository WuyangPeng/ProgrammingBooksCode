// File: PayCheckDriver.cpp
// This program uses virtual functions to 
// calculate weekly pay for three 
// C++ Auto Dealership employees.

#include <iostream>
using namespace std;

#include "CPP_Staff.h"
#include "CPP_Sales.h"

int main()
{
	cout << "Pay day at the C++ Car Dealership \n"
			<< "Calculate pay for one staff member"
			<< " and two salespersons. \n";
	
	//one secretary, two salesmen
	CPP_Staff admin;
	CPP_Sales seller1, seller2;

	//make an array of base class pointers
	CPP_Employee *emp[3];

	//load array with sales and staff addresses
	emp[0] = &admin;
	emp[1] = &seller1;
	emp[2] = &seller2;

	//Loop through all employees
	//Ask for and calculate pay
	for(int i = 0; i < 3; ++i)
	{
		emp[i]->AskForPayInfo();
		emp[i]->CalculatePay();
	}
	
	//Now write everyone's pay
	for(int i = 0; i < 3; ++i)
	{
		emp[i]->WritePayInfo();
	}

	cout << "Sweet!\n";
	return 0;
}

