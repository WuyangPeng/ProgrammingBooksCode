#include <unordered_set>
#include <iostream>
using std::tr1::unordered_set;
using std::cout;

typedef unordered_set<int> iset;

static void show_details(const iset& set)
  { // show container properties
  cout << "load factor: " << set.load_factor()
    << " target load factor: " << set.max_load_factor()
    << " buckets: " << set.bucket_count() << '\n';
  }

int main()
  { // show growth pattern
  iset set;
  show_details(set);
  int i;
  for (i = 0; i < 20; ++i)
    set.insert(i);
  show_details(set);
  for ( ; i < 40; ++i)
    set.insert(i);
  show_details(set);
  for ( ; i < 60; ++i)
    set.insert(i);
  show_details(set);
  set.max_load_factor(2.0);
  show_details(set);
  set.rehash(10);
  show_details(set);
  set.rehash(30);
  show_details(set);
  return 0;
  }