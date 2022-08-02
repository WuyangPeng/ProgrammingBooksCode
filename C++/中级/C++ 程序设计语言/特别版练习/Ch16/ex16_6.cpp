/* Code for exercise 16.6.
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

char const *dont_like[] = {
   "kumquat", "pomelo", "starfruit", "walnut", "watermelon",
   0 };

void process_data(std::vector<string> &fruits) {
   std::sort(fruits.begin(), fruits.end());
   std::vector<string>::iterator p = fruits.begin();
   for (int i = 0; (p!=fruits.end()) and dont_like[i];) {
      int order = p->compare(dont_like[i]);
      if (order>0) // *p "comes after" dont_like[i]
         ++i;
      else
      if (order<0)
         ++p;
      else // order==0, i.e. *p==dont_like[i]
         p = fruits.erase(p);
   }
   using std::copy;
   copy(fruits.begin(), fruits.end(),
        std::ostream_iterator<string>(std::cout, "\n"));
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

