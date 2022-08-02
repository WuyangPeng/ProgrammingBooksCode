/* Code for exercise 5.6.
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

/* Notes:

This file should not compile properly and instead your compiler
should diagnose various errors.

*/

#include <iostream>

void f(char c) { std::cout << c << std::endl; }
void g(char &c) { std::cout << c << std::endl; }
void h(char const &c) { std::cout << c << std::endl; }

int main() {
   char c;
   unsigned char uc;
   signed char sc;
   f('a');
   f(49);
   f(3300); // OK, but probably dangerous
   f(c);
   f(uc);
   f(sc);
   g('a'); // Error
   g(49); // Error
   g(3300); // Error
   g(c);
   g(uc); // Error: unsigned char->char produces rvalue
   g(sc); // Error: signed char->char produces rvalue
   h('a'); // Temporary
   h(49); // Temporary
   h(3300); // Temporary, probably dangerous
   h(c);
   h(uc); // Temporary (possibly dangerous)
   h(sc); // Temporary (possibly dangerous)
   return 0;
}

