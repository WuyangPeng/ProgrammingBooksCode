#include <regex>
#include <string>
#include <iostream>
using std::string; using std::cout;

typedef string::const_iterator seq_t;
typedef std::tr1::regex_iterator<seq_t> rgxiter;
typedef rgxiter::regex_type rgx_t;

int main()
  { // constructing regex_iterator objects
  rgx_t rgx("not found");
  string target("this is text");
  rgxiter first(target.begin(), target.end(), rgx);
  rgxiter last;
  if (first == last)
    cout << "regular expression not found\n";
  return 0;
  }