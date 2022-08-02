#include <regex>
#include <iostream>
#include <string>
#include <sstream>
using std::tr1::regex; using std::tr1::regex_replace;
using std::cout; using std::string;
using std::istringstream;

static const string addrlist =
"joebob@notarealaddress.org, Joe, Bob, Bubba, iguana\n"
"missy@notarealaddress.org, Missy, Treadwell,"
  "Reginald Addington Farnsworth II,"
  "prize-winning Toy Poodle\n"
"killer@notarealaddress.org, Spike, Redwood,"
  "Fangs, snake\n"
"kitten@notarealaddress.org, Sally, Smith,"
  "Mr. Bubbles, goldfish\n";

static string formletter =
"To: $1\n"
"Dear $2,\n"
"I'm sure your $5, $4,\n"
"as well as all the other pets in the $3 family,\n"
"will enjoy our latest offering,"
" Universal-Ultra-Mega Vitamins,\n"
"Now available for all kinds of animals,"
" including $5s.\n"
"Don't delay, get some today!\n";

int main()
  {
  regex rgx(
    "(.*)[[:space:]]*,[[:space:]]*"
    "(.*)[[:space:]]*,[[:space:]]*"
    "(.*)[[:space:]]*,[[:space:]]*"
    "(.*)[[:space:]]*,[[:space:]]*"
    "(.*)");
  string letter =
    regex_replace(addrlist, rgx, formletter);
  cout << letter;
  return 0;
  }