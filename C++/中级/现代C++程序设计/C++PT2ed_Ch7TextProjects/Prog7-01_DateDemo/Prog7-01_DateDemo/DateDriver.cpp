//File: DateDriver.cpp

#include <iostream>
#include "Date.h"

using namespace std;

int main()
{
	cout<<"The first demo program for our Date class. ";
	
	//Make one Date object using the default constructor.
	//It contains our default data--which is today's date.
	Date myDefDate;
	
	//Make another Date object and pass in our own data.
	Date myOwnDate(1,10,1964,"Mom's Birthday");


	//Now ask each Date object for its formatted string.
	string sDefDate = myDefDate.GetFormattedDate();
	string sOwnDate = myOwnDate.GetFormattedDate();

	cout << "\nThe Default Date is:\n";
	cout << sDefDate << endl;

	cout << "My Own Date is:\n";
	cout << sOwnDate << endl;
	
	return 0;
}