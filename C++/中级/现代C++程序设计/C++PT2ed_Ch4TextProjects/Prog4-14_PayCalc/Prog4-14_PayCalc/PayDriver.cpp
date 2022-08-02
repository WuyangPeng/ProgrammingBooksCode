//File:  PayDriver.cpp
//This file contains the main function for
//the Weekly Pay Calculation program.

#include "PayFunctions.h"
#include <iostream>
using namespace std;

int main()
{
	cout <<"This is the Pay Calculation Program.\n"
		<< "We'll calculate three employees' weekly salary. \n";

	//declare variables;
	float managerPay, salesPay, staffPay;

	//first a manager making $45000/year
	managerPay = CalcPay(45000.00);

	//next a salesperson who sold $10000 worth of good
	//who has a 20% commission and $200 base pay
	salesPay = CalcPay(200.00, 10000.00, 20);

	//last, a staff person who earns $12/hr and 
	//worked 45 hours this week
	staffPay = CalcPay(45,12.00);

	cout.setf(ios::fixed);
	cout.precision(2);
	cout << "\nWeekly Pay Results"
		<< "\n     Manager: $ " << managerPay
		<< "\n Salesperson: $ " << salesPay
		<< "\nStaff person: $ " << staffPay << endl;

	return 0;
}
