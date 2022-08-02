#include <regex>
#include <iostream>
using std::tr1::regex; using std::tr1::cmatch;
using std::tr1::regex_search;
using namespace std::tr1::regex_constants;
using std::cout;

static void search(const char *tgt, const char *expr)
  { // show all subsequences of tgt that match expr
  regex rgx(expr);
  cmatch match;
  match_flag_type flags = match_default;
  const char *first = tgt;
  const char *last = tgt + strlen(tgt);
  for (;;)
    { // keep trying
    if (regex_search(first, last, match, rgx, flags))
      { // show match, move past it
      cout << match.str()
        << " at offset "
        << (match[0].first - tgt) << '\n';
      first += match.position() + match.length();
      flags = flags | match_not_bol | match_prev_avail;
      }
    else
      break;
    }
  }

int main()
  { // demonstrate use of match_not_bol
  const char *expr = "\\babc";
  const char *tgt = "abcabc";
  search(tgt, expr);
  return 0;
  }