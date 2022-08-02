#include <regex>
#include <iostream>
using std::tr1::regex; using std::tr1::regex_match;
using namespace std::tr1::regex_constants;
using std::cout;

int main()
  { // demonstrate use of match_not_null
  regex rgx("a*|b");
  const char *tgt = "ccc";
  if (regex_search(tgt, rgx))
    cout << "Matches.\n";
  else
    cout << "Doesn't match.\n";
  if (regex_search(tgt, rgx, match_not_null))
    cout << "Matches.\n";
  else
    cout << "Doesn't match.\n";
  return 0;
  }