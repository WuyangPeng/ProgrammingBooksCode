#include <regex>
#include <iomanip>
#include <iostream>
using std::tr1::regex; using std::tr1::regex_search;
using std::cout; using std::setw;

void show_match(const regex& rgx, const char *str)
  { // check for match
  cout << setw(10) << str << ": ";
  if (regex_search(str, rgx))
    cout << "matches\n";
  else
  cout << "doesn't match\n";
  }

int main()
  { // demonstrate use of regex_search
  regex rgx("b(c*)d");
  show_match(rgx, "bd");            // matches
  show_match(rgx, "d");             // doesn't match
  show_match(rgx, "bcd");           // matches
  show_match(rgx, "bc");            // doesn't match
  show_match(rgx, "abd");           // matches
  show_match(rgx, "bde");           // matches
  return 0;
  }