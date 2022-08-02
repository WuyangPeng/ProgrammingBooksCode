/* Code for exercise 7.3.
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

int main(int argc, char *argv[]) {
   if (argc<2) {
      cout << "Hi! Why not pass me arguments?\n";
   } else {
      for (int k = 1; k!=argc; ++k)
         cout << "Hello, " << argv[k] << "!\n";
   }
   return 0;
}

