/* Code for exercise 14.1.
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

#include <iostream.h>


template<class R = void, class T1 = void, class T2 = void>
struct STC {
   typedef R (*PF)(T1, T2);
   STC(PF pf): prev_pf_(cur_pf_) { cur_pf_ = pf; }
   ~STC() { cur_pf_ = prev_pf_; }
   R operator()(T1 a, T2 b) { return cur_pf_(a, b); }
private:
   PF prev_pf_;
   static PF cur_pf_;
};

template<class R, class T1, class T2>
typename STC<R, T1, T2>::PF STC<R, T1, T2>::cur_pf_ = 0;

template<class R, class T1>
struct STC<R, T1, void> { // Partial specialization
   typedef R (*PF)(T1);
   STC(PF pf): prev_pf_(cur_pf_) { cur_pf_ = pf; }
   ~STC() { cur_pf_ = prev_pf_; }
   R operator()(T1 a) { return cur_pf_(a); }
private:
   PF prev_pf_;
   static PF cur_pf_;
};

template<class R, class T1>
typename STC<R, T1, void>::PF STC<R, T1, void>::cur_pf_ = 0;

template<typename R>
struct STC<R, void, void> { // Partial specialization
   typedef R (*PF)();
   STC(PF pf): prev_pf_(cur_pf_) { cur_pf_ = pf; }
   ~STC() { cur_pf_ = prev_pf_; }
   R operator()() { return cur_pf_(); }
private:
   PF prev_pf_;
   static PF cur_pf_;
};

template<class R>
typename STC<R, void, void>::PF STC<R, void, void>::cur_pf_ = 0;


int g(int i) {
   return i*i;
}

int f() {
   STC<int, int> gc(&g);
   std::cout << gc(4) << '\n';
   return 3;
}


int main() {
   STC<int> fc(&f);
   {
      STC<int, int> gc(&g);
      std::cout << gc(7) << '\n';
   }
   std::cout << fc() << '\n';
   return 0;
}

