/* Code for exercise 13.15.
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

#include <iostream.h>

namespace Template {
   template<typename T>
   void count_down(T const &count) {
      std::cout << count << '\n';
      if (count)
         count_down(count-1);
   }
   template<>
   void count_down(double const &count) {
      count_down<int>(count);
   }
}

int main() {
   Template::count_down(3.4);
   return 0;
}

