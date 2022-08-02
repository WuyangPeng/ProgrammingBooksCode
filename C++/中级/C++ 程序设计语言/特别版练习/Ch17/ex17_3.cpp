/* Code for exercise 17.3.
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
#include <fstream>
#include <set>
#include <string>

// using std::string;

bool load_nospace_word(istream &input, string &word) {
   return input >> word;
}

bool load_letter_word(istream &input, string &word) {
   bool result;
   char c;
   while (input.get(c))
      if (isalpha(c)) {
         word = c;
         break;
      }
   while (result = input.get(c)) {
      if (!isalpha(c)) {
         input.putback(c);
         break;
      }
      word += c;
   }
   return result;
}

typedef bool (*Loader)(istream&, string&);

main(int argc, char *argv[]) {
   istream *input;
   Loader loader;
   int name_pos;
   if (argc>1 && strcmp(argv[1], "-letters")==0) {
      name_pos = 2;
      loader = &load_letter_word;
   } else {
      name_pos = 1;
      loader = &load_nospace_word;
   }
   if (argc==name_pos)
      input = &cin;
   else
   if (argc==name_pos+1)
      input = new ifstream(argv[name_pos]);
   else {
      cerr << "Unexpected arguments.\n";
      exit(-1);
   }
   string word;
   std::set<string, std::less<string> > listing;
   while (loader(*input, word))
      listing.insert(word);
   std::copy(listing.begin(), listing.end(),
             std::ostream_iterator<string>(cout, "\n"));
   if (argc==name_pos+1)
      delete input;
   return 0;
}

