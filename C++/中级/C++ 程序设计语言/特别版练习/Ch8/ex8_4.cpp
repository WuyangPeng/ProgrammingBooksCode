/* Code for exercise 8.4.
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

void f() {
   throw "Bomb!";
}

int main() {
   try {
      f();
   } catch(char const* s) {
      std::cout << "Caught " << s << std::endl;
   }
   return 0;
}

