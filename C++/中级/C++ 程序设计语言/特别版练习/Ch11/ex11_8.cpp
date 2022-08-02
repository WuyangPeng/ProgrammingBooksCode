/* Code for exercise 11.8.
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

#include "str.hpp"
#include <stdio.h>

inline String String::operator()(int left, int right) {
   check(left); check(right);
   if (left<=right) {
      char *a = new char[right-left+2];
      std::strncpy(a, rep->s+left, right-left+1);
      a[right-left+1] = '\0';
      String result(a);
      delete[] a;
      return result;
   } else { // return an "empty string"
      return String();
   }
}

// Steal this from ex11_10.cpp:
inline char const* String::c_string() const {
   return rep->s;
}

int main() {
   String s("Hello, World!");
   printf("%s\n", s(3, 8).c_string());
   return 0;
}

