#include <regex>
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
using std::tr1::regex; using std::tr1::cregex_iterator;
using std::tr1::cmatch;
using std::cout; using std::string;
using std::ostream_iterator; using std::copy;

namespace std { // add inserter to namespace std
template <class Elem, class Alloc>
basic_ostream<Elem, Alloc>& operator<<(
  basic_ostream<Elem, Alloc>& out, const cmatch& val)
  {  // insert cmatch object into stream
  static string empty("[empty]");
  return out << (val.length() ? val.str() : empty);
  }
}

int main()
  { // demonstrate use of cregex_iterator
  const char *expr = "a*|c";
  const char *tgt = "bcd";
  regex rgx(expr);
  const char *end = tgt + strlen(tgt);
  cregex_iterator first(tgt, end, rgx), last;
  ostream_iterator<cmatch> out(cout, "\n");
  copy(first, last, out);
  return 0;
  }