/* Code for exercise 5.7.
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

struct Month {
   char const *name_;
   int length_;
};

int const n_months = 12;

Month const month[n_months]
   = {{"January", 31}, {"February", 28}, {"March", 31},
      {"April", 30}, {"May", 31}, {"June", 30},
      {"July", 31}, {"August", 31}, {"September", 30},
      {"October", 31}, {"November", 30}, {"December", 31}};

int main() {
   for (int k = 0; k!=n_months; ++k)
      std::cout << month[k].name_ << ":\t"
                << month[k].length_ << std::endl;
   return 0;
}

