//File: Date.h

#ifndef _DATE_H
#define _DATE_H

#include <string>
using namespace std;

class Date
{
	protected:
			int month, day, year;
			string description;
			int dayOfYear;
			bool bLeap;
			void CalcDayOfYear();
			void DetermineLeapYear();

	public:
			Date();
			Date(int m, int d, int y, string desc);
			void SetDate(int m, int d, int y, string desc);
			void SetDesc(string d){ description = d; }

			string GetFormattedDate();

			int GetDayOfYear(){ return dayOfYear;}
			int GetYear(){ return year;}
			int GetMonth(){ return month;}
			int GetDay(){ return day;}
			bool isLeapYear(){ return bLeap; }
};

#endif