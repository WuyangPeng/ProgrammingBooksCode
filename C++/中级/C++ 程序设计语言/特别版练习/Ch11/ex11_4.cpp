/* Code for exercise 11.4.
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

/* Notes:

This is not a complete program (no main()).
 
*/


struct RINT {
   RINT(int i): i_(i) {}
   RINT& operator=(int i) { i_ = i; return *this; }
private:
   int i_;
   friend RINT operator+(RINT const&);
   friend RINT operator+(RINT const&, RINT const&);
   friend RINT operator-(RINT const&);
   friend RINT operator-(RINT const&, RINT const&);
   friend RINT operator*(RINT const&, RINT const&);
   friend RINT operator/(RINT const&, RINT const&);
   friend RINT operator%(RINT const&, RINT const&);
};

RINT operator+(RINT const &a) {
   return a;
}

RINT operator+(RINT const &a, RINT const &b) {
   return RINT(a.i_+b.i_);
}

RINT operator-(RINT const &a) {
   return RINT(-a.i_);
}

RINT operator-(RINT const &a, RINT const &b) {
   return RINT(a.i_-b.i_);
}

RINT operator*(RINT const &a, RINT const &b) {
   return RINT(a.i_*b.i_);
}

RINT operator/(RINT const &a, RINT const &b) {
   return RINT(a.i_/b.i_);
}

RINT operator%(RINT const &a, RINT const &b) {
   return RINT(a.i_%b.i_);
}

