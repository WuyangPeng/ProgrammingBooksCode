#include <regex>
#include <iostream>
#include <string>
using std::tr1::regex; using std::tr1::cmatch;
using std::tr1::regex_search;
using namespace std::tr1::regex_constants;
using std::cout; using std::string;

static void search(const char *tgt, const char *expr)
  { // show all subsequences of tgt that match expr
  regex rgx(expr);
  cmatch match;
  match_flag_type flags = match_default;
  match_flag_type mod = match_default;
  const char *first = tgt;
  const char *last = tgt + strlen(tgt);
  string empty("[empty]");
  for (;;)
    { // keep trying
    if (regex_search(first, last, match,
      rgx, flags | mod))
      { // show match, move past it
      cout << (match.length() ? match.str() : empty)
        << " at offset "
        << (match[0].first - tgt) << '\n';
      if (match.length() != 0)
        { // move past match, clear modifier flags
        first += match.position() + match.length();
        mod = match_default;
        }
      else
        mod = match_not_null | match_continuous;
      flags = flags | match_not_bol | match_prev_avail;
      }
    else if (mod != match_default && first != last)
      { // move past failed match, clear modifier flags
      ++first;
      mod = match_default;
      }
    else
      break;
    }
  }

int main()
  { // demonstrate use of match_not_bol
  const char *expr = "a*|c";
  const char *tgt = "bcd";
  search(tgt, expr);
  return 0;
  }