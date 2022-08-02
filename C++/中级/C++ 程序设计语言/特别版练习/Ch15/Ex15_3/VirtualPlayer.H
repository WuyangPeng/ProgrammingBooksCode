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

#ifndef VIRTUALPLAYER_H
#define VIRTUALPLAYER_H

#include "Board.H"

struct VirtualPlayer {
   VirtualPlayer(Color c): color_(c), maxdepth_(6) {}
   void get_move(Board const&, int &row, int &col);
private:
   int eval_self(Board const&, int r, int c,
                 int best, int worst, int depth);
   int eval_opponent(Board const&, int r, int c,
                     int best, int worst, int depth);
   int eval_end_of_game(Board const&);
   int value_of(Board const&);
   Color color_;
   int maxdepth_;
};
#endif

