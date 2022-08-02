#include <regex>
#include <iomanip>
#include <iostream>
#include <string>
using std::tr1::regex; using std::tr1::regex_match;
using std::tr1::match_results; using std::tr1::sub_match;
using std::string;
using std::cout; using std::setw;

template <class BidIt>
void show(const char *title, const sub_match<BidIt>& sm)
  {
  cout << setw(20) << title << ": ";
  if (sm.matched)
    cout << sm.str() << '\n';
  else
    cout << "[no match]\n";
  }

int main()
  {
  regex rgx("(a+)|(b+)");
  string tgt("bbb");
  match_results<string::iterator> m;
  show("no search", m[0]);
  if (!regex_match(tgt.begin(), tgt.end(), m, rgx))
    cout << "search failed\n";
  else
    { // search succeeded, capture group 1 not part of match
    show("full match", m[0]);
    show("capture group 1", m[1]);
    show("capture group 2", m[2]);
    }
  return 0;
  }
