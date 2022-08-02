#include <regex>
#include <iostream>
#include <string>
using std::tr1::regex; using std::tr1::regex_search;
using std::tr1::smatch;
using std::string; using std::cout;

int main()
  { // search for regular expression in text
  string str = "abcdef";
  string::const_iterator first = str.begin();
  string::const_iterator second = str.end();
  smatch match;
  string expr = "^(abc|def)";
  regex rgx(code);
  while (regex_search(first, second, match, rgx))
    { // check range for match
    cout << match[0] << '\n';
    first += match.position() + match.length();
    }
  return 0;
  }