/* Code for exercise 15.2.
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
#include <typeinfo>

using namespace std;

#define CTOR(CC) {                                   \
   cout << #CC " constructor: "                      \
        << typeid(*this).name() << '\n';             \
   from_outside(this);                               \
   cout << '\n';                                     \
}

#define DTOR(CC) {                                   \
   cout << #CC " destructor: "                       \
        << typeid(*this).name() << '\n';             \
   from_outside(this);                               \
    cout << '\n';                                    \
}


void from_outside(struct A*);

struct A {
   A() CTOR(A)
   ~A() DTOR(A)
};

void from_outside(A *object) {
   cout << "Located at address: " << (void*)object
        << "\nFrom outside: " << typeid(*object).name()
        << endl;
}


void from_outside(struct B *object);

struct B: A { // Single inheritance, non-polymorphic base
   B() CTOR(B)
   virtual ~B() DTOR(B) // makes the class polymorphic
};

void from_outside(B *object) {
   cout << "Located at address: " << (void*)object
        << "\nFrom outside: " << typeid(*object).name()
        << endl;
}


struct C: B { // Single inheritance, polymorphic base
   C() CTOR(C)
   virtual ~C() DTOR(C) // make the class polymorphic
};

struct D: B { // Single inheritance, polymorphic base
   D() CTOR(D)
   virtual ~D() DTOR(D) // make the class polymorphic
};

void from_outside(struct E*);

struct E: C, D { // Multiple inheritance, regular bases
   E() CTOR(E)
   virtual ~E() DTOR(E) // make the class polymorphic
};

void from_outside(E *object) {
   from_outside((C*)object); // Resolve conversion to B*
   from_outside((D*)object); // Ditto
}


struct F: virtual B {
   F() CTOR(F)
   virtual ~F() DTOR(F) // make the class polymorphic
};

struct G: virtual B {
   G() CTOR(G)
   virtual ~G() DTOR(G)
};

struct H: F, G { // Multiple inheritance, virtual bases
   H() CTOR(H)
   virtual ~H() DTOR(H)
};

void from_outside(struct I*);

struct I: E, H { // All of it
   I() CTOR(I)
   virtual ~I() DTOR(I)
};

void from_outside(I *object) {
   from_outside((C*)object); // Resolve conversion to B*
   from_outside((D*)object); // Ditto
   from_outside((H*)object); // And once more
}

int main() {
   I complex_object;
   cout << "Total size of I-object: " << sizeof(I) << endl;
}



