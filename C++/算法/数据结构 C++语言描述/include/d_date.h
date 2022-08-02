#ifndef DATE_CLASS
#define DATE_CLASS

#include <iostream>
#include <iomanip>
#include <string>

#include "d_except.h"

using namespace std;

class date
{
   public:
      date (int mm=1, int dd=1, int yyyy=1900);
			// supply date in format MM/DD/YYYY
			// preconditions: 1 <= mm <= 12,
			//                1 <= dd <= daysInMonth()

      void writeShortDate () const;
			// output the date in the format "MM/DD/YYYY"
      void writeLongDate () const;
			// output the date in the format "month day, year"

      void incrementDate(int ndays);
			// add ndays days to the date
			// precondition: 0 <= ndays <= 365

      int numberOfDays() const;
			// return the number of days into the year

      int getMonth() const;
			// return the month as integer value 1 to 12
      int getDay() const;
			// return day of the month
      int getYear() const;
			// return the year

      void setMonth(int mm);
			// update the month
			// precondition: 1 <= mm <= 12
      void setDay(int dd);
			// update the day
			// precondition: 1 <= dd <= daysInMonth()
      void setYear(int yyyy);
			// update the year
			// precondition:  if the date is February 29,
			//                yyyy must be a leap year
      int daysInMonth() const;
			// return number of days in the month

      bool isLeapYear() const;
			// is the current year a leap year (true/false)

   private:
      enum monthName {Jan = 1, Feb, Mar, Apr, May, Jun,
                      Jul, Aug, Sep, Oct, Nov, Dec};
			// private type used by date

      int month, day, year;
			// private members that specify the date

};

// constructor. month, day, year given as integer
// values mm dd yyyy
date::date (int mm, int dd, int yyyy):
      month(mm), day(dd), year(yyyy)
{
   if (month < 1 || month > 12)
		throw dateError("date constructor:", month, "invalid month");

   if (day <= 0 || day > daysInMonth())
		throw dateError("date constructor:", day, "invalid day of month");
}

// write date in the format "MM/DD/YYYY"
void date::writeShortDate () const
{
   // save current format flags and fill character
   ios_base::fmtflags currentFlags = cout.flags();
   char currentFill = cout.fill();

   // enable right justification
   cout.setf(ios::right,ios::adjustfield);

   // output the month right-justified in
   // two character positions, blank fill
   cout.fill(' ');
   cout << setw(2) << month;

   // set fill char to '0'
   cout.fill('0');
   cout << '/' << setw(2) << day << '/' << year;

   // restore the fill char and the format flags
   cout.fill(currentFill);
   cout.setf(currentFlags);
}

// write date with full month name
void date::writeLongDate() const
{
   // array begins with empty string corresponding to month 0
   static string monthNames[] =
      {"", "January", "February", "March", "April", "May",
       "June", "July", "August", "September", "October",
       "November", "December"
      };
   // use month as index into monthNames
   cout << monthNames[month] << " " << day << ", " << year;
}

// add ndays days to the date. ndays must be in the range
// 0 <= ndays <= 365
void date::incrementDate(int ndays)
{
   int totalDays, daysInYear = 365;
   int addDay;

   if (ndays < 0 || ndays > 365)
		throw dateError("date incrementDate():", ndays, "is out of range");

   if(isLeapYear())
   {
      addDay = 1;
      daysInYear++;
   }
   else
      addDay = 0;

   totalDays = numberOfDays() + ndays;
   if (totalDays/daysInYear == 1 && totalDays%daysInYear != 0)
   {
      year++;
      if(isLeapYear())
         addDay = 1;
      else
         addDay = 0;
      totalDays = totalDays % daysInYear;
   }

   if (totalDays <= 31)
   {
      month = 1;
      day = totalDays;
   }
   else if (totalDays <= 59 + addDay)
   {
      month = 2;
      day = totalDays - 31;
   }
   else if (totalDays <= 90 + addDay)
   {
      month = 3;
      day = totalDays - (59 + addDay);
   }
   else if (totalDays <= 120 + addDay)
   {
      month = 4;
      day = totalDays - (90 + addDay);
   }
   else if (totalDays <= 151 + addDay)
   {
      month = 5;
      day = totalDays - (120 + addDay);
   }
   else if (totalDays <= 181 + addDay)
   {
      month = 6;
      day = totalDays - (151 + addDay);
   }
   else if (totalDays <= 212 + addDay)
   {
      month = 7;
      day = totalDays - (181 + addDay);
   }
   else if (totalDays <= 243 + addDay)
   {
      month = 8;
      day = totalDays - (212 + addDay);
   }
   else if (totalDays <= 273 + addDay)
   {
      month = 9;
      day = totalDays - (243 + addDay);
   }
   else if (totalDays <= 304 + addDay)
   {
      month = 10;
      day = totalDays - (273 + addDay);
   }
   else if (totalDays <= 334 + addDay)
   {
      month = 11;
      day = totalDays - (304 + addDay);
   }
   else if (totalDays <= 365 + addDay)
   {
      month = 12;
      day = totalDays - (334 + addDay);
   }
}


// determine the number of days into the year
int date::numberOfDays() const
{
   // assign a place holder value of 0 for monthLength[0]
   int monthLength[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};

   int daysToDate = 0, i;

   // add up all the days in the preceding months
   for (i = 1; i < month; i++)
      daysToDate += monthLength[i];

   // if year is a leap year and the month is March or later,
   // increment daysToDate.  use member function isLeapYear()
   if (isLeapYear() && month > 2)
      daysToDate += day + 1;
   else
      daysToDate += day;

   return daysToDate;
}

// return the month as integer value 1 to 12
int date::getMonth() const
{
   return month;
}

// return day of the month
int date::getDay() const
{
   return day;
}

// return the year
int date::getYear() const
{
   return year;
}

// assign a new month
void date::setMonth(int mm)
{
   // verify that mm is in the range 1 to 12
   if (mm < 1 || mm > 12)
		throw dateError("date setMonth():", mm, "invalid month");

   month = mm;
}

// assign a new day of current month
void date::setDay(int dd)
{
   // verify that dd is in correct range for
   // the current month
   if (dd <= 0 || dd > daysInMonth())
		throw dateError("date setDay():", dd, "invalid day of month");

   day = dd;
}

void date::setYear(int yyyy)
{
   // assign the new year
   year = yyyy;

   // if the date is February 29, yyyy must be a
   // leap year
   if (month == 2 && day == 29 && !isLeapYear())
		throw dateError("date setYear():",
							 year, "Not a leap year. February 29 invalid");
}

// return the number of days in the month
int date::daysInMonth() const
{
   int monthLength;

   // monthName(month) converts integer month to the
   // equivalent monthName object
   switch (monthName(month))
   {
      case Jan:
      case Mar:
      case May:
      case Jul:
      case Aug:
      case Oct:
      case Dec:   monthLength = 31;    // months with 31 days
                  break;

      case Apr:
      case Jun:
      case Sep:
      case Nov:   monthLength = 30;    // months with 30 days
                  break;

      case Feb:   if (isLeapYear())    // special case of Feb
                     monthLength = 29;
                  else
                     monthLength = 28;
                  break;
   }
   return monthLength;
}

// is the current year a leap year (true/false)
bool date::isLeapYear() const
{
   if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
      return true;
   else
      return false;
}

#endif   // DATE_CLASS
