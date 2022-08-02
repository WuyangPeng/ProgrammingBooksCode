/* Code for exercise 10.5.
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

#include <assert.h>
#include <iostream>
#include <stddef.h>
#include <stdlib.h> // For rand()

struct Histogram {
   Histogram(ptrdiff_t minval, size_t gap, size_t n_bins);
   ~Histogram() { delete[] bin_; }
   void record(ptrdiff_t);
   void output_to(std::ostream&);
private:
   ptrdiff_t const minval_, maxval_;
   size_t const gap_;
   size_t *const bin_;
   size_t n_small_, n_large_;
};


Histogram::Histogram(ptrdiff_t m, size_t g, size_t n)
   : minval_(m), maxval_(m+n*g-1), gap_(g),
     bin_(new size_t[n]), n_small_(0), n_large_(0) {
   assert(g!=0 && n!=0);
   for (int k = 0; k!=n; ++k) { bin_[k] = 0; }
}

void Histogram::record(ptrdiff_t datapoint) {
   if (datapoint<minval_)
      ++n_small_;
   else if (datapoint>maxval_)
      ++n_large_;
   else
      ++bin_[(datapoint-minval_)/gap_];
}

void Histogram::output_to(std::ostream &output) {
   output << "< " << minval_ << ": " << n_small_ << '\n';
   for (ptrdiff_t left = minval_; left<maxval_; left += gap_)
      output << left << ".." << left+gap_-1 << ": " 
             << bin_[(left-minval_)/gap_] << '\n';
   output << "> " << maxval_ << ": " << n_large_ << '\n';
}

int main() {
   Histogram h(0, 10, 10); /* 10 bins that are 10 units wide */
   for (int k = 0; k!=10000; ++k) {
      h.record((int)(10.0*rand()/rand()));
   }
   h.output_to(std::cout);
   return 0;
}

