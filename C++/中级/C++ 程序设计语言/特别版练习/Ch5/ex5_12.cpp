/* Code for exercise 5.12.
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

#include <assert.h>
#include <stdio.h>
#include <string>
//using std::string;

size_t count_charpair(string const &s, char a, char b) {
   size_t result = 0;
   string::const_iterator p = s.begin();
   while(p!=s.end())
      if (*p++==a)
         if (p!=s.end() && *p==b)
            ++result;
   return result;
}

size_t count_charpair(char const *s, char a, char b) {
   assert(s);
   size_t result = 0;
   while (*s)
      if (*s++==a)
         if (*s==b)
            ++result;
   return result;
}

int main() {
   printf("Pairs ab in \"aabbaba\": %d\n",
          count_charpair("aabbaba", 'a', 'b'));
   printf("Pairs ab in string(\"aabbaba\"): %d\n",
          count_charpair(string("aabbaba"), 'a', 'b'));
}

