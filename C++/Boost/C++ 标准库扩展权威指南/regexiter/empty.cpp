#include <regex>
#include <iostream>
using std::tr1::regex; using std::tr1::cmatch;
using std::tr1::regex_search;
using namespace std::tr1::regex_constants;
using std::cout;

int main()
  { // show empty match
  const char *expr = "a*";
  regex rgx(expr);
  cmatch match;
  const char *tgt = "bcd";
  if (regex_search(tgt, match, rgx))
    { // show the match
    cout << "Matched at offset " << match.position()
      << ", with length " << match.length() << '\n';
    }
  return 0;
  }