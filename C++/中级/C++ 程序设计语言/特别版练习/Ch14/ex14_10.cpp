/* Code for exercise 14.10.
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

#include <stdio.h>

struct Callback {
   virtual void operator()() = 0;
   virtual void operator()() const = 0;
};

template<void (*PF)()>
struct CallbackFunction: Callback {
   virtual void operator()() { PF(); }
   virtual void operator()() const { PF(); }
};

template<typename T, void (T::*MF)()>
struct ObjectCallback: Callback {
   ObjectCallback(T &object): object_(object) {}
   virtual void operator()() { (object_.*MF)(); }
   virtual void operator()() const { (object_.*MF)(); }
private:
   T &object_;
};

void a() { printf("Hello\n"); }
void b() { printf("World!\n"); }

struct X {
   X(char const *p, char const *q): p_(p), q_(q) {}
   void f() { printf("%s\n", p_); }
   void g() { printf("%s\n", q_); }
private:
   char const *p_, *q_;
};

void greet(Callback const &first, Callback const &second) {
   first();
   second();
}

int main() {
   greet(CallbackFunction<&a>(), CallbackFunction<&b>());
   X x("Hello", "Class!");
   greet(ObjectCallback<X, &X::f>(x), ObjectCallback<X, &X::g>(x));
}

