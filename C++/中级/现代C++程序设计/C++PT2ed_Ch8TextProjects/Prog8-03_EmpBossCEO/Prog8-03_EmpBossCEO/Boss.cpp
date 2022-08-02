//File:  Boss.cpp

#include <iostream>
using namespace std;

#include "Boss.h"

void Boss::AskEmpInfo()
{
	Employee::AskEmpInfo();   //ask for name, SSN, dept, salary
	cout << "\nWhat is my bonus this year? $$$$$$  ";
	cin >> bonus;
	cin.ignore();
}

void Boss::WriteEmpInfo()
{
	Employee::WriteEmpInfo();   //writes name, SSN, dept, salary
	cout << "\n   Bonus:  $" << bonus;
}
