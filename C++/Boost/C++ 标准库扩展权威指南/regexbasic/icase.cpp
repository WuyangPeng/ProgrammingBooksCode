#include <regex>
#include <iostream>
using std::tr1::regex;
using std::tr1::regex_match;
using namespace std::tr1::regex_constants;
using std::cout;

static void match(const char *title,
const char *expr, const char *tgt,
  syntax_option_type flags)
  { // check for match
  regex rgx(expr, flags);
  cout << '`' << expr << "` (" << title << "): ";
  if (regex_match(tgt, rgx))
    cout << "matched";
  else
    cout << "didn't match";
  cout << " `" << tgt << "`\n";
  }

static void match4(const char *title, const char *expr,
  syntax_option_type flags)
  { // check four matches
  match(title, expr, "a", flags);
  match(title, expr, "\x61", flags);
  match(title, expr, "A", flags);
  match(title, expr, "\x41", flags);
  }

int main()
  { // demonstrate icase flag
  match4("case sensitive", "a", ECMAScript);
  match4("case insensitive", "a", ECMAScript | icase);
  match4("case sensitive", "[a-c]", ECMAScript);
  match4("case insensitive", "[a-c]",
    ECMAScript | icase);
  return 0;
  }