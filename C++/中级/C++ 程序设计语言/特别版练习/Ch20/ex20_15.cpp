/* Code for exercise 20.15.
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

#include <ctype.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>


#if !defined C_STYLE

bool read_string(std::string &s) {
   int const buffer_size = 100;
   char buffer[buffer_size+1];
   int i = 0, c;
   while ((c = std::cin.get()) && (std::cin) && isspace(c));
   while ((c = std::cin.get()) && (std::cin) && !isspace(c)
          && i!=buffer_size) {
      buffer[i++] = char(c);
   }
   buffer[i] = '\0';
   s.assign(buffer, i);
   if (std::cin) {
      std::cin.putback(c);
      if (!isspace(c)) {
         std::string remainder;
         read_string(remainder);
         s.append(remainder);
      }
      return true;
   } else
      return false;
};

#else // C_STYLE is defined:

bool read_string(std::string& s) {
   int const buffer_size = 100;
   char buffer[buffer_size+1];
   int i = 0, c;
   while ((c = getc(stdin))!=EOF && isspace(c));
   while ((c = getc(stdin))!=EOF && !isspace(c) && i!=buffer_size) {
      buffer[i++] = char(c);
   }
   buffer[i] = '\0';
   s.assign(buffer, i);
   if (c!=EOF) {
      ungetc(c, stdin);
      if (!isspace(c)) {
         std::string remainder;
         read_string(remainder);
         s.append(remainder);
      }
      return true;
   } else
      return false;
};

#endif


int main() {
   std::string word;
   int n = 0;
   bool not_eof;
   clock_t start = clock();
#if defined(SIMPLE)
   while (std::cin >> word) ++n;
#else
   do {
      not_eof = read_string(word);
      ++n;
   } while (not_eof);
#endif
   printf("Read %d words in %f seconds.\n",
          n, (clock()-start)/CLOCKS_PER_SEC);
   return 0;
}

