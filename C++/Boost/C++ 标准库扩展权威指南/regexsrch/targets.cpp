#include <regex>
#include <iostream>
#include <list>
#include <string>
using std::tr1::regex; using std::tr1::regex_match;
using std::cout;
using std::list;
using std::basic_string;

int main()
  { // designating the target sequence
  regex rgx("b(c*)d");

  // pointer
  const char *tgt1 = "bcd";
  if (regex_match(tgt1, rgx))
    cout << "Matches.\n";
  else
    cout << "Doesn't match.\n";

  // string
  basic_string<char> tgt2("bcd");
  if (regex_match(tgt2, rgx))
    cout << "Matches.\n";
  else
    cout << "Doesn't match.\n";

  // pair of bidirectional iterators
  list<char> tgt0;
  tgt0.push_back('b');
  tgt0.push_back('c');
  tgt0.push_back('d');
  if (regex_match(tgt0.begin(), tgt0.end(), rgx))
    cout << "Matches.\n";
  else
    cout << "Doesn't match.\n";

  return 0;
  }