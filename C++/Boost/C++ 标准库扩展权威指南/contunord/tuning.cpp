#include <unordered_set>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
using std::cout; using std::setw;
using std::copy; using std::ostream_iterator;

typedef std::tr1::unordered_set<int> iset;
typedef iset::value_type elt;

static void show_buckets(const iset& set)
  { // show details of buckets in set
  cout << setw(3) << set.size() << " elements, "
    << setw(3) << set.bucket_count() << " buckets, "
    << " load factor " << set.load_factor() << ".\n";
  for (int i = 0; i < set.bucket_count(); ++i)
    cout << i << ':' << set.bucket_size(i) << " ";
  cout << '\n';
  ostream_iterator<elt> output(cout, " ");
  for (int i = 0; i < set.bucket_count(); ++i)
    { // show contents of bucket i
    cout << setw(3) << i << ": ";
    copy(set.begin(i), set.end(i), output);
    cout << '\n';
    }
  }

int main()
  { // demonstrate use of bucket functions
  iset set;
  for (int i = 0; i < 100; ++i)
    set.insert(i);
  show_buckets(set);
  return 0;
  }