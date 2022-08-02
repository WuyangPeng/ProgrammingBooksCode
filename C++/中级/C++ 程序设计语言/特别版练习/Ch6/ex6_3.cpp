/* Code for exercise 6.3.
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

#include <iostream>
#include <map>
#include <string>

struct Stat {
   // Make sure the default constructor does the right thing
   // (used internally by the map data-structure)
   Stat(): sum_(0.0), count_(0) {}
   double sum_;
   int count_;
};

using std::string;
typedef std::map<string, Stat> Data;

void collect_data(Data &stats) {
   string name;
   while (cin >> name) {
      double datum;
      std::cin >> datum;
      stats[name].sum_ += datum;
      ++stats[name].count_;
   }
}

void print_stats(Data const &stats) {
   double global_sum = 0.0;
   int global_count = 0;
   for (Data::const_iterator p = stats.begin(); p!=stats.end(); ++p) {
      std::cout << (*p).first // the 'key' element
                << ": sum = " << (*p).second.sum_
                << ", mean = "
                << (*p).second.sum_/(*p).second.count_
                << '\n';
      global_sum += (*p).second.sum_;
      global_count += (*p).second.count_;
   }
   std::cout << "Global sum: " << global_sum
             << ", Global mean: " << global_sum/global_count
             << std::endl;
}

int main() {
   Data stats;
   collect_data(stats);
   print_stats(stats);
   return 0;
}

