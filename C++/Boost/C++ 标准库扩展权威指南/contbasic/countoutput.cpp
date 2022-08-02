#include <iostream>
using std::cout;

template <class Iter>
void setcount(Iter first, int count)
  { // algorithm to write successive values to sequence
  for (int i = 0; i < count; ++i)
    *first++ = i;
  }

int main()
  { // demonstrate use of output sequence
  const int NVALS = 6;
  int values[NVALS];
  setcount(values, NVALS);
  for (int i = 0; i < NVALS; ++i)
    cout << values[i] << ' ';
  cout << '\n';
  return 0;
  }