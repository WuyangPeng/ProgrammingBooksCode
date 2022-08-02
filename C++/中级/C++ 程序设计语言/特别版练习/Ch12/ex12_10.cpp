/* Code for exercise 12.10.
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
#include <map>
#include <typeinfo>
#include <utility> // for pair<>

struct Shape {
   virtual ~Shape() {} // Make Shape polymorphic
};

struct Square: Shape {
   // ...
};

struct Triangle: Shape {
   // ...
};


// We will map pairs of type_info pointers to
// pointers to intersection functions:
using std::type_info;
typedef std::pair<type_info const*, type_info const*> TwoTypes;
typedef bool (*Intersector)(Shape*, Shape*);

// The map needs an ordering relation:
bool operator<(TwoTypes const &a, TwoTypes const &b) {
   if ((a.first)->before(*b.first))
      return true;
   else
   if ((*a.first)==(*b.first))
      return (a.second)->before(*b.second);
   else
      return false;
}

typedef std::map<TwoTypes, Intersector> DispatchMap;

DispatchMap& intersector_map() {
   static DispatchMap dispatch_table;
   return dispatch_table;
}

template<class Type1, class Type2>
void register_intersector(Intersector pf) {
   intersector_map()[TwoTypes(&typeid(Type1), &typeid(Type2))] = pf;
}

bool intersect(Shape *a, Shape *b) {
   std::cerr << "Looking for intersection function for "
             << typeid(*a).name() << " and " << typeid(*b).name() << ": ";
   TwoTypes combination(&typeid(*a), &typeid(*b));
   DispatchMap::iterator p = intersector_map().find(combination);
   return (*p->second)(a, b);
}

bool squares_intersect(Shape *a, Shape *b) {
   std::cerr << "entering squares_intersect.\n";
   assert(a && b);
   Square *sq1 = dynamic_cast<Square*>(a);
   Square *sq2 = dynamic_cast<Square*>(b);
   // ... code to determine if *sq1 and *sq2 intersect
   return false;
}

bool square_and_triangle_intersect(Shape *a, Shape *b) {
   std::cerr << "entering square_and_triangle_intersect.\n";
   assert(a && b);
   Square *sq;
   Triangle *tr;
   if ((sq = dynamic_cast<Square*>(a))!=0) {
      tr = dynamic_cast<Triangle*>(b);
   } else { // *a is a Triangle, *b is a Square
      tr = dynamic_cast<Triangle*>(a);
      sq = dynamic_cast<Square*>(b);
   }
   // ... code to determine if *sq and *tr intersect
   return false;
}

void register_all_intersectors() {
   register_intersector<Square, Square>(squares_intersect);
   register_intersector<Square, Triangle>(square_and_triangle_intersect);
   register_intersector<Triangle, Square>(square_and_triangle_intersect);
   // ...
}

int main() {
   register_all_intersectors();
   Square s;
   Triangle t;
   intersect(&s, &s);
   intersect(&t, &s);
   // ...
}

