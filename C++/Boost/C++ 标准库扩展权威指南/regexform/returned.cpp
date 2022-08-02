#include <regex>
#include <iostream>
#include <string>
#include <algorithm>
using std::tr1::regex; using std::tr1::smatch;
using std::tr1::regex_search;
using std::string; using std::cout;
using std::copy;

int main()
  { // demonstrate match_results::format
  string result("The URL '");
  string tail("' was found.");
  regex rgx("http://([^/: ]+)");
  string text("The site http://www.petebecker.com has"
    " useful information.");
  smatch match;
  if (regex_search(text, match, rgx))
    { // show result of successful match
    copy(tail.begin(), tail.end(),
      match.format(back_inserter(result), "$&"));
    cout << result << '\n';
    }
  return 0;
  }