/* Code for exercise 16.3.
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
#include <cctype>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using std::string;

// Utility function-object to convert alphabetic characters
// to lower-case:
struct LowerCase {
   char operator()(char const &c) const
      { return std::tolower(c); }
};

void process_data(std::vector<std::string> &fruits) {
   for (std::vector<string>::iterator p = fruits.begin();
        p!=fruits.end(); ++p)
      if ((*p)[0]=='a')
         std::cout << *p << '\n';
}

int main() {
   string fruit;
   std::vector<string> fruits;
   std::cout << "Enter fruit names. Terminate with \".\" (period).\n";
   while((std::cin >> fruit) && (fruit[0]!='.')) {
      std::transform(fruit.begin(), fruit.end(),
                     fruit.begin(), LowerCase());
      fruits.push_back(fruit);
   }
   process_data(fruits);
   return 0;
}

