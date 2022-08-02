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

#include "Board.H"
#include "BoardTextViewer.H"
#include <assert.h>

void BoardTextViewer::draw(Board &board) {
   assert((Board::kNCols<10) && (Board::kNRows<27));
   int r, c;
   output_ << "\n   ";
   for (c = 1; c!=Board::kNCols+1; ++c)
      output_ << ' ' << c;
   output_ << "\n  .-";
   for (c = 1; c!=Board::kNCols+1; ++c)
      output_ << "--";
   for (r = 1; r!=Board::kNRows+1; ++r) {
      output_ << "\n " << char('a'+r-1) << '|';
      for (c = 1; c!=Board::kNCols+1; ++c)
         if (board(r, c)==kWhite)
            output_ << " o";
         else if (board(r, c)==kBlack)
            output_ << " *";
         else
            output_ << "  ";
   }
   output_ << "\n[ Black(*): " << board.score(kBlack)
           << "    White(o): " << board.score(kWhite)
           << " ]\n\n";
}

