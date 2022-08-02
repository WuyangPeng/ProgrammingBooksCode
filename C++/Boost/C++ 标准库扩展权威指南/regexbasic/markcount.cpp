#include <regex>
#include <iostream>
using std::tr1::regex;
using std::cout;

void show_count(const char *title, const regex& rgx)
  {
  cout << '\"' << title << "\" has " << rgx.mark_count()
    << " capture group"
    << (rgx.mark_count() == 1 ? "" : "s")
    << ".\n";
  }

void show(const char *expr)
  {
  regex rgx(expr);
  show_count(expr, rgx);
  }

int main()
  { // demonstrate use of mark_count
  show("");
  show("abc");
  show("(abc)");
  show("(a)b(c)");
  show("(a(b)c)");
  return 0;
  }