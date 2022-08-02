#ifndef CALENDAR_CLASS
#define CALENDAR_CLASS

#include <iostream>
#include <iomanip>
#include <string>

#include "d_date.h"
#include "d_except.h"

using namespace std;

class calendar
{
   public:
      calendar(int m = 1, int y = 1900);
			// initialize the month and year for display.
			// precondition: month is in the range 1 to 12 and year
			// is 1900 or later

      void displayCalendar() const;
			// display the calendar with a header and a table of dates

      int getMonth() const;
			// return the current month for the calendar

      int getYear() const;
			// return the current year for the calendar

      void setMonth(int m);
			// update the month for the calendar
			// precondition:  m must be in the range 1 to 12

      void setYear(int y);
			// update the year for the calendar
			// precondition:  y must be >= 1900

   private:
      date d;
			// date object representing the 1st day in the
			// specified the month and year

      int firstDay() const;
			// return day of the week (0-6) holding first day of month

      void displayTitle() const;
			// output month and year followed by names for days
			// of the week

      void displayDates() const;
			// output the dates under the correct days of the week
};

// constructor. check for valid date and initialize attributes
calendar::calendar(int mm, int yyyy)
{
   // do error checking before continuing
   if (mm < 1 || mm > 12)
		throw dateError("calendar constructor:", mm, "invalid month");

   if (yyyy < 1900)
		throw dateError("calendar constructor:", yyyy, "is prior to 1900");

   // assign 1st of month mm in year yyyy
   d = date(mm,1,yyyy);
}

// return the first day of the month
int calendar::firstDay() const
{
   int y, year = d.getYear();

   // tmpDate is always Jan. 1 for the years y=1900 to the
   // current year. used to check for leap year
   date tmpDate(1,1,1900);
   int day = 1;   // set day to Monday, January 1, 1900

   for (y = 1900; y < year; y++)
   {
      tmpDate.setYear(y);
      if (tmpDate.isLeapYear())
          day += 366;
      else
         day += 365;
   }

   // add days from Jan 1 to first of month.  note
   // that we must subtract 1, since Jan 1 is day 1
   day += d.numberOfDays()-1;

	// day of week is remainder after dividing day by 7
   return day%7;
}

// output month and year followed by labels for days of week
void calendar::displayTitle() const
{
   // an initialized array of strings for the month names
   static string monthName[13] =
      {"","January","February","March","April","May",
       "June","July","August","September","October",
       "November","December"};

   // use calendar month as an index into the array
   cout << setw(29) << monthName[d.getMonth()];

   // output the year
   cout << setw(5) << d.getYear();
   cout << endl;

   // output names for days of the week
   cout << "    Sun    Mon    Tue    Wed    Thu    Fri    Sat"
        << endl;
}

// output dates of the calendar under the correct days of week
void calendar::displayDates() const
{
   // set number of days in the month
   int monthLength = d.daysInMonth();
   int dayValue = 1;
   int day = 0, first = firstDay();

   // skip spaces up to the first day of the month
   while (day < first)
   {
      cout << setw(7) << " ";
      day++;
   }

   // output the dates 1 .. monthLength
   while (dayValue <= monthLength)
   {
      cout << setw(7) << dayValue;
      dayValue++;
      // is next day Sunday of a new week?
      if (day == 6)
         cout << endl;
      day = (day+1)%7;
   }

   // skip unused days in the last week
   if (day != 0)
      cout << endl;
}

// update the current month
void calendar::setMonth(int mm)
{
   // verify that mm is a valid month
   if (mm < 1 || mm > 12)
		throw dateError("calendar setMonth():", mm, "invalid month");

   // set d to new month
   d.setMonth(mm);
}

// update the current year
void calendar::setYear(int yyyy)
{
   // verify that yyyy is valid
   if (yyyy < 1900)
		throw dateError("calendar setYear():", yyyy, "is prior to 1900");

   // set d to new year
   d.setYear(yyyy);
}

// return the current month
int calendar::getMonth() const
{
   return d.getMonth();
}

// return the current year
int calendar::getYear() const
{
   return d.getYear();
}

// display the calendar
void calendar::displayCalendar() const
{
   displayTitle();   // output the month/year title
   displayDates();   // output the grid of dates
}

#endif   // CALENDAR_CLASS
