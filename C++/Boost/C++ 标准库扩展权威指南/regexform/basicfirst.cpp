#include <regex>
#include <iostream>
#include <string>
using std::tr1::regex; using std::tr1::regex_replace;
using namespace std::tr1::regex_constants;
using std::cout;
using std::string;

static const string text =
"Each morning I check http://www.nytimes.com and\n"
"http://www.boston.com for news of what happened\n"
"overnight. I also look at http://www.tnr.com to\n"
"see any new articles they have posted.";

int main()
  { // demonstrate basic search
  regex rgx("http://([^/: ]+)");
  string replacement("http://www.wsj.com");
  string result;
  regex_replace(back_inserter(result),
    text.begin(), text.end(),
    rgx, replacement, format_first_only);
  cout << result;
  return 0;
  }