/* Code for exercise 20.5.
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
#include <iostream>
#include <iterator>
#include <string>

template<typename C, typename T, typename A>
struct string_appender
   : std::iterator<std::output_iterator_tag, void, void, void, void> {
   typedef std::basic_string<C, T, A> string;
   typedef typename string::value_type value_type;
   explicit string_appender(string &s): s_(s) {}
   string_appender& operator=(value_type const &ch) {
      s_.append(1, ch);
      return *this;
   }
   string_appender& operator*() { return *this; }
   string_appender const& operator*() const { return *this; }
   string_appender& operator++() { return *this; }
   string_appender operator++(int) { return *this; }
private:
   std::string &s_;
};


template<typename C, typename T, typename A> inline
string_appender<C, T, A>
back_inserter(std::basic_string<C, T, A> &s) {
   return string_appender<C, T, A>(s);
}


char const apx[] = "-appendix";

int main() {
   std::string book("preface");
   std::copy(&apx[0], &apx[0]+sizeof(apx), back_inserter(book));
   std::cout << book << '\n';
   return 0;
}

