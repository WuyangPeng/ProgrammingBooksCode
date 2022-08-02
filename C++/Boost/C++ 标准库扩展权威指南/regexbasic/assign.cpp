#include <regex>
#include <string>
using std::tr1::regex;
using std::string;

int main()
  { // demonstrate basic_regex assignment operators
  regex rgx;            // empty regular expression object
  rgx = "abc";          // holds \tcode{"}{}abc\tcode{"}, ECMAScript encoding
  string str("[def]");
  rgx = str;            // holds \tcode{"}{}[def]\tcode{"}, ECMAScript encoding
  regex rgx1("abc[def]", regex::basic);
  rgx = rgx1;           // holds \tcode{"}{}abc[def]\tcode{"}, BRE encoding
  return 0;
  }