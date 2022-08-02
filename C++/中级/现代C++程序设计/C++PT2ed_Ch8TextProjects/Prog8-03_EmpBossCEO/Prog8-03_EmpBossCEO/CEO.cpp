//File:  CEO.cpp

#include "CEO.h"
#include <iostream>
using namespace std;

void CEO::AskEmpInfo()
{
	Boss::AskEmpInfo();
	cout << "\nHow many shares do I get?  ";
	cin >> stock_options;
	cin.ignore();

}

void CEO::WriteEmpInfo()
{
	Boss::WriteEmpInfo();
	cout << "\n  Shares:  " << stock_options;
}

