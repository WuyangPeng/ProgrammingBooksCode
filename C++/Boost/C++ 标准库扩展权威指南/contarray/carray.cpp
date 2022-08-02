#include <algorithm>
#include <iostream>
using std::cout; using std::sort;

void do_sort(int *values, int count)
  { // sort contents of array
  sort(values, values + count);
  }

int main()
  { // demonstrate use of C-style array as STL sequence
  const int ELEMS = 6;
  int values[ELEMS] = { 3, 1, 4, 2, 9, 8 };
  for (int i = 0; i < ELEMS; ++i)
    cout << values[i] << ' ';
  cout << '\n';
  do_sort(values, ELEMS);
  for (int i = 0; i < ELEMS; ++i)
    cout << values[i] << ' ';
  cout << '\n';
  return 0;
  }
