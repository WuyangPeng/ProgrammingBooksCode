#include <regex>
#include <iostream>
#include <string>
using std::tr1::regex; using std::tr1::regex_iterator;
using std::string; using std::cout;

typedef regex_iterator<string::const_iterator> iter_t;

static void show_equal(const char *title,
  const iter_t& iter0, const iter_t& iter1)
  { // show equality of iterator objects
  cout << title << "\n    "
    << (iter0 == iter1 ? "equal" : "not equal") << '\n';
  }

int main()
  { // demonstrate regex_iterator comparison operators
  regex rgx0("abc"), rgx1("abc");
  string tgt0("abc"), tgt1("abc");
  iter_t iter0(tgt0.begin(), tgt0.end(), rgx0);
  iter_t iter1(tgt0.begin(), tgt0.end(), rgx1);
  show_equal(
    "same range, different regular expression objects",
    iter0, iter1);
  iter_t iter2(tgt0.begin() + 1, tgt0.end(), rgx0);
  show_equal(
    "different range, same regular expression objects",
    iter0, iter2);
  iter_t iter3, iter4;
  show_equal("default constructed",
    iter3, iter4);
  show_equal(
    "non-default constructed and default constructed",
    iter0, iter4);
  ++iter0;  // move past final match
  show_equal(
    "incremented to end and default constructed",
    iter0, iter4);
  return 0;
  }