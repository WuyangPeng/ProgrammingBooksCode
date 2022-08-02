#include <regex>
#include <iostream>
#include <algorithm>
#include <iterator>
using std::tr1::regex; using std::tr1::regex_search;
using std::tr1::match_results; using std::tr1::sub_match;
using std::cout; using std::ostream_iterator;
using std::copy;

typedef const char *iter;
typedef sub_match<iter> sub;
typedef match_results<iter> mtch;

namespace std { // add inserter to namespace std
template <class Elem, class Alloc>
basic_ostream<Elem, Alloc>& operator<<(
  basic_ostream<Elem, Alloc>& out, const sub& val)
  {  // insert sub_match<iter> into stream
  return out << '`' << val.str() << '`';
  }
}

int main()
  {
  regex rgx("b(c*|(x))d");
  const char *tgt = "abcccde";
  mtch match;
  if (!regex_search(tgt, match, rgx))
    return EXIT_FAILURE;
  copy(match.begin(), match.end(),
    ostream_iterator<sub>(cout, "\n"));
  return 0;
  }