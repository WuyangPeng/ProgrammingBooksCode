#include <regex>
#include <iostream>
#include <string>
using std::tr1::regex;
using std::tr1::cmatch; using std::tr1::regex_search;
using std::cout; using std::string;

int main()
  {
  string str("\\.a");
  regex rgx(str);
  cmatch match;
  if (std::tr1::regex_search("aba.a", match, rgx))
    std::cout << "match found after "
      << match.prefix() << '\n';
  return 0;
  }