#include <regex>
#include <iostream>
#include <stdlib.h>
using std::tr1::regex; using std::tr1::match_results;
using std::tr1::regex_search;
using std::cout;

typedef match_results<const char *> mtch;

static void show(const char *title, const mtch& match)
  { // summarize match_results object
  cout << title << ":\n";
  cout << " size: " << match.size() << '\n';
  cout << " contents: `" << match.str() << "`\n";
  }

int main()
  { // demonstrate various constructors and modifiers
  mtch match;
  show("after default constructor", match);
  regex rgx("b(c*)d");
  const char *tgt = "abcccde";
  mtch match1;
  if (!regex_search(tgt, match1, rgx))
    return EXIT_FAILURE;
  show("after successful search", match1);
  mtch match2(match1);
  show("after copy construction", match2);
  match.swap(match1);
  show("after swap", match);
  swap(match, match1);
  show("after another swap", match);
  match = match2;
  show("after assignment", match);
  return 0;
  }