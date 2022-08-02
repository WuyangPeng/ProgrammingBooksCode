#include <regex>
#include <iostream>
#include <iomanip>
#include <string>
using std::string; using std::cout; using std::setw;

typedef string::const_iterator seq_t;
typedef std::tr1::regex_iterator<seq_t> rgxiter;
typedef rgxiter::regex_type rgx_t;
typedef rgxiter::value_type match_t;

static void show(const match_t& match)
  { // show contents of \tcode{match_t} object
  for (int idx = 0; idx < match.size(); ++idx)
    { // show match[idx]
    cout << idx << ": ";
    if (match[idx].matched)
      cout << setw(match.position(idx)) << ""
        << match.str(idx) << '\n';
    else
      cout << "[not matched]";
    }
  }

int main()
  { // demonstrate regex_iterator dereferencing
  string id =
    "([[:alpha:]]+)([[:space:]]+)([[:digit:]]{2,5})";
  rgx_t model_descr(id);
  string item("Emperor 280, Emperor 400, Whisper 60");
  rgxiter first(item.begin(), item.end(), model_descr);
  rgxiter last;
  cout << "   " << item << '\n';
  while (first != last)
    show(*first++);
  return 0;
  }
