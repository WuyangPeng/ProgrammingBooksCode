/* Code for exercise 5.11.
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
#include <iostream.h>
#include <list>
#include <set>
#include <string>

int main() {
   using std::copy;
   using std::cout;
   using std::ostream_iterator;
   using std::pair;
   using std::string;
   typedef std::set<string> WordSet;
   typedef WordSet::iterator WordIter;
   typedef std::list<WordIter> Index;
   WordSet words;
   Index input_order;
   // Input the words uniquely
   for(string new_word;
       cin >> new_word, new_word!="Quit";) {
      pair<WordIter, bool> const &trace = words.insert(new_word);
      if (trace.second)
         input_order.push_back(trace.first);
   }
   // Output unique words in order of input:
   cout << "\n>>> Unique words in input order:\n";
   for (Index::iterator p = input_order.begin(); p!=input_order.end(); ++p) {
      cout << *(*p) << '\n';
   }
   // Output unique words in default set<string> order:
   cout << "\n>>> Unique words in sorted order:\n";
   copy(words.begin(), words.end(),
        ostream_iterator<string>(cout, "\n"));
   return 0;
}

