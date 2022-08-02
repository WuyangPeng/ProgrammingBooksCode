// File: prg13_1.cpp
// after declaring an hourly employee, Steve Howard, call
// displayEmployeeInfo() to output his data. change the employee's
// hourly pay to $10 using setHourlyPay() and call payrollCheck()
// to pay the worker using the new rate

#include <iostream>

#include "d_emp.h"

using namespace std;

int main()
{
	// declare an hourly employee
	hourlyEmployee hEmp("Steve Howard","896-54-3217",7.50,40);

	// output only the base class information on Steve Howard
	hEmp.employee::displayEmployeeInfo();
	cout << endl;

	// give Steve Howard a raise and output full set of information
	hEmp.setHourlyPay(10.00);
	hEmp.displayEmployeeInfo();
	cout << endl;

	// provide a weekly check
	hEmp.payrollCheck();
	cout << endl;

	return 0;
}

/*
Run:

Name: Steve Howard
Social Security Number:  896-54-3217

Name: Steve Howard
Social Security Number:  896-54-3217
Status:   hourly employee
Payrate:  $10.00 per hour
Work schedule (hours per week) 40.00

Pay Steve Howard (896-54-3217)  $400.00
*/
