//File: CEODriver.cpp
//This program creates one CEO object.

#include <iostream>
using namespace std;
#include "CEO.h"

int main()
{
	cout << "Work, Work, Work. \n";
	
	CEO BigCheese;
	
	cout << "\nAsk for info on the CEO ";
	BigCheese.AskEmpInfo();
	
	cout << "\nWriting info on the CEO ";
	BigCheese.WriteEmpInfo();

	cout << "\n\nNo more work to do.\n\n";
	return 0;
}

