#include <regex>
#include <iostream>
using std::tr1::regex; using std::tr1::regex_match;
using namespace std::tr1::regex_constants;
using std::cout;

int main()
  { // demonstrate use of match_not_bol
  regex rgx("^abcd");
  const char *tgt = "abcd";
  if (regex_match(tgt, rgx))
    cout << "Matches.\n";
  else
    cout << "Doesn't match.\n";
  if (regex_match(tgt, rgx, match_not_bol))
    cout << "Matches.\n";
  else
    cout << "Doesn't match.\n";
  return 0;
  }