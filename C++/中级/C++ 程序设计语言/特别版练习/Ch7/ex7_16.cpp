/* Code for exercise 7.16.
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

#include <assert.h>
#include <limits>
#include <stdexcept>
#include <string>
#include <iostream.h>

namespace { char const digit[] = "0123456789ABCDEF"; }

void print(int value, int base = 10) {
   int const MXS = 128; // Maximum number of digits
   assert((numeric_limits<int>::radix==2) 
      and (numeric_limits<int>::digits<=MXS));
   if (base<2 or base>16)
      throw std::domain_error(std::string("Print error"));
   char rep[MXS+2];
   rep[MXS+1] = '\0'; // Place an end-of-string marker
   if (value<0) { // Add in the sign if needed
      rep[0] = '-'; // This may have to move later
      value = -value;
   } else
      rep[0] = '+';
   char *p = rep+MXS; // Start at the end
   do { // Move back, inserting digits as you go
      *p-- = digit[value%base];
      value = value/base;
   } while (value);
   *p = rep[0]; // Place the sign just before the most
                // significant digit.
   std::cout << p;
}


int main() {
   for (int base = 2; base!=17; ++base) {
      std::cout << "12345 in base " << base << ": ";
      print(12345, base);
      std::cout << '\n';
   }
   return 0;
}

