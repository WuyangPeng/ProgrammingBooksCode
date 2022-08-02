#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <list>
using std::tr1::array;
using std::copy; using std::find;
using std::ostream_iterator;
using std::list;
using std::cout; using std::setw;
using std::numeric_limits;

typedef list<int> bucket;
typedef array<bucket, 5> table;

size_t hash(int i)
  { // return hash value for i
  return i;
  }

void show(const table& tbl)
  { // show contents of buckets in table
  for (int i = 0; i < tbl.size(); ++i)
    { // show contents of bucket i
    cout << "bucket " << setw(2) << i << ": ";
    copy(tbl[i].begin(), tbl[i].end(),
      ostream_iterator<int>(cout, " "));
    cout << '\n';
    }
  }

void insert(table& tbl, int val)
  { // insert val into table
  size_t hash_val = hash(val) % tbl.size();
  tbl[hash_val].push_back(val);
  }

bool contains(const table& tbl, int val)
  { // return true if tbl contains val
  int hash_val = hash(val) % tbl.size();
  bucket::const_iterator first = tbl[hash_val].begin();
  bucket::const_iterator last = tbl[hash_val].end();
  return find(first, last, val) != last;
  }

void report(const table& tbl, int val)
  { // report whether tbl contains val
  cout << "table "
    << (contains(tbl, val) ? "contains "
       : "does not contain ")
    << val << '\n';
  }

int main()
  { // demonstrate simple hash table
  table tbl;
  insert(tbl, 3);
  insert(tbl, 195);
  insert(tbl, 5);
  insert(tbl, 6);
  insert(tbl, 55);
  insert(tbl, 1);
  insert(tbl, 33);
  insert(tbl, 40);
  show(tbl);
  report(tbl, 3);
  report(tbl, 4);
  return 0;
  }
