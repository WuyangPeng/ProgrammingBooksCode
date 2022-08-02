#ifdef _MSC_VER
// disable warning messages that identifier was truncated
// to 'number' characters in the debug information
#pragma warning(disable:4786)
#endif	// _MSC_VER

// File: prg13_3.cpp
// declare four employees and insert each one into a map whose key
// is SSN of a worker and whose value is a pointer to the employee
// object. in a loop, prompt for Social Security Number. use find()
// to search map for an entry with that SSN. if located, pass
// pointer value to function pay() that processes the paycheck for
// employee. if the SSN is not valid, output a message. terminate
// the program when the user inputs the SSN "000-00-0000"

#include <iostream>
#include <fstream>
#include <map>

#include "d_emp.h"	// include the employee hierarchy

using namespace std;

// issue the pay check to the employee pointed to by emp
void pay(employee* emp);

int main()
{
	// declare four employees
	salaryEmployee sEmpA ("Bill Roberts","837-57-8293", 950.00);
	salaryEmployee sEmpB ("Dena Thomas","538-27-4981", 1300.00);
	hourlyEmployee hEmpA ("Sally Gere","583-73-5081", 15.00, 40.00);
	hourlyEmployee hEmpB ("Ty Le","654-20-2981", 30.00, 30.00);

	// database is a map with SSN as the key and a pointer to the
	// employee as the value
	map<string, employee*> empMap;
	string ssn;

	// insert the employees into the map
	empMap["837-57-8293"] = &sEmpA;
	empMap["538-27-4981"] = &sEmpB;
	empMap["583-73-5081"] = &hEmpA;
	empMap["654-20-2981"] = &hEmpB;

	while (true)
	{
		cout << "Enter social security number: ";
		cin >> ssn;
		if (ssn == "000-00-0000")
			break;

		// search for ssn in the map and pay the
		// employee if found
		if (empMap.find(ssn) != empMap.end())
			pay(empMap[ssn]);
		else
			cout << "Not a recognized employee" << endl;
		cout << endl;
	}

	return 0;
}

void pay(employee* emp)
{
	// execute payrollCheck() for the type of employee
	// emp points at
	emp->payrollCheck();
}

/*
Run:

Enter social security number: 538-27-4981
Pay Dena Thomas (538-27-4981)  $1300.00

Enter social security number: 691-45-7651
Not a recognized employee

Enter social security number: 654-20-2981
Pay Ty Le (654-20-2981)  $900.00

Enter social security number: 000-00-0000
*/
