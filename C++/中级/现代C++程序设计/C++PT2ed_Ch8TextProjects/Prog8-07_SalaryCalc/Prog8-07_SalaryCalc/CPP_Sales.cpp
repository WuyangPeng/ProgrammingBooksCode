//File:  CPP_Sales.cpp
#include "CPP_Sales.h"
#include <iostream>
using namespace std;

CPP_Sales::CPP_Sales()
{
	commission = 0;
	weeklySales = 0;
}

void CPP_Sales::CalculatePay()
{
	//Sales employees are paid on commission.
	weeklyPay = weeklySales * commission/100.0;
}

void CPP_Sales::AskForPayInfo()
{
	CPP_Employee::AskForPayInfo();
	
	cout << "Enter commission rate in %, i.e. 15 for 15% ";
	cin >> commission;

	cout << "Enter sales for the week ";
	cin >> weeklySales;
	cin.ignore();
}

void CPP_Sales::WritePayInfo()
{
	cout.precision(2);
	cout.setf(ios::fixed);
	cout << "\nSalesperson: " << name
		<< "\nWeekly Pay $" << weeklyPay << endl;
}
