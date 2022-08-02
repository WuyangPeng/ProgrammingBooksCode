#include <regex>
#include <iostream>
using std::tr1::regex;
using std::cout;

void show_flags(const regex& rgx)
  { // extract and show flag values
  regex::flag_type flags = rgx.flags();
  if ((flags & regex::ECMAScript) == regex::ECMAScript)
    cout << "ECMAScript";
  else if ((flags & regex::basic) == regex::basic)
    cout << "basic";
  else if ((flags & regex::extended) == regex::extended)
    cout << "extended";
  else if ((flags & regex::grep) == regex::grep)
    cout << "grep";
  else if ((flags & regex::egrep) == regex::egrep)
    cout << "egrep";
  else if ((flags & regex::awk) == regex::awk)
    cout << "awk";
  else
    cout << "unknown grammar";
  if ((flags & regex::icase) == regex::icase)
    cout << " | icase";
  if ((flags & regex::collate) == regex::collate)
    cout << " | collate";
  if ((flags & regex::nosubs) == regex::nosubs)
    cout << " | nosubs";
  if ((flags & regex::optimize) == regex::optimize)
    cout << " | optimize";
  cout << '\n';
  }

int main()
  { // demonstrate member function basic_regex::flags
  regex rgx;
  show_flags(rgx);
  rgx.assign("", regex::grep | regex::nosubs);
  show_flags(rgx);
  rgx = "a";
  show_flags(rgx);
  return 0;
  }