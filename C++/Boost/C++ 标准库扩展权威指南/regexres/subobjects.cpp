#include <regex>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <string>
using std::tr1::regex; using std::tr1::regex_match;
using std::tr1::match_results; using std::tr1::sub_match;
using std::copy;
using std::ostream_iterator; using std::string;
using std::cout; using std::setw;

template <class BidIt>
void show(const char *title, const sub_match<BidIt>& sm)
  {
  typedef sub_match<BidIt>::value_type MyTy;
  cout << setw(20) << title << ": ";
  if (sm.matched)
    copy(sm.first, sm.second,
      ostream_iterator<MyTy>(cout));
  else
    cout << "[no match]";
  cout << '\n';
  }

int main()
  {
  regex rgx("(a+)|(b+)");
  string tgt("bbb");
  match_results<string::iterator> match;
  show("no search", match[0]);
  if (!regex_match(tgt.begin(), tgt.end(), match, rgx))
    cout << "search failed\n";
  else
    { // search succeeded, capture group 1 not part of match
    show("full match", match[0]);
    show("capture group 1", m[1]);
    show("capture group 2", m[2]);
    }
  return 0;
  }
