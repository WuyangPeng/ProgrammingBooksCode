/* Code for exercise 6.14.
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

#include <algorithm>
#include <cstring>
#include <cstdio>

void rev(char *s) { std::reverse(s, s+std::strlen(s)); }

char ship[] = "Titanic";

int main() {
   printf("Before: %s\n", ship);
   rev(ship);
   printf("After:  %s\n", ship);
}

