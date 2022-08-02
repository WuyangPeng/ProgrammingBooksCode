#include <regex>
#include <iostream>
using std::tr1::regex; using std::tr1::regex_match;
using namespace std::tr1::regex_constants;
using std::cout;

int main()
  { // demonstrate use of match_prev_avail
  regex rgx("\\bbcd");
  const char *txt = "abcd";
  const char *tgt = txt + 1;
  if (regex_match(tgt, rgx))
    cout << "Matches.\n";
  else
    cout << "Doesn't match.\n";
  if (regex_match(tgt, rgx, match_prev_avail))
    cout << "Matches.\n";
  else
    cout << "Doesn't match.\n";
  return 0;
  }
