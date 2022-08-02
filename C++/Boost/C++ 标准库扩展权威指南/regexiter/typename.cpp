#include <regex>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>

typedef std::string::const_iterator seq_t;
typedef std::tr1::regex_iterator<seq_t> rgxiter;
typedef rgxiter::regex_type rgx_t;
typedef std::tr1::match_results<seq_t> match_t;

namespace std { // add inserter to namespace std
template <class Elem, class Alloc>
std::basic_ostream<Elem, Alloc>& operator<<(
  std::basic_ostream<Elem, Alloc>& out,
  const match_t& val)
  { // insert cmatch object into stream
  static std::string empty("[empty]");
  return out << (val.length() ? val.str() : empty);
  }
}

int main()
  { // split out words from text file
  rgx_t rgx("[[:alnum:]_#]+");
  ifstream input("typename.cpp");
  std::string str;
  while (std::getline(input, str))
    { // split out words from a line of text
    rgxiter first(str.begin(), str.end(), rgx), last;
    std::ostream_iterator<rgxiter::value_type>
      tgt(std::cout, "\n"));
    std::copy(first, last, tgt);
    }
  return 0;
  }