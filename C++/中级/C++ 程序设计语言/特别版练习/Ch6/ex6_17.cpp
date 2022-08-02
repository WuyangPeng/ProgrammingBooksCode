/* Code for exercise 6.17.
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

#include <stdio.h>

namespace { char const digit[] = "0123456789"; }

char* itoa(int i, char b[]) {
   char *p = b;
   if (i<0) { // Add in the sign if needed
      *p++ = '-';
      i = -i;
   }
   int shifter = i;
   do { // Move to where the representation ends
      ++p;
      shifter = shifter/10;
   } while (shifter);
   *p = '\0';
   do { // Move back, inserting digits as you go
      *--p = digit[i%10];
      i = i/10;
   } while (i);
   return b;
}

int main() {
   char buf[80];
   printf("itoa(45*12345679) = \"%s\"\n", itoa(45*12345679, buf));
   return 0;
}

