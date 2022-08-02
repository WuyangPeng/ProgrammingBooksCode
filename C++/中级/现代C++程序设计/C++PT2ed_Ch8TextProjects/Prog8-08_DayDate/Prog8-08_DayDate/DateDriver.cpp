//File: DateDriver.cpp

#include <iostream>
#include "DayDate.h"

using namespace std;

int main()
{
	cout<<"The DayDate class derived from Date. \n";

	//First get a Date using default constructors.
	//This will give us system date and day.

	cout << "\nMake and show default date.\n";
	DayDate myDate;

	//Now ask the DayDate object for its formatted string.
	cout << myDate.GetFormattedDate() << endl;

	//Now make a date
	cout << "\nMake and show our own date.\n";
	DayDate theDate(3,14, 1998,"Jason's Birthday");
	cout << theDate.GetFormattedDate() << endl;
	
	return 0;
}