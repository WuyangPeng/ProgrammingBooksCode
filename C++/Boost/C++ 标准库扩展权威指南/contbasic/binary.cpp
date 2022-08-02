#include <functional>
#include <iostream>
using std::binary_function;
using std::cout;

template <class Ty>
struct lt : binary_function<Ty, Ty, bool>
  { // compare values
  bool operator()(const Ty& val0, const Ty& val1)
    { // return val0 < val1
    return val0 < val1;
    }
  };

template <class Iter, class Cmp>
void merge(Iter first1, Iter last1,
  Iter first2, Iter last2,
  Iter dest, Cmp cmp)
  { // merge sorted ranges
  while (first1 != last1 && first2 != last2)
    { // copy lesser element to output sequence
    if (cmp(*first1, *first2))
      *dest++ = *first1++;
    else
      *dest++ = *first2++;
    }
  while (first1 != last1)
    *dest++ = *first1++;
  while (first2 != last2)
    *dest++ = *first2++;
  }

int main()
  { // demonstrate use of binary function object
  const int NVAL0 = 6;
  const int NVAL1 = 7;
  const int NRES = NVAL0 + NVAL1;
  int values0[NVAL0] = { 1, 4, 9, 16, 25, 36 };
  int values1[NVAL1] = { 1, 1, 2, 3, 5, 8, 13 };
  int res[NRES];
  merge(values0, values0 + NVAL0,
    values1, values1 + NVAL1,
    res, lt<int>());
  for (int i = 0; i < NRES; ++i)
    cout << res[i] << ' ';
  cout << '\n';
  return 0;
  }