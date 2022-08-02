/* Code for exercises 11.8 and 11.10.
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

/*

This header contains the String implementation as presented in
Bjarne Stroustrup's "The C++ Programming Language (third edition)".

It is used by ex11_8.cpp and ex11_10.cpp.

*/

#include <assert.h>
#include <iostream>
#include <string.h>


class String {
   struct Srep; // Internal representation.
   Srep *rep;
   friend struct String_iter;
public:
   class Cref; // Behaves somewhat like char&.
   class Range {}; // For exceptions.
 

   // Creation, copying and destruction:
   inline String(); // x = ""
   inline String(char const*); // x = "abc"
   inline String(String const&); // x = other_string
   inline String& operator=(char const*);
   inline String& operator=(String const&);
   inline ~String();

   // Access and bounds-checking:
   inline void check(int) const;
   inline char read(int) const;
   inline void write(int, char);
   inline char operator[](int) const;
   inline Cref operator[](int);
   inline int size() const;

   // Access to C-style representation (Exercise 11.10):
   char const* c_string() const;

   // Substring operator (Exercise 11.8):
   inline String operator()(int left, int right);

   // Relational operators:
   friend bool operator==(String const&, char const*);
   friend bool operator==(String const&, String const&);
   friend bool operator!=(String const&, char const*);
   friend bool operator!=(String const&, String const&);

   // Concatenation:
   inline String* operator+=(char const*); // Exercise.
   inline String& operator+=(String const&); // Exercise.

   // Formatted I/O:
   friend ostream& operator<<(ostream&, String const&); // Exercise.
   friend istream& operator>>(istream&, String&); // Exercise.
};


// Internal representation of a String (with sharing):

struct String::Srep {
   char *s; // Pointer to array of chars (elements).
   int sz; // Number of chars.
   int n; // Reference count.

   Srep(int nsz, char const *p) {
      n = 1;
      sz = nsz;
      s = new char[sz+1]; // Add space for terminator.
      strcpy(s, p);
   }

   ~Srep() { delete[] s; }

   Srep* get_own_copy() { // Clone if necessary.
      if (n==1) { return this; }
      --n;
      return new Srep(sz, s);
   }

   void assign(int nsz, char const *p) {
      if (sz!=nsz) {
         delete[] s;
         sz = nsz;
         s = new char[sz+1];
      }
      strcpy(s, p);
   }

private: // Prevent copying
   Srep(Srep const&);
   Srep& operator=(Srep const&);
};


// Dispatcher (proxy, helper) for writing to a char in a String:
class String::Cref { // Reference to s[i]
   friend class String;
   String &s;
   int i;
   Cref(String &ss, int ii): s(ss), i(ii) {}
public:
   operator char() { return s.read(i); } // Yield value.
   void operator=(char c) { s.write(i, c); } // Change value.
};


// String members functions:

inline String::String() { rep = new Srep(0, ""); }

inline String::String(char const *s) { rep = new Srep(strlen(s), s); }

inline String::String(String const &x) { // Copy constructor.
   ++(x.rep->n);
   rep = x.rep; // Share representation.
}

inline String& String::operator=(char const *s) {
   if (rep->n==1) { rep->assign(strlen(s), s); } // Recycle Srep.
   else { // Use new Srep.
      --(rep->n);
      rep = new Srep(strlen(s), s);
   }
   return *this;
}

inline String& String::operator=(String const &x) { // Copy assignment.
   ++(x.rep->n); // Protect against "str = str;"
   if (--(rep->n)==0) { delete rep; }
   rep = x.rep; // Share representation.
   return *this;
}

inline String::~String() { if (--(rep->n)==0) { delete rep; } }


inline void String::check(int i) const {
   if (i<0 || rep->sz<=i) {
      throw Range();
   }
}

inline char String::read(int i) const { return rep->s[i]; }

char String::operator[](int i) const { check(i); return rep->s[i]; }

inline void String::write(int i, char c) {
   rep = rep->get_own_copy();
   rep->s[i] = c;
}

inline String::Cref String::operator[](int i) {
   check(i);
   return String::Cref(*this, i);
}

inline int String::size() const { return rep->sz; }

inline bool operator==(String const &x, char const *s) {
   return strcmp(x.rep->s, s)==0;
}

inline bool operator==(String const &x, String const &y) {
   return strcmp(x.rep->s, y.rep->s)==0;
}

inline bool operator!=(String const &x, char const *s) {
   return strcmp(x.rep->s, s)!=0;
}

inline bool operator!=(String const &x, String const &y) {
   return strcmp(x.rep->s, y.rep->s)!=0;
}



