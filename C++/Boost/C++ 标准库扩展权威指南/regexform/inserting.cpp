#include <regex>
#include <iostream>
#include <string>
#include <sstream>
using std::tr1::regex; using std::tr1::smatch;
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

static void write_letter(const smatch& match)
  {
  cout << "To: " << match.str(1) << '\n';
  cout << "Dear " << match.str(2) << ",\n";
  cout << "I'm sure your " << match.str(5)
    << ", " << match.str(4) << ",\n";
  cout << "as well as all the other pets in the "
    << match.str(3) << " family,\n";
  cout << "will enjoy our latest offering,"
    << " Universal-Ultra-Mega Vitamins,\n";
  cout << "Now available for all kinds of animals,"
    << " including " << match.str(5) << "s.\n";
  cout << "Don't delay, get some today!\n";
  }

int main()
  {
  regex rgx(
    "(.*)[[:space:]]*,[[:space:]]*"
    "(.*)[[:space:]]*,[[:space:]]*"
    "(.*)[[:space:]]*,[[:space:]]*"
    "(.*)[[:space:]]*,[[:space:]]*"
    "(.*)");
  smatch match;
  istringstream addresses(addrlist);
  string address;
  while (getline(addresses, address)
    && regex_match(address, match, rgx))
      write_letter(match);
  return 0;
  }