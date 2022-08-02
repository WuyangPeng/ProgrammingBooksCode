/* Code for exercise 8.7.
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
#include <ctime>

int seven(bool do_throw) {
   if (do_throw)
      throw 7;
   else return 7;
}

int main() {
   unsigned long return_count = 0;
   std::clock_t end = std::clock()+5*CLOCKS_PER_SEC;
   do {
      int sept = seven(false);
      ++return_count;
   } while (std::clock()<end);
   std::cout << "Plain return: " << return_count/5
                                 << " times per second\n";
   return_count = 0;
   end = std::clock()+5*CLOCKS_PER_SEC;
   do {
      try {
         seven(true);
      } catch(int sept) {
         ++return_count;
      }
   } while (std::clock()<end);
   std::cout << "Thrown return: " << return_count/5
                                  << " times per second\n";
   return 0;
}

