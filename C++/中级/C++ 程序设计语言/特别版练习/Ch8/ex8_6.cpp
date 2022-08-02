/* Code for exercise 8.6.
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
#include <string>
#include <cstdlib>
#include <ctime>

int level;

void f_without_string(int throw_level) {
   ++level;
   if (throw_level==level)
      throw level;
   else
      f_without_string(throw_level);
}

void f_with_string(int throw_level) {
   std::string s;
   ++level;
   if (throw_level==level)
      throw level;
   else
      f_with_string(throw_level);
}

int main(int argc, char* argv[]) {
   int throw_level = (argc<2 or std::atoi(argv[1])<1)?
                     0: std::atoi(argv[1]);
   unsigned long catch_count = 0;
   std::clock_t end = std::clock()+5*CLOCKS_PER_SEC;
   do {
      level = 0;
      try {
         if (throw_level==0)
            throw 0;
         else
            f_without_string(throw_level);
      } catch (int depth) {
         ++catch_count;
      }
   } while (std::clock()<end);
   std::cout << "Without string: " << catch_count/5
                                   << " catches/second.\n";
   catch_count = 0;
   end = std::clock()+5*CLOCKS_PER_SEC;
   do {
      level = 0;
      try {
         if (throw_level==0)
            throw 0;
         else
            f_with_string(throw_level);
      } catch (int depth) {
         ++catch_count;
      }
   } while (std::clock()<end);
   std::cout << "With string: " << catch_count/5
                                << " catches/second\n";
   return 0;
}

