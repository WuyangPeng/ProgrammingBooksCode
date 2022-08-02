#include <regex>
#include <iostream>
using std::tr1::regex; using std::tr1::regex_search;
using namespace std::tr1::regex_constants;
using std::cout;

int main()
  { // demonstrate use of match_continuous
  regex rgx("bcd");
  const char *tgt = "abcd";
  if (regex_search(tgt, rgx))
    cout << "Matches.\n";
  else
    cout << "Doesn't match.\n";
  if (regex_search(tgt, rgx, match_continuous))
    cout << "Matches.\n";
  else
    cout << "Doesn't match.\n";
  return 0;
  }