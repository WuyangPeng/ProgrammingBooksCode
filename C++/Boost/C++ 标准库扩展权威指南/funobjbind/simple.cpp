#include <functional>
#include <iostream>
using std::tr1::bind;
using namespace std::tr1::placeholders;
using std::less; using std::cout;

template <class Pr>
int count_elements(const int *first, const int *last,
  Pr pred)
  { // count elements in the range [first,last) for which pred(elt) is true
  int count = 0;
  while (first != last)
    if (pred(*first++))
      ++count;
  return count;
  }

int count_ge10(int *first, int *last)
  { // bind 10 as first argument to less<int>
  int val = 10;
  return count_elements(first, last,
    bind(less<int>(), val, _1));
  }

int main()
  { // demonstrate simple uses of bind
  int values[6] = { 1, 3, 19, 12, 6, 11 };
  int count = count_ge10(values, values + 6);
  cout << count
    << " values greater than or equal to 10\n";
  return 0;
  }