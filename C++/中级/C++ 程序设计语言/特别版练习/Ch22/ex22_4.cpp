/* Code for exercise 22.4.
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
#include <map>
#include <numeric>
#include <string>

typedef std::map<std::string, int> Tbl;

void readitems(Tbl &m) {
   std::string word;
   int val = 0;
   while (std::cin >> word >> val)
      m[word] += val;
}

template<class T> struct Add2 {
   int operator()(int a, T const &b) const {
      return a+b.second;
   }
};

int main() {
   Tbl tbl;
   readitems(tbl);
   typedef Tbl::const_iterator const_iter;
   for (const_iter p = tbl.begin(); p!=tbl.end(); ++p)
      std::cout << p->first << '\t' << p->second << '\n';
   std::cout << "----------------\ntotal\t"
             << std::accumulate(tbl.begin(), tbl.end(), 0,
                                Add2<Tbl::value_type>())
             << '\n';
   return !std::cin;
}

