/* Code for exercise 6.12.
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
#include <numeric>
#include <set>
#include <string>

using std::string;
typedef std::multiset<double> SubData;
typedef std::map<string, SubData> Data;

void collect_data(Data &stats) {
   string name;
   while (std::cin >> name) {
      double datum;
      std::cin >> datum;
      stats[name].insert(datum);
   }
}

void print_setstats(SubData const &stats) {
   std::size_t count = 0;
   double sum = 0.0, median;
   for (SubData::const_iterator p = stats.begin();
        p!=stats.end(); ++p, ++count) {
      if (count==(stats.size()-1)/2) {
         median = *p;
         if (stats.size()%2==0) {
            SubData::const_iterator q = p;
            median = (median+(*++q))/2.0;
         }
      }
      sum += *p;
   }
   std::cout << "sum = " << sum
             << ", mean = " << sum/double(count)
             << ", median = " << median << std::endl;
}

// merge_stats: move items from the per-name sets to 
// a global set, so that we can eventually compute the
// overall statistics.
void merge_stats(SubData &dest, SubData &src) {
   // Associative containers can take "insertion hints":
   SubData::iterator hint = dest.begin();
   for (SubData::iterator p = src.begin(); p!=src.end(); ++p) {
      hint = dest.insert(hint, *p);
      src.erase(p);
   }
}

void print_stats(Data &stats) {
   SubData global_set;
   for (Data::iterator p = stats.begin();
        p!=stats.end(); ++p) {
      cout << (*p).first << ": ";
      print_setstats((*p).second);
      merge_stats(global_set, (*p).second);
   }
   cout << "Global stats: ";
   print_setstats(global_set);
}

int main() {
   Data stats;
   collect_data(stats);
   print_stats(stats);
   return 0;
}

