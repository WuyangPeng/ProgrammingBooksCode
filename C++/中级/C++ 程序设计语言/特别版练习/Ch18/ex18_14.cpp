/* Code for exercise 18.14.
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
#include <iostream>
#include <iterator>
#include <new>
#include <vector>
#include <string>

void error(char const *name, char const *msg) {
   std::cerr << name << msg << '\n';
   std::exit(1);
}

int main(int argc, char *argv[]) {
   try {
      if (argc!=2)
         error(argv[0],
               ": unexpected number of arguments.\n");
      int length = std::strlen(argv[1]);
      std::sort(argv[1], argv[1]+length);
      std::vector<std::string> anagrams;
      // First: collect all permutations
      using std::next_permutation;
      do {
         anagrams.push_back(std::string(argv[1]));
      } while (next_permutation(argv[1], argv[1]+length));
      std::sort(anagrams.begin(), anagrams.end());
      std::vector<std::string>::iterator last_anagram =
         std::unique(anagrams.begin(), anagrams.end());
      std::ostream_iterator<std::string, char>
         output(std::cout, " ");
      std::copy(anagrams.begin(), last_anagram, output);
   } catch (std::bad_alloc const&) {
      error(argv[0], ": out of memory.\n");
   }
   return 0;
}

