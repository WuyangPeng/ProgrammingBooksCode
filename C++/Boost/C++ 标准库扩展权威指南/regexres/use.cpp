#include <regex>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
using std::tr1::regex; using std::tr1::regex_match;
using std::tr1::match_results;
using std::cout; using std::string;

int main()
  { // demonstrate use of match_results
  regex rgx("b(c*)d");
  const char *tgt = "abcccde";
  match_results<const char *> match;
  if (!regex_search(tgt, match, rgx))
    cout << "search failed\n";
  else
    { // match succeeded
    cout << "matched text:  " << match.str(0) << '\n';
    cout << "matched group:  " << match.str(1) << '\n';
    }
  return 0;
  }