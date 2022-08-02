/* Code for exercise 6.13.
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
#include <cstring>

char* cat(char const *a, char const *b) {
   std::size_t la = std::strlen(a);
   char *s = new char[la+std::strlen(b)+1];
   std::strcpy(s, a);
   std::strcpy(s+la, b);
   return s;
}


void concatenate(char const *a, char const *b, char *dest) {
   while (*a!='\0') *dest++ = *a++;
   while (*b!='\0') *dest++ = *b++;
   *dest = '\0';
}


int main() {
   char *result1 = cat("C++ ", "Programming");
   printf("%s\n", result1);
   delete[] result1; // New is done in "cat)" function

   char result2[80];
   concatenate("Four ", "Seasons", result2);
   printf("%s\n", result2);
}

