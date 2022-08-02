/* Code for exercise 8.5.
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
#include <cstdlib>

int level = 0;

void f(int throw_level) {
   ++level;
   if (throw_level==level)
      throw level;
   else
      f(throw_level);
}

int main(int argc, char* argv[]) {
   try {
      if (argc<2 or std::atoi(argv[1])<1)
         throw 0;
      else
         f(std::atoi(argv[1]));
   } catch (int depth) {
      std::cout << "Caught level "
                << depth << " exception.\n";
   }
   return 0;
}

