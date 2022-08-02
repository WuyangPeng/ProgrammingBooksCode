#include <regex>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
using std::tr1::regex;
using std::tr1::sregex_token_iterator;
using std::map;
using std::cout; using std::basic_ostream;
using std::setw; using std::ostream_iterator;
using std::string; using std::copy;

string text =
"The quality of mercy is not strain'd,\n"
"It droppeth as the gentle rain from heaven\n"
"Upon the place beneath: it is twice bless'd;\n"
"It blesseth him that gives and him that takes:\n"
"'Tis mightiest in the mightiest; it becomes\n"
"The throned monarch better than his crown;\n"
"His sceptre shows the force of temporal power,\n"
"The attribute to awe and majesty,\n"
"Wherein doth sit the dread and fear of kings\n";
// William Shakespeare, \textup{The Merchant of Venice}

typedef map<string, int> counter;
typedef counter::value_type pairs;

namespace std { // add inserter to namespace std
template <class Elem, class Alloc>
basic_ostream<Elem, Alloc>& operator<<(
  basic_ostream<Elem, Alloc>& out, const pairs& val)
  {  // insert pair<string, int> into stream
  return out << setw(10) << val.first
    << ": " << val.second;
  }
}

int main()
  {  // count occurrences of each word
  regex word_sep("[ ,.\\t\\n;:]+");
  sregex_token_iterator words(
    text.begin(), text.end(), word_sep, -1);
  sregex_token_iterator end;
  map<string, int> word_count;
  while (words != end)
    ++word_count[*words++];
  copy(word_count.begin(), word_count.end(),
    ostream_iterator<pairs>(cout, "\n"));
  return 0;
  }
