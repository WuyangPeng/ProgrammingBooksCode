//File: DateTimeDemo.cpp
//This program shows how to access the 
//computer's system time and date.

//We use the C language time and date functions.

#include <iostream>
#include <ctime>		
using namespace std;

int main()
{
	cout << "What is the date and time?  \n";
	
	//If you just need a char array for the
	//date and time, can use _strtime and _strdate.

	char timeRightNow[20];
	char dateRightNow[20];

	// The _strtime function fills a character 
	// array with the system time.
	// The _strdate function gives us the date.

	_strtime(timeRightNow);  
	_strdate(dateRightNow);
	cout << "\nFrom the _strdate and _strtime functions:";
	cout << "\nThe date is " << dateRightNow
		<< "\nThe system time is " << timeRightNow ; 

	// If we need integer values for hr, min, sec
	// or month, day year, we use a time_t struct 
	// that is defined in time.h

	// UTC time format variable
	time_t SystemTime;         


	// Pass the address of SystemTime to time() 
	// It fills the SystemTime with UTC seconds

	time(&SystemTime);  


	// Need to convert UTC to something we can use.
	// The localtime function does that.
	// Declare tm ptr to hold individual time info

	struct tm *OStime;      

	// Pass the address of SystemTime to localtime() 
	// It converts to tm struct, which has all we need.

	OStime = localtime(&SystemTime);  

	// Now we access the hr, min, sec of system time,
	// by using the -> operator
	
	int hour = OStime->tm_hour;
	int min = OStime->tm_min;
	int sec = OStime->tm_sec;

	int month = OStime->tm_mon;	//0 = Jan, 11 = Dec
	int day = OStime->tm_mday;
	int year = OStime->tm_year;	//based from 1900

	cout << "\n\nFrom the data struct:";
	cout << "\nThe date is " << month + 1 
		<< "/" << day << "/" << year + 1900;
	cout << "\nThe time is " << hour << ":" 
			<< min << ":" << sec << endl;

	return 0;
}

