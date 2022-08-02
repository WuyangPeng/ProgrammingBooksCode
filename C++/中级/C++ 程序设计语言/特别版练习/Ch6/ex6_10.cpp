/* Code for exercise 6.10.
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

This is not a complete program.
Furthermore functions strlen, strcpy and strcmp with equivalent
functionality are already available in the standard library.

This is for illustration purposes only.

*/

#include <assert.h>
#include <cstddef> // For std::size_t

std::size_t strlen(char const *s) {
   assert(s);
   std::size_t len = 0;
   while (s[len])
      ++len;
   return len;
}

void strcpy(char *d, char const *s) {
   assert(s && d);
   do {
      *d++ = *s;
   } while (*s++);
}

enum CStringOrder { FirstBeforeSecond = -1, Same = 0,
                    SecondBeforeFirst = 1};

CStringOrder strcmp(char const *first, char const *second) {
   assert(first && second);
   unsigned char const *f
      = (unsigned char const*)(first);
   unsigned char const *s
      = (unsigned char const*)(second);
   do {
      if ((*f)<(*s))
         return FirstBeforeSecond;
      else
      if ((*s)<(*f))
         return SecondBeforeFirst;
   } while (*(s++) && *(f++));
   assert((*(s-1)==0) && (*(f-1)==0));
   return Same;
}

