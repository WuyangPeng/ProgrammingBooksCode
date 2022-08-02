//File:  Employee.cpp

#include "Employee.h"
#include <iostream>
#include <string>
using namespace std;

Employee::Employee()
{
	name = "";
	SSN = "";
	salary = 0;
	dept = "";
}

void Employee::AskEmpInfo()
{
	cout << "\nEnter the employee's name    ";
	getline(cin,name);

	cout << "Enter the employee's SSN   ";
	getline(cin,SSN);

	cout << "Enter the dept code ";
	getline(cin,dept);
	
	cout << "Enter the yearly salary   ";
	cin >> salary;
	cin.ignore();
}

void Employee::WriteEmpInfo()
{
	cout << "\nEmployee:  " << name <<  "\n     SSN:  " << SSN;
	cout << "\n    Dept:  " << dept << "\n  Salary:  $" << salary;

}