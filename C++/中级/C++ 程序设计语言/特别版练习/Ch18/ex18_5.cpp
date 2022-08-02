/* Code for exercise 18.5.
 | 
 | "C++ Solutions--Companion to The C++ Programming Language, Third Edition"
 | by David Vandevoorde; Addison-Wesley 1998; ISBN 0-201-30965-3.
 |
 | Permission to use, copy, modify, distribute and sell this software
 | and its documentation for any purpose is hereby granted without fee.
 | The author makes no representations about the suitability of this
 | software for any purpose.  It is provided "as is" without express or
 | implied warranty.
 `----------------------------------------------------------------------*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <list>

template<typename T, typename Less, typename Cursor>
void quicksort(Less &fcn, Cursor left, Cursor right) {
   // Zero- or one-element lists are trivially sorted:
   Cursor probe = left;
   if (probe==right or ++probe==right)
      return;

   T pivot = *left;
   // Partition the list into elements less-than and not
   // less-than the pivot (less-than is defined by fcn):
   Cursor p = partition(left, right, bind2nd(fcn, pivot));
   if (p==left)
      ++p;
   else
   if (p==right)
      --p;

   // Recursively sort these partitions:
   quicksort<T>(fcn, left, p);
   quicksort<T>(fcn, p, right);
}

template<typename T, typename Less>
void sort(std::list<T> &container,
          Less fcn = std::less<int>()) {
   quicksort<T>(fcn, container.begin(), container.end());
}

int main() {
   std::list<int> L;
   int value = 31;
   std::cout << "Before sorting: ";
   for (int k = 0; k!=10; ++k) {
      value = value*13261%1023;
      L.push_back(value); // Just some value
      std::cout << L.back() << ' ';
   }
   sort(L, std::less<int>());
   std::cout << "\nAfter sorting: ";
   for (list<int>::iterator p = L.begin(); p!=L.end(); ++p) {
      std::cout << *p << ' ';
   }
   std::cout << '\n';
   return 0;
}

