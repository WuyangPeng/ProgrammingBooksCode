#include <regex>
#include <string>
using std::tr1::regex;
using std::string;

int main()
  { // demonstrate basic_regex constructors
  regex rgx0;           // default constructor; matches nothing
  char expr1[] = "abc[d-f]";
  regex rgx1(expr1);    // holds \tcode{"}{}abc[d-f]\tcode{"}, ECMAScript grammar
  regex rgx2(expr1, 3); // holds \tcode{"}{}abc\tcode{"}, ECMAScript grammar
  regex rgx3(rgx2);     // holds \tcode{"}{}abc\tcode{"}, ECMAScript grammar
  string str("[def]");
  regex rgx4(str, regex::basic);
                        // holds \tcode{"}{}[def]\tcode{"}, BRE grammar
  regex rgx5(str.begin(), str.end(),
    regex::basic | regex::icase);
                        // holds \tcode{"}{}[def]\tcode{"}, BRE grammar,
                        // case insensitive
  return 0;
  }