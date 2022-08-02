/* Code for exercise 6.7.
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

int gi = 0;
int f(int a, int b) {
   std::cout << "(a b gi) = (" << a << ' ' << b
                                    << ' ' << gi << ")\n";
   return a+b+gi;
}

int main() {
   f(++gi, ++gi);
   f(1, 2)+f(3, 4);
   if (f(5, 6)==++gi);
   f((gi++)+(gi++), 0);
   gi & 32/gi;
   return 0;
}

