/* Code for exercise 7.11.
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
#include <stdarg.h>
#include <iostream.h>
#include <stdexcept>


void error(char const *fmt, ...) {
   assert(fmt);
   va_list p;
   va_start(p, fmt);
   for (char const *s = fmt; *s; ++s)
      if (*s!='%')
         std::cerr.put(*s);
      else
         switch (*(++s)) {
         case '%': std::cerr.put('%'); break;
         case 's': std::cerr << va_arg(p, char const*); break;
         case 'c': std::cerr << va_arg(p, char); break;
         case 'd': std::cerr << va_arg(p, int); break;
         default: throw std::domain_error(std::string ("panic"));
         }
   va_end(p);
}

int main() {
   error("A string \"%s\", a single character \'%c\', an integer %d\n"
         "and a percent-symbol \'%%\'.\n",
         "Hello World", '$', 12345);
   return 0;
}

