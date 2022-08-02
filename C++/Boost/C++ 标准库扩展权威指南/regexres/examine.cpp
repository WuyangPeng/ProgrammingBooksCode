#include <regex>
#include <iostream>
#include <stdlib.h>
using std::tr1::regex; using std::tr1::regex_search;
using std::tr1::match_results; using std::tr1::sub_match;
using std::cout;

typedef match_results<const char *> mtch;

static void show(int idx, const mtch& match)
  { // show contents of match[idx]
  cout << " match[" << idx << "]: "
    << (match[idx].matched ? "   " : "not")
    << " matched, `" << match.str(idx)
    << "` at offset " << match.position(idx)
    << ", with length " << match.length(idx) << '\n';
  }

int main()
  { // demonstrate operator[]
  regex rgx("b(c*|(x))d");
  const char *tgt = "abcccde";
  mtch match;
  if (!regex_search(tgt, match, rgx))
    return EXIT_FAILURE;
  cout << "After search, size is "
    << match.size() << '\n';
  cout << " text preceding match is `"
    << match.prefix() << "`\n";
  for (int i = 0; i < match.size() + 2; ++i)
    show(i, match);
  cout << " text following match is `"
    << match.suffix() << "`\n";
  return 0;
  }