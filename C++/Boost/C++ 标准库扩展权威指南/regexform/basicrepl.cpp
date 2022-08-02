#include <regex>
#include <iostream>
#include <string>
using std::tr1::regex; using std::tr1::regex_replace;
using std::cout;
using std::string;

static const string text =
"For some reason, instead of using the name Microsoft,\n"
"I used the name Intel when I wrote this. Now I need\n"
"to change it, since I wasn't talking about Intel,\n"
"but about Microsoft. Intelligent people like to think\n"
"they don't make such silly mistakes, but sometimes,\n"
"alas, they do.\n";

int main()
  { // demonstrate basic search and replace
  regex rgx("Intel");
  string replacement("Microsoft");
  string result;
  regex_replace(back_inserter(result),
    text.begin(), text.end(), rgx, replacement);
  cout << result;
  return 0;
  }