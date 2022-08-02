/* Code for exercise 7.19.
 | 
 | "C++ Solutions--Companion to The C++ Programming Language, Third Edition"
 | by David Vandevoorde; Addison-Wesley 1998; ISBN 0-201-30965-3.
 |
 | Permission to use, copy, modify, distribute and sell this software
 | and its documentation for any purpose is hereby granted without fee.
 | The author makes no representations about the suitability of this
 | software for any purpose.  It is provided "as is" without express or
 | implied warranty.
 `----------------------------------------------------------------------*/

/* Notes:

This program borrow from Ch5/ex5_13.cpp.

*/

#include <iostream>
#include <stdlib.h>

struct Date {
   unsigned day_: 5; // Bitfield: use only 5 bits to
                    //  represent this integer member
   unsigned month_: 4;
   int year_: 15;
};

bool is_leapyear(int y) {
   return !(y%4) and ((y%100) or !(y%400));
} // y is a multiple of 4, but not a multiple of 100
  // that is not a multiple of 400.

struct Month {
   enum { Jan = 1, Feb, Mar, Apr, May, Jun,
          Jul, Aug, Sep, Oct, Nov, Dec };
   static int n_days(int m, int y) {
      return m!=Feb? n_days_[m-1]
                   : (is_leapyear(y)? 29: 28);
   }
private:
   static int const n_days_[12];
};

int const Month::n_days_[12]
   = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

std::istream& operator>>(std::istream &input, Date &d) {
   int const bufsize = 6;
   char buffer[bufsize];
   input.getline(buffer, bufsize, '/');
   d.month_ = atoi(buffer);
   input.getline(buffer, bufsize, '/');
   d.day_ = atoi(buffer);
   int y;
   input >> y;
   d.year_ = y; 
   return input;
}

std::ostream& operator<<(std::ostream &output, Date const &d) {
   output << d.month_ << '/' << d.day_ << '/' << d.year_;
   return output;
}

Date& init(Date &d, unsigned day, unsigned month, int year) {
   d.day_ = day;
   d.month_ = month;
   d.year_ = year;
   return d;
}

Date next_year(Date const &d) {
   Date n;
   n.day_ = d.day_;
   n.month_ = d.month_;
   n.year_ = d.year_+1;
   // February 29, but not a leap year?
   if (n.day_>Month::n_days(n.month_, n.year_)) {
      n.day_ = 1; n.month_ = 3;
   }
   return n;
}

Date next_month(Date const &d) {
   Date n;
   n.day_ = d.day_;
   n.month_ = d.month_%12+1;
   n.year_ = d.year_;
   if (n.month_==1)
      n = next_year(n);
   if (n.day_>Month::n_days(n.month_, n.year_))
      n.day_ = Month::n_days(n.month_, n.year_);
   return n;
}

Date next_day(Date const &d) {
   Date n;
   n.day_ = (d.day_)%Month::n_days(d.month_, d.year_)+1;
   n.month_ = d.month_;
   n.year_ = d.year_;
   if (n.day_==1)
      return next_month(n);
   else
      return n;
}


int MS[] = { 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };

enum DayOfWeek { Sunday = 0, Monday, Tuesday, Wednesday,
                 Thursday, Friday, Saturday };

DayOfWeek day_of_week(Date const &dt) {
   int const y = dt.year_, m = dt.month_, d = dt.day_;
   int const j1 = (1+y-1+(y-1)/4-(y-1)/100+(y-1)/400)%7;
   if (m<=2 or !is_leapyear(y))
      return DayOfWeek((j1+MS[m-1]+d-1)%7);
   else
      return DayOfWeek((j1+MS[m-1]+d)%7);
}

Date next_Monday(Date const &d) {
   DayOfWeek dday = day_of_week(d);
   int const n_days = (dday==Sunday)? 1: 8-dday;
   Date Monday(d);
   for (int k = 0; k!=n_days; ++k)
      Monday = next_day(Monday);
   return Monday;
}

char const *month_name[7] = { "Sunday", "Monday", "Tuesday", "Wednesday",
                              "Thursday", "Friday", "Saturday" };

int main() {
   Date input;
   std::cout << "Input Date (M/D/Y, e.g. 7/21/1969): ";
   std::cin >> input;
   std::cout << "Cannonical output: " << input << '\n';
   std::cout << "This is a " << month_name[day_of_week(input)] << '\n';
   std::cout << "The next day is " << next_day(input) << '\n';
   std::cout << "The next Monday is " << next_Monday(input) << '\n';
   std::cout << "In one month is will be " << next_month(input) << '\n';
   std::cout << "One year from " << input
             << " will be " << next_year(input) << '\n';
   return 0;
}

