/* Code for exercise 5.13.
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

This is not a complete program. It just shows a possible "Date"
structure and some functions to process it.

This file is extended to a comlete program in Ch7/ex7_19.cpp.

*/

#include <iostream>
#include <stdlib.h>

struct Date {
   unsigned day_: 5; // Bitfield: use only 5 bits to
                    //  represent this integer member
   unsigned month_: 4;
   int year_: 15;
};

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

std::ostream& operator<<(std::ostream &output, Date &d) {
   output << d.month_ << '/' << d.day_ << '/' << d.year_;
   return output;
}

Date& init(Date &d, unsigned day, unsigned month, int year) {
   d.day_ = day;
   d.month_ = month;
   d.year_ = year;
   return d;
}

