/* Code for exercise 6.16.
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

#include <limits>
#include <stdexcept>
#include <string>
#include <stdio.h>

#if 0
using std::domain_error;
using std::range_error;
using std::string;
#endif

namespace {
   inline int digit(char c, int base) {
      int value;
      switch (c) {
         case '0': value = 0; break;
         case '1': value = 1; break;
         case '2': value = 2; break;
         case '3': value = 3; break;
         case '4': value = 4; break;
         case '5': value = 5; break;
         case '6': value = 6; break;
         case '7': value = 7; break;
         case '8': value = 8; break;
         case '9': value = 9; break;
         case 'a': case 'A': value = 10; break;
         case 'b': case 'B': value = 11; break;
         case 'c': case 'C': value = 12; break;
         case 'd': case 'D': value = 13; break;
         case 'e': case 'E': value = 14; break;
         case 'f': case 'F': value = 15; break;
         default:
            throw domain_error(string("invalid digit"));
      }
      if (value>=base)
         throw domain_error(string("invalid digit"));
      return value;
   }

   inline char next_char(char const *&p) {
      if (*p!='\\') // \ is special; hence '\\'
         return *p++;
      else { // 3 octal digits:         
         int char_value = digit(p[1], 8)*64
                         +digit(p[2], 8)*8
                         +digit(p[3], 8);
         if (char_value>std::numeric_limits<char>::max()
          or char_value<std::numeric_limits<char>::min())
            throw domain_error(string("not a char"));
         p += 4; // backslash and 3 octal digits
         return char_value;
      }
   }

   void load_first_digit(char const *&s, int &value,
                         bool &is_negative, int &base) {
      char c1 = next_char(s);
      is_negative = c1=='-';
      if (c1=='-' || c1=='+')
         c1 = next_char(s);
      if (c1=='\0') { // "", "-" and "+" are illegal
         throw domain_error(string("invalid input"));
      } else if (c1!='0') {
         base = 10;
      } else {
         char const *p = s;
         char c2 = next_char(p);
         if (c2=='x' || c2=='X') { // "0x..."?
            base = 16;
            s = p;
            c1 = next_char(s);
         } else { // c2!='x' and c2!='X'
             base = 8; // I.e., even "0" is treated as octal
         }
      }
      value = digit(c1, base);
   }
} // End unnamed namespace (helper functions)

int atoi(char const *s) {
   int value, base;
   bool is_negative;
   load_first_digit(s, value, is_negative, base); 
   while (char c = next_char(s)) {
      if (value>std::numeric_limits<int>::max()/base)
         throw range_error(string("out-of-range"));
      value *= base;
      int d = digit(c, base);
      if (value>std::numeric_limits<int>::max()-d)
         throw range_error(string("out-of-range"));
      value += d;
   }
   return is_negative? -value: value;
}

int main() {
   printf("atoi(\"123\") = %d\n", atoi("123"));
   printf("atoi(\"0123\") = %d\n", atoi("0123"));
   printf("atoi(\"0x123\") = %d\n", atoi("0x123"));
}
