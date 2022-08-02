/* Code for exercise 11.10.
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

inline char const* String::c_string() const {
   return rep->s;
}

int main() {
   String s("Hello, World!");
   printf("%s\n", s.c_string());
   return 0;
}

