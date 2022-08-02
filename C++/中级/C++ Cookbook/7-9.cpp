#include <iostream>
#include <istream>
#include <string>
#include <list>
#include <algorithm>
#include <iterator>
#include <cctype>
#include "utils.h" // For printContainer( ): see 7.10

using namespace std;

// Convert a string to upper case
string strToUpper(const string& s) {
   string tmp;
   for (string::const_iterator p = s.begin( ); p != s.end( ); ++p)
      tmp += toupper(*p);
   return(tmp);
}

string strAppend(const string& s1, const string& s2) {
   return(s1 + s2);
}

int main( ) {

   cout << "Enter a series of strings: ";
   istream_iterator<string> start(cin);
   istream_iterator<string> end;
   list<string> lst(start, end), out;

   // Use transform with an unary function...
   transform(lst.begin( ), lst.end( ),
             back_inserter(out),
             strToUpper);

   printContainer(out);

   cin.clear( );

   cout << "Enter another series of strings: ";
   list<string> lst2(++start, end);
   out.clear( );

   // ...or a binary function and another input sequence.
   transform(lst.begin( ), lst.end( ), lst2.begin( ),
             back_inserter(out),
             strAppend);

   printContainer(out);
}
