/* Code for exercise 5.10.
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

#include <iostream>
#include <algorithm>
#include <string>

// If your compiler does not yet place its standard library in
// namespace 'std', omit the following four lines.
using std::copy;
using std::cout;
using std::ostream_iterator;
using std::string;

int const n_months = 12;

string month[n_months]
    = { string("January"), string("February"),
        string("March"), string("April"),
        string("May"), string("June"),
        string("July"), string("August"),
        string("September"), string("October"),
        string("November"), string("December") };

int main() {
   copy(&month[0], &month[0]+n_months,
         ostream_iterator<string>(cout, "\n"));
   return 0;
}

