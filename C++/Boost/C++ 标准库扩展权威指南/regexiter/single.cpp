#include <regex>
#include <iostream>
#include <string>
using std::string; using std::cout;

typedef string::const_iterator seq_t;
typedef std::tr1::regex_token_iterator<seq_t> rgxiter;
typedef rgxiter::regex_type rgx_t;
typedef rgxiter::value_type match;

static void show(int field)
  { // demonstrate single-field constructor
  string id =
    "([[:alpha:]]+)([[:space:]]+)([[:digit:]]{2,5})";
  rgx_t model_descr(id);
  string item("Emperor 280, Emperor 400, Whisper 60");
  rgxiter first(item.begin(), item.end(),
    model_descr, field);
  rgxiter last;
  while (first != last)
    cout << *first++ << '\n';
  }

int main()
  { // demonstrate regex_token_iterator single-field constructor
  cout << "Full match:\n";
  show(0);
  cout << "\nModel name:\n";
  show(1);
  cout << "\nModel number:\n";
  show(3);
  cout << "\nSeparators:\n";
  show(-1);
  return 0;
  }