#include <regex>
using std::tr1::regex;

int main()
  { // demonstrate use of swap
  regex rgx0;       // empty regular expression object
  regex rgx1("abc");// holds \tcode{"}{}abc\tcode{"}
  rgx0.swap(rgx1);  // rgx0 holds \tcode{"}{}abc\tcode{"} and rgx1 is empty
  swap(rgx0, rgx1); // rgx0 is empty and rgx1 holds \tcode{"}{}abc\tcode{"}
  return 0;
  }