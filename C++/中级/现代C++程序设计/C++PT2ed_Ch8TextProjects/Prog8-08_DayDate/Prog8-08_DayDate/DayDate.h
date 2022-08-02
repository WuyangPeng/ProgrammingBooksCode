//DayDate.h
//This new DayDate class includes the day
//of week in its formatted date string.

#include "Date.h"

#ifndef _DAYDATE_H
#define _DAYDATE_H

#include <string>
using namespace std;

class DayDate : public Date
{
private:
	//can only determine day if using 
	//system date
	string dayOfWeek;		//Monday, Tuesday, etc
	void FigureDayOfWeek();
public:
	DayDate();
	DayDate(int m, int d, int y, string desc);
	string GetFormattedDate();
};

#endif


