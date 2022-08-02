//File:  Employee.h

#ifndef  _EMPLOYEE_H
#define  _EMPLOYEE_H

#include <string>
using namespace std;

class Employee
{
protected:
	string name,SSN, dept;
	float salary;
public:
	Employee();
	void AskEmpInfo();
	void WriteEmpInfo();
};

#endif