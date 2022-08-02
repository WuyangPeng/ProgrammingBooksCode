/* Code for exercise 7.18.
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

#include <stdio.h>
#include <string>
#include <stdexcept>

int factorial(int a) {
   if (a<0) throw std::domain_error(std::string("negative factorial"));
   int result = 1;
   while (a>1)
      result *= a--;
   return result;
}

int main() {
   printf("7! = %d\n", factorial(7));
   return 0;
}

