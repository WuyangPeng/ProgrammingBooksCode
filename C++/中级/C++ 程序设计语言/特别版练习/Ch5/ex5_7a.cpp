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

int const n_months = 12;

char const *month[n_months]
   = {"January", "February", "March", "April",
      "May", "June", "July", "August",
      "September", "October", "November", "December"};

int const month_length[n_months]
   = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
   for (int k = 0; k!=n_months; ++k)
      std::cout << month[k] << ":\t"
                << month_length[k] << std::endl;
   return 0;
}

