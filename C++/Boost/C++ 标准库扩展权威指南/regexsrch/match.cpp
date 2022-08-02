#include <regex>
#include <iomanip>
#include <iostream>
using std::tr1::regex; using std::tr1::regex_match;
using std::cout; using std::setw;

void show_match(const regex& rgx, const char *str)
  { // check for match
  cout << setw(10) << str << ": ";
  if (regex_match(str, rgx))
    cout << "matches\n";
  else
    cout << "doesn't match\n";
  }

int main()
  { // demonstrate exact match
  regex rgx("b(c*)d");
  show_match(rgx, "bd");            // matches
  show_match(rgx, "d");             // doesn't match
  show_match(rgx, "bcd");           // matches
  show_match(rgx, "bc");            // doesn't match
  show_match(rgx, "abd");           // doesn't match
  show_match(rgx, "bde");           // doesn't match
  return 0;
  }