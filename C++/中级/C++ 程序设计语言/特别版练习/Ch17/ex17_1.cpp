/* Code for exercise 17.1
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

#include <deque>
#include <list>
#include <numeric>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

int const kMinSize = 1000;
int const kMaxSize = 8000;

int *data = new int[kMaxSize];

void generate_data() {
   for (int k = 0; k!=kMaxSize; ++k)
      data[k] = rand();
}

void consume(int, ...) {}



int *c_array = new int[kMaxSize];

void c_array_fill(int size) {
   delete[] c_array;
   c_array = new int[size];
   for (int k = 0; k!=size; ++k)
      c_array[k] = data[k];
}

void c_array_traverse(int size) {
   int sum = 0;
   for (int k = 0; k!=size; ++k)
      sum += c_array[k];
   consume(0, sum);
}

void c_array_lookup(int size) {
   int const desired_value = data[size/2];
   int k;
   for (k = 0; k!=size; ++k)
      if (c_array[k]==desired_value)
         break;
   consume(0, k);
}



std::vector<int> *std_vector = new std::vector<int>;

void vector_fill(int size) {
   delete std_vector;
   std_vector = new std::vector<int>;
   for (int k = 0; k!=size; ++k)
      std_vector->push_back(data[k]);
}

void vector_traverse(int) {
   consume(0, std::accumulate(std_vector->begin(),
                              std_vector->end(), 0));
}

void vector_lookup(int size) {
   consume(0, std::find(std_vector->begin(),
                        std_vector->end(),
                        data[size/2]));
}



std::deque<int> *std_deque = new std::deque<int>;

void deque_fill(int size) {
   delete std_deque;
   std_deque = new std::deque<int>;
   for (int k = 0; k!=size; ++k)
      std_deque->push_back(data[k]);
}

void deque_traverse(int) {
   consume(0, std::accumulate(std_deque->begin(),
                              std_deque->end(), 0));
}

void deque_lookup(int size) {
   consume(0, std::find(std_deque->begin(),
                        std_deque->end(),
                        data[size/2]));
}



std::list<int> *std_list = new std::list<int>;

void list_fill(int size) {
   delete std_list;
   std_list = new std::list<int>;
   for (int k = 0; k!=size; ++k)
      std_list->push_back(data[k]);
}

void list_traverse(int) {
   consume(0, std::accumulate(std_list->begin(),
                              std_list->end(), 0));
}

void list_lookup(int size) {
   consume(0, std::find(std_list->begin(), std_list->end(),
                        data[size/2]));
}



std::set<int> *std_set = new std::set<int>;

void set_fill(int size) {
   delete std_set;
   std_set = new std::set<int>;
   for (int k = 0; k!=size; ++k)
      std_set->insert(data[k]);
}
void set_traverse(int) {
   consume(0, std::accumulate(std_set->begin(),
                              std_set->end(), 0));
}

void set_lookup(int size) {
   consume(0, std_set->find(data[size/2]));
}



void print_header() {
   printf(
"Container kind    Size    Insertion  Traversal  Lookup\n"
"-------------------------------------------------------\n"
   );
}

typedef void (*Test)(int);

int calibrate(int seconds, Test test, int size) {
   clock_t end = clock()+seconds*CLOCKS_PER_SEC;
   int n;
   for (n = 0; clock()<end; ++n)
      test(size);
   return n;
}

double time_in_seconds(int n , Test test, int size) {
   clock_t start = clock();
   for (int k = 0; k!=n; ++k)
      test(size);
   return (clock()-start)/double(CLOCKS_PER_SEC);
}

void benchmark(char const *container_name, int n,
               Test filling, Test traversal, Test lookup) {
   for (int size = kMinSize; size<=kMaxSize; size *= 2) {
      filling(size); // Set up starting data set
      printf("%13s  %7d:   %7.2f   %7.2f   %7.2f\n",
             size==kMinSize? container_name: "", size,
             time_in_seconds(n, filling, size),
             time_in_seconds(n, traversal, size),
             time_in_seconds(n, lookup, size));
   }
   printf("\n");
}

int main() {
   generate_data();
   c_array_fill(kMinSize); // Initialize for calibration
   int n = calibrate(1 /* sec */, &c_array_lookup, kMinSize);
   print_header();
   benchmark("C array", n,
             c_array_fill, c_array_traverse, c_array_lookup);
   benchmark("std::vector", n,
             vector_fill, vector_traverse, vector_lookup);
   benchmark("std::deque", n,
             deque_fill, deque_traverse, deque_lookup);
   benchmark("std::list", n,
             list_fill, list_traverse, list_lookup);
   benchmark("std::set", n,
             set_fill, set_traverse, set_lookup);
return 0;
}

