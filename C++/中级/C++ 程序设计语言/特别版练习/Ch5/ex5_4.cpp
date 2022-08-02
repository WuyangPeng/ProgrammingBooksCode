/* Code for exercise 5.4.
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

void swap_values(int *p1, int *p2) {
   int tmp = *p1;
   *p1 = *p2;
   *p2 = tmp;
}

void swap(int &v1, int &v2) {
   int tmp = v1;
   v1 = v2;
   v2 = tmp;
}

int main() {
   int a = 3, b = 27;
   std::cout << "Initially:\n";
   std::cout << "a = " << a << "  b = " << b << '\n';
   swap_values(&a, &b);
   std::cout << "After swap_values:\n";
   std::cout << "a = " << a << "  b = " << b << '\n';
   swap(a, b);
   std::cout << "After swap:\n";
   std::cout << "a = " << a << "  b = " << b << '\n';
}

