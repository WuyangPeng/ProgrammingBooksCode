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


struct Vector;

template<typename Op>
struct Vop {
   Vop(Op const &op): op_(op) {}
   double operator[](ptrdiff_t k) const { return op_[k]; }
   ptrdiff_t size() const { return op_.size(); }
   operator Op() const { return op_; }
private:
   Op const op_;
};


struct Vector {
   Vector(): s_(0) {}

   explicit Vector(ptrdiff_t s): a_(new double[s]), s_(s) {}

   Vector(Vector const &a): a_(new double[a.s_]), s_(a.s_) {
      copy(a);
   }

   template<typename Op>
      Vector(Vop<Op> const &expr) {
         s_ = expr.size();
         a_ = new double[s_];
         for (ptrdiff_t k = 0; k!=s_; ++k)
            a_[k] = expr[k];
      }

   ~Vector() { if (s_!=0) delete[] a_; }

   Vector& operator=(Vector const &a)
      { if (this==&a) copy(a); return *this; }

   template<typename Op>
      Vector& operator=(Vop<Op> const &expr) {
         for (ptrdiff_t k = 0; k!=s_; ++k)
            a_[k] = expr[k];
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

   void copy(Vector const &a) {
      memcpy(a_, a.a_, s_*sizeof(double));
   }
private:
   double *a_;
   ptrdiff_t s_;
};


template<typename Va, typename Vb>
struct Vadd {
   Vadd(Va const &a, Vb const &b): a_(a), b_(b) {}
   double operator[](ptrdiff_t k) const
      { return a_[k]+b_[k]; }
   ptrdiff_t size() const { return a_.size(); }
private:
   Va const &a_;
   Vb const &b_;
};

inline
Vop<Vadd<Vector, Vector> > // <- return type
operator+(Vector const &a, Vector const &b) { // (1)
   return Vop<Vadd<Vector, Vector> >(Vadd<Vector, Vector>(a, b));
}

template<typename Va> inline
Vop<Vadd<Va, Vector> > // <- return type
operator+(Vop<Va> const &a, Vector const &b) { // (2)
   return Vop<Vadd<Va, Vector> >(Vadd<Va, Vector>(a, b));
}

template<typename Vb> inline
Vop<Vadd<Vector, Vb> > // <- return type
operator+(Vector const &a, Vop<Vb> const &b) { // (3)
   return Vop<Vadd<Vector, Vb> >(Vadd<Vector, Vb>(a, b));
}

template<typename Va, typename Vb> inline
Vop<Vadd<Va, Vb> > // <- return type
operator+(Vop<Va> const &a, Vop<Vb> const &b) { // (4)
   return Vop<Vadd<Va, Vb> >(Vadd<Va, Vb>(a, b));
}

template<typename Va, typename Vb>
struct Vmul {
   Vmul(Va const &a, Vb const &b): a_(a), b_(b) {}
   double operator[](ptrdiff_t k) const
      { return a_[k]*b_[k]; }
   ptrdiff_t size() const { return a_.size(); }
private:
   Va const &a_;
   Vb const &b_;
};

inline
Vop<Vmul<Vector, Vector> >
operator*(Vector const &a, Vector const &b) {
   return Vop<Vmul<Vector, Vector> >(Vmul<Vector, Vector>(a, b));
}

template<typename Va> inline
Vop<Vmul<Va, Vector> >
operator*(Vop<Va> const &a, Vector const &b) {
   return Vop<Vmul<Va, Vector> >(Vmul<Va, Vector>(a, b));
}

template<typename Vb> inline
Vop<Vmul<Vector, Vb> >
operator*(Vector const &a, Vop<Vb> const &b) {
   return Vop<Vmul<Vector, Vb> >(Vmul<Vector, Vb>(a, b));
}

template<typename Va, typename Vb> inline
Vop<Vmul<Va, Vb> >
operator*(Vop<Va> const &a, Vop<Vb> const &b) {
   return Vop<Vmul<Va, Vb> >(Vmul<Va, Vb>(a, b));
}

struct VScalar {
   VScalar(double v, ptrdiff_t s): v_(v), size_(s) {}
   double operator[](ptrdiff_t) const { return v_; }
   ptrdiff_t size() const { return size_; }
private:
   double v_;
   ptrdiff_t size_;
};

inline
Vop<Vmul<VScalar, Vector> >
operator*(double a, Vector const &b) {
   return Vop<Vmul<VScalar, Vector> >
             (Vmul<VScalar, Vector>(VScalar(a, b.size()), b));
}

inline
Vop<Vmul<Vector, VScalar> >
operator*(Vector const &a, double b) {
   return Vop<Vmul<Vector, VScalar> >
             (Vmul<Vector, VScalar>(a, VScalar(b, a.size())));
}

template<typename Va> inline
Vop<Vmul<Va, VScalar> >
operator*(Vop<Va> const &a, double b) {
   return Vop<Vmul<Va, VScalar> >(Vmul<Va, VScalar>(a, VScalar(b, a.size())));
}

template<typename Vb> inline
Vop<Vmul<VScalar, Vb> >
operator*(VScalar a, Vop<Vb> const &b) {
   return Vop<Vmul<VScalar, Vb> >(Vmul<VScalar, Vb>(VScalar(a, b.size()), b));
}


int main() {
   Vector x(10000), y(10000), z(10000);
   for (int i = 0; i<10000; ++i) {
      x[i] = y[i] = z[i] = 1.0/i;
   }
   for (int i = 0; i<10000; ++i) {
      x = 0.5*(x+y)+z;
   }
   return 0;
}

