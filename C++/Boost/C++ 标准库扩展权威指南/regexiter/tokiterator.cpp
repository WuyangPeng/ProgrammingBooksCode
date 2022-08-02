#include <regex>
#include <iostream>
#include <string>
using std::string; using std::cout;

typedef string::const_iterator seq_t;
typedef std::tr1::regex_token_iterator<seq_t> rgxiter;
typedef rgxiter::regex_type rgx_t;
typedef rgxiter::value_type match;

int main()
  { // demonstrate regex_token_iterator
  string id =
    "([[:alpha:]]+)([[:space:]]+)([[:digit:]]{2,5})";
  rgx_t model_descr(id);
  string item("Emperor 280, Emperor 400, Whisper 60");
  int fields[] = { 0, 1, 3 };
  rgxiter first(item.begin(), item.end(),
    model_descr, fields);
  rgxiter last;
  cout << item << '\n';
  while (first != last)
    cout << *first++ << '\n';
  return 0;
  }
