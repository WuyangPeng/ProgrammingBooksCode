/* Code for exercise 20.1.
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

#include <iostream>
#include <stddef.h>
#include <stdlib.h>
#include <string>
#include <string.h>


std::string dotconnect1(std::string const &a, std::string const &b) {
   return a+'.'+b;
}


std::string dotconnect2(std::string const &a, std::string const &b) {
   std::string result(a.size()+b.size()+1, '.');
   result.replace(0, a.size(), a);
   result.replace(a.size()+1, b.size(), b);
   return result;
}


char* dotconnect3(char const *a, char const *b) {
   size_t alen = strlen(a), blen = strlen(b);
   char *result = (char*)malloc(alen+blen+2);
   memcpy(result, a, alen);
   result[alen] = '.';
   memcpy(result+alen+1, b, blen);
   result[alen+blen+2] = '\0';
   return result;
}


int main() {
   std::string sa("blue"), sb("blob");
   char const *ca = "blue", *cb = "blob";
   std::cout << "dotconnect 1: " << dotconnect1(sa, sb) << '\n';
   std::cout << "dotconnect 2: " << dotconnect2(sa, sb) << '\n';
   std::cout << "dotconnect 3: " << dotconnect1(ca, cb) << '\n';
   return 0;
}


