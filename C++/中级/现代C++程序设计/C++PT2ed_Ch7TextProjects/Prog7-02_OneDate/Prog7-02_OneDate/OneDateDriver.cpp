//File: OneDateDriver.cpp

#include <iostream>
#include "Date.h"

using namespace std;

int main()
{
	cout<<"The second demo program for our Date class.";
	
	//Use default constructor to make a date object.
	Date myDate;
	
	//Now ask Date object for its formatted string.
	string sDate = myDate.GetFormattedDate();
	cout << "\nThe formatted date is: ";
	cout << sDate;

	//get individual values from Date object
	cout << "\nmonth = " << myDate.GetMonth();
	cout << "\nday = " << myDate.GetDay();
	cout << "\nyear = " << myDate.GetYear();
	cout << "\nday of year = " << myDate.GetDayOfYear();
	
	//leap year?
	cout << "\n" << myDate.GetYear(); 
	if(myDate.isLeapYear() == true)
		cout << " is a leap year" << endl;
	else
		cout << " is NOT a leap year" << endl;

	//now ask user for a new description
	string newDesc;
	cout << "\n\nEnter a new description for today: ";
	getline(cin,newDesc);
	
	//set new description into the object
	myDate.SetDesc(newDesc);
	
	//write again
	sDate = myDate.GetFormattedDate();
	cout << "The date with new description is: \n";
	cout << sDate << endl;
	
	return 0;
}