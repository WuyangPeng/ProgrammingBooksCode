/* Code for exercise 15.3.
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

#ifndef PLAYER_H
#define PLAYER_H

#include "Board.H"

struct Player {
   virtual ~Player() {}
   virtual void get_move(Board const&, int &r, int &c) = 0;
   virtual void skip_move(Board const&) {}
   virtual void win() {}
   virtual void lose() {}
   virtual void tie() {}
};
#endif

