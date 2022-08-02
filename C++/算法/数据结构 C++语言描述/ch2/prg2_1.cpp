// File: prg2_1.cpp
// the program tests the calendar class by prompting for a month
// and year and displaying the calendar. runs include invalid
// input that test the program's response to errors.

#include <iostream>
#include <cstdlib>		// for exit()

#include "d_cal.h"      // use calendar class

using namespace std;

int main()
{
   // month and year entered by the user
   int month, year;
	// default month January, 1900
	calendar cal;

   cout << "Enter the month and year: ";
   cin >> month >> year;
	cout << endl;

	// either setYear() or setMonth() can cause an error.
	// place the calls in a try block
	try
	{
		// set the year and month
		cal.setYear(year);
		cal.setMonth(month);
	}

	// catch the dateError exception if setYear()
	// or setMonth() throws it
	catch(const dateError& de)
	{
		// output the error string and return
		cerr << de.what() << endl;
		exit(1);
	}

	// display the calendar
	cal.displayCalendar();

   return 0;
}

/*
Run 1:

Enter the month and year: 2 2003

                     February 2003
    Sun    Mon    Tue    Wed    Thu    Fri    Sat
                                                1
      2      3      4      5      6      7      8
      9     10     11     12     13     14     15
     16     17     18     19     20     21     22
     23     24     25     26     27     28

Run 2:

Enter the month and year: 2 2004

                     February 2004
    Sun    Mon    Tue    Wed    Thu    Fri    Sat
      1      2      3      4      5      6      7
      8      9     10     11     12     13     14
     15     16     17     18     19     20     21
     22     23     24     25     26     27     28
     29

Run 3:

Enter the month and year: 3 2004

                        March 2004
    Sun    Mon    Tue    Wed    Thu    Fri    Sat
             1      2      3      4      5      6
      7      8      9     10     11     12     13
     14     15     16     17     18     19     20
     21     22     23     24     25     26     27
     28     29     30     31

Run 4:

Enter the month and year: 8 1899

calendar setYear(): 1899 is prior to 1900

Run 5:

Enter the month and year: 13 1938

calendar setMonth(): 13 invalid month
*/
