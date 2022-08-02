#include <regex>
#include <iostream>
#include <string>
using std::tr1::regex;
using std::tr1::regex_token_iterator;
using std::string; using std::cout;

typedef string::const_iterator siter;
typedef regex_token_iterator<siter> iter_t;

static void show_equal(const char *title,
  const iter_t& iter0, const iter_t& iter1)
  { // show equality of iterator objects
  cout << title << "\n    "
    << (iter0 == iter1 ? "equal" : "not equal") << '\n';
  }

int main()
  { // demonstrate regex_token_iterator comparison operators
  string csv("[[:space:]]*,[[:space:]]*");
  regex rgx(csv);
  string data("Ron Mars, 2114 East St.   ,  Biloxi, MI");
  int selector0[] = { 0, 1 };
  int selector1[] = { 0, 1 };
  int selector2[] = { 1, 0 };
  iter_t iter0(data.begin(), data.end(), rgx, selector0);
  iter_t iter1(data.begin(), data.end(), rgx, selector0);
  show_equal("equal arguments", iter0, iter1);
  iter_t iter2(data.begin(), data.end(), rgx, selector1);
  show_equal("equal selectors", iter0, iter2);
  iter_t iter3(data.begin(), data.end(), rgx, selector2);
  show_equal("unequal selectors", iter0, iter3);

  iter_t iter4(++iter0);
  show_equal("copy", iter0, iter4);
  ++iter0;
  show_equal("unequal increments", iter0, iter4);
  ++iter4;
  show_equal("equal increments", iter0, iter4);
  return 0;
  }