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

#ifndef BOARD_H
#define BOARD_H

#include <assert.h>

enum MoveResult { kUnsuccessful = 0, kSuccessful };
enum Color { kEmpty = 0, kWhite, kBlack };

inline Color opponent_of(Color color) {
   assert((color==kWhite) or (color==kBlack));
   return color==kWhite? kBlack: kWhite;
}

struct Board {
   Board();
   Color operator()(int r, int c) const { return b_[r][c]; }
   void move(Color, int r, int c);
   MoveResult get_possible_move(Color,
                                int &r, int &c) const;
   MoveResult valid_move(Color, int r, int c) const;
   int score(Color color) const
      { return color==kWhite? white_score_: black_score_; }
   enum { kNRows = 8, kNCols = 8 };
private:
   Color b_[kNRows+2][kNCols+2];
   int black_score_, white_score_;
};
#endif

