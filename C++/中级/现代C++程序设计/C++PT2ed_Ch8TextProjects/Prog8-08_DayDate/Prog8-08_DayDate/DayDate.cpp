//File: DayDate.cpp

#include "DayDate.h"
#include <ctime>
using namespace std;

DayDate::DayDate()
{
	//default Date gets system date
	FigureDayOfWeek();
}
	
DayDate::DayDate(int m, int d, int y, string desc):
Date(m,d,y,desc)
{
	//can't determine day of week, so we
	//set this to ""
	dayOfWeek = "";
}

string DayDate::GetFormattedDate()
{
	//Get string from parent
	string s = Date::GetFormattedDate();
	
	//This is in the form:
	//Description: Month XX, XXXX
	//So we'll insert the day of week after the:

	int colon = s.find(":");

	s.insert(colon+2, dayOfWeek);
	return s;
}

void DayDate::FigureDayOfWeek()
{
	string weekdays[7] = {"Sunday ", "Monday ",
		"Tuesday ", "Wednesday ", "Thursday ", 
		"Friday ", "Saturday "};

	//Time give us day of week number
	time_t rawtime;
	tm *OStime;

	time(&rawtime);
	OStime = localtime(&rawtime);

	int dayNum = OStime->tm_wday;
	dayOfWeek = weekdays[dayNum];
}

