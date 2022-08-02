/* Code for exercise 10.19.
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

/* Notes:

   Older versions of the standard library do not have a header
   <sstream>. Usually they have a header <strstream.h> instead,
   but some work is required to make this program work with
   that header. In particular, the line:
      std::istringstream words(line);
   would have to be replaced by:
      ::istrstream words(line.cstr());
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using std::istream;
using std::string;
using std::vector;

typedef std::map<string, vector<int> > LineIndex;
typedef vector<string>::const_iterator EntryIt;

LineIndex* make_line_index(istream &input,
                           vector<string> const &entries) {
   // First create the index and enter the entries in it:
   LineIndex *index = new LineIndex;
   for (EntryIt p = entries.begin(); p!=entries.end(); ++p)
      (*index)[*p]; // Causes insertion

   // Now, read one line at a time:
   string line, word;
   int line_number = 0;
   while (std::getline(input, line)) {
      ++line_number;
      std::istringstream words(line);

      // Read each word in this line and update the index if needed:
      while (words >> word) {
         LineIndex::iterator p = index->find(word);
         if (p!=index->end()) // Found?
            (*p).second.push_back(line_number);
      }
   }
   return index;
}

int main(int argc, char *argv[]) {
   // Words to look up: argv[1..argc-1]
   // Enter them in a vector:
   vector<string> entries;
   for (int k = 1; k!=argc; ++k)
      entries.push_back(string(argv[k]));
   // Compute the index using the above function:
   LineIndex *index = make_line_index(cin, entries);
   // Output the results:
   vector<string>::iterator p = entries.begin();
   for (; p!=entries.end(); ++p) {
      cout << "Word " << *p << " appears in lines ";
      LineIndex::iterator lines = index->find(*p);
      std::copy((*lines).second.begin(), (*lines).second.end(),
                ostream_iterator<int>(cout, ", "));
      cout << ".\n";
   }
}

