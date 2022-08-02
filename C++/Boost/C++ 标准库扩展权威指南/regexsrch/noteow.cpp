#include <regex>
#include <iostream>
using std::tr1::regex; using std::tr1::regex_match;
using namespace std::tr1::regex_constants;
using std::cout;

int main()
  { // demonstrate use of match_not_eow
  regex rgx("abcd\\b");
  const char *txt = "abcde";
  const char *end = txt + 4;    // points to \tfq{}e\tfq
  if (regex_match(txt, end, rgx))
    cout << "Matches.\n";
  else
    cout << "Doesn't match.\n";
  if (regex_match(txt, end, rgx, match_not_eow))
    cout << "Matches.\n";
  else
    cout << "Doesn't match.\n";
  return 0;
  }
