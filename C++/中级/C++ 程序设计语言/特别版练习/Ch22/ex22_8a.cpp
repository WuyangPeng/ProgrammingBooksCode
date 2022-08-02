/* Code for exercise 22.8.
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
#include <stddef.h>
#include <string.h>

struct SimpleArray {
   SimpleArray(): s_(0) {}
   SimpleArray(ptrdiff_t s): a_(new double[s]), s_(s) {}
   SimpleArray(SimpleArray const &a)
      : a_(new double[a.s_]), s_(a.s_) {
      copy(a);
   }
   ~SimpleArray() { if (s_!=0) delete[] a_; }
   SimpleArray& operator=(SimpleArray const&a) {
      if (&a!=this)
         copy(a);
      return *this;
   }
   ptrdiff_t size() const { return s_; }
   void size(ptrdiff_t s) {
      assert(s_==0 and s>0);
      s_ = s;
      a_ = new double[s];
   }
   double const& operator[](ptrdiff_t k) const
      { return a_[k]; }
   double& operator[](ptrdiff_t k) { return a_[k]; }
   void copy(SimpleArray const &a) {
      memcpy(a_, a.a_, s_*sizeof(double));
   }
private:
   double *a_;
   ptrdiff_t s_;
};


SimpleArray operator+(SimpleArray const &a,
                      SimpleArray const &b) {
   SimpleArray result(a.size());
   for (ptrdiff_t k = 0; k!=a.size(); ++k)
      result[k] = a[k]+b[k];
   return result;
}

SimpleArray operator*(SimpleArray const &a,
                      SimpleArray const &b) {
   SimpleArray result(a.size());
   for (ptrdiff_t k = 0; k!=a.size(); ++k)
      result[k] = a[k]*b[k];
   return result;
}

SimpleArray operator*(double a, SimpleArray const &b) {
   SimpleArray result(b.size());
   for (ptrdiff_t k = 0; k!=b.size(); ++k)
      result[k] = a*b[k];
   return result;
}


int main() {
   SimpleArray x(10000), y(10000), z(10000);
   for (int i = 0; i<10000; ++i) {
      x[i] = y[i] = z[i] = 1.0/i;
   }
   for (int i = 0; i<10000; ++i) {
      x = 0.5*(x+y)+z;
   }
   return 0;
}

