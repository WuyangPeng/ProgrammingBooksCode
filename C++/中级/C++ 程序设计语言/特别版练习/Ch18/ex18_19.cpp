/* Code for exercise 18.19.
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
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <vector>

void error(char const *name, char const *msg) {
   std::cerr << name << msg << '\n';
   std::exit(1);
}

// The following is copied from Exercise 18.5:
template<class T, class Less, class Cursor>
void quicksort(Less fcn, Cursor left, Cursor right) {
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


void test_quicksort(char *filename) {
   std::ifstream in(filename);
   std::list<std::string> words;
   std::string word;
   while (in >> word)
      words.push_back(word);
   std::clock_t start = std::clock();
   quicksort<std::string>(std::less<std::string>(), words.begin(), words.end());
   std::cerr << "QuickSort: "
             << (std::clock()-start)/CLOCKS_PER_SEC << '\n';
}


void test_copysort(char *filename) {
   using std::string;
   std::ifstream in(filename);
   std::list<string> words;
   string word;
   while (in >> word)
      words.push_back(word);
   std::clock_t start = std::clock();
   std::vector<string> tmp(words.size(), string());
   std::copy(words.begin(), words.end(), tmp.begin());
   std::sort(tmp.begin(), tmp.end(), std::less<string>());
   std::copy(tmp.begin(), tmp.end(), words.begin());
   std::cerr << "Copy+Sort: "
             << (std::clock()-start)/CLOCKS_PER_SEC << '\n';
}


int main(int argc, char *argv[]) {
   if (argc!=2)
      error(argv[0], ": unexpected number of arguments.\n");
   test_quicksort(argv[1]);
   test_copysort(argv[1]);
   return 0;
}

