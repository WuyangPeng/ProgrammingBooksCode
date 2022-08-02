#include <unordered_map>
#include <iostream>
#include <ostream>
#include <iomanip>
#include <string>
#include <utility>
#include <algorithm>
#include <iterator>
#include <functional>
using std::tr1::unordered_multimap;
using std::string; using std::make_pair; using std::pair;
using std::setw; using std::setfill;
using std::copy; using std::cout;
using std::basic_ostream; using std::ostream_iterator;
using std::ios_base; using std::ios;
using std::unary_function;

typedef unordered_multimap<string, string> dictionary;
typedef dictionary::value_type element;

static const char *pairs[] =
  { // English/German word pairs
  "day",      "Tag",
  "strange",  "fremd",
  "car",      "Auto",
  "smart",    "elegant",
  "trait",    "Merkmal",
  "strange",  "seltsam",
  "smart",    "raffiniert",
  "smart",    "klug",
  "clever",   "raffiniert",
  0,            0
  };

namespace std { // add inserter to namespace std
template <class Elem, class Traits>
basic_ostream<Elem, Traits>& operator<<(
  basic_ostream<Elem, Traits>& str, const element& elt)
  { // insert element into stream and restore flags
  ios_base::fmtflags flags = str.flags();
  str.setf(ios::left, ios::adjustfield);
  str << ' ' << setw(10) << elt.first << elt.second;
  str.flags(flags);
  return str;
  }
}

template <class InIt, class OutIt, class Pred>
OutIt copy_if(InIt first, InIt last, OutIt dest, Pred pr)
  { // copy elements for which pr(*first) is true
  for ( ; first != last; ++first, ++dest)
    if (pr(*first))
      *dest = *first;
  return dest;
  }

struct equals
  : unary_function<element, bool>
  { // callable type that matches second object in pair to string
  equals(const string& s) : str(s) {}
  bool operator()(const element& elt) const
    { // return true for match
    return elt.second == str;
    }
private:
  string str;
  };

int main()
  { // demonstrate use of unordered_multimap
  dictionary dict;

    // initialize:
  const char **cur = pairs;
  while (cur[0])
    { // add initial entries
    dict.insert(make_pair(cur[0], cur[1]));
    cur += 2;
    }

    // print out all elements
  ostream_iterator<element> output(cout, "\n");
  cout << make_pair("English", "German") << '\n';
  cout << setfill('-') << setw(20) << ""
    << setfill(' ') << '\n';
  copy(dict.begin(), dict.end(), output);

    // print out all values for key "smart"
  string key("smart");
  cout << '\n' << key << ": \n";
  copy(dict.lower_bound(key), dict.upper_bound(key),
    output);

    // print out all keys for value "raffiniert"
  string value("raffiniert");
  cout << '\n' << value << ": \n";
  copy_if(dict.begin(), dict.end(),
    output, equals(value));
  return 0;
  }
