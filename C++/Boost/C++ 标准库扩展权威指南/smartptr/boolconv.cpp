#include <memory>
#include <iostream>
#include <string>
using std::tr1::shared_ptr;
using std::cout;
using std::string;

typedef shared_ptr<string> stp;

void show(stp s)
  { // show contents of target string
  if (s)
    cout << "string holds '" << *s << "'\n";
  else
    cout << "string is empty\n";
  }

int main()
  { // demonstrate conversion operator
  stp s;
  show(s);
  s.reset(new string("Hello, world"));
  show(s);
  return 0;
  }