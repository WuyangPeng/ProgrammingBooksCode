//File: CPP_Staff.cpp
#include "CPP_Staff.h"
#include <iostream>
using namespace std;

CPP_Staff::CPP_Staff()
{
	hrsWorked = 0;
	hrRate = 0;
}

void CPP_Staff::CalculatePay()
{
	//1.5 * rate for all hours over 40.0
	if(hrsWorked <= 40.0)
		weeklyPay = hrsWorked * hrRate;
	else
	{
		weeklyPay = 40.0 * hrRate 
		+ (hrsWorked - 40.0) * 1.5 * hrRate;
	}
}

void CPP_Staff::AskForPayInfo()
{
	CPP_Employee::AskForPayInfo();

	cout << "Enter hourly rate $ ";
	cin >> hrRate;

	cout << "Enter hours worked this week ";
	cin >> hrsWorked;
	cin.ignore();
}

void CPP_Staff::WritePayInfo()
{
	cout.precision(2);
	cout.setf(ios::fixed);
	cout << "\nStaff person: " << name
		<< "\nWeekly Pay $" << weeklyPay << endl;
}
