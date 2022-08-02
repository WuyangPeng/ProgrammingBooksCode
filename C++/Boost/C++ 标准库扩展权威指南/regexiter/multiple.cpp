#include <regex>
#include <iostream>
#include <string>
#include <vector>
using std::string; using std::cout; using std::vector;

typedef string::const_iterator seq_t;
typedef std::tr1::regex_token_iterator<seq_t> rgxiter;
typedef rgxiter::regex_type rgx_t;
typedef rgxiter::value_type match;

static void show(const vector<int>& fields)
  { // demonstrate multiple-field constructor
  string id =
    "([[:alpha:]]+)([[:space:]]+)([[:digit:]]{2,5})";
  rgx_t model_descr(id);
  string item("Emperor 280, Emperor 400, Whisper 60");
  rgxiter first(item.begin(), item.end(),
    model_descr, fields);
  rgxiter last;
  while (first != last)
    cout << *first++ << '\n';
  }

int main()
  { // demonstrate regex_token_iterator multiple-field constructor
  vector<int> fields;
  fields.push_back(0);
  cout << "Full match:\n";
  show(fields);
  fields.push_back(3);
  cout << "Full match, model number:\n";
  show(fields);
  fields.push_back(1);
  cout << "Full match, model number, model name:\n";
  show(fields);
  return 0;
  }