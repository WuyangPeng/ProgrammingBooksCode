#include <regex>
#include <iostream>
#include <string>
using std::string; using std::cout;

typedef string::const_iterator seq_t;
typedef std::tr1::regex_token_iterator<seq_t> rgxiter;
typedef rgxiter::regex_type rgx_t;
typedef rgxiter::value_type match;

int main()
  { // demonstrate use of selector value -1
  string csv("[[:space:]]*,[[:space:]]*");
  rgx_t rgx(csv);
  string data("Ron Mars, 2114 East St.   ,  Biloxi, MI");
  rgxiter first(data.begin(), data.end(), rgx, -1);
  rgxiter last;
  while (first != last)
    cout << *first++ << '\n';
  return 0;
  }
