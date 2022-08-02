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

#include <assert.h>
#include "Board.H"

Board::Board() {
   for (int r = 0; r!=kNRows+2; ++r)
      for (int c = 0; c!=kNRows+2; ++c)
         b_[r][c] = kEmpty;
   b_[kNRows/2+1][kNRows/2]
      = b_[kNRows/2][kNRows/2+1] = kBlack;
   b_[kNRows/2][kNRows/2]
      = b_[kNRows/2+1][kNRows/2+1] = kWhite;
   black_score_ = white_score_ = 2;
}


MoveResult Board::valid_move(Color color,
                             int r, int c) const {
   assert((r>=1) and (r<=kNRows)
      and (c>=1) and (c<=kNCols));
   if (b_[r][c]!=kEmpty)
      return kUnsuccessful;
   Color opponent = opponent_of(color);
   for (int dr = -1; dr!=2; ++dr)
      for (int dc = -1; dc!=2; ++dc)
         if ((dr!=0) or (dc!=0)) {
            int row = r, col = c;
            do {
               row += dr;
               col += dc;
            } while (b_[row][col]==opponent);
            if ((b_[row][col]==color)
            and ((row!=r+dr) or (col!=c+dc)))
               return kSuccessful;
         }
   return kUnsuccessful;
}


void Board::move(Color color ,int r, int c) {
   assert(valid_move(color, r, c));
   Color opponent = opponent_of(color);
   int count = 0;
   for (int dr = -1; dr!=2; ++dr)
      for (int dc = -1; dc!=2; ++dc)
         if ((dr!=0) or (dc!=0)) {
            int row = r, col = c;
            do {
               row += dr;
               col += dc;
            } while (b_[row][col]==opponent);
            // If this direction captures something,
            // change the color of the captured pieces:
            if ((b_[row][col]==color)
            and ((row!=r+dr) or (col!=c+dc)))
               for (row = r+dr, col = c+dc;
                    b_[row][col]==opponent;
                    row += dr, col += dc) {
                  b_[row][col] = color;
                  ++count;
               }
         }
   b_[r][c] = color;
   if (color==kBlack) {
      black_score_ += count+1;
      white_score_ -= count;
   } else {
      white_score_ += count+1;
      black_score_ -= count;
   }
}

MoveResult Board::get_possible_move(Color color,
                                    int &r, int &c) const {
   for (r = 1; r!=kNRows+1; ++r)
      for (c = 1; c!=kNCols+1; ++c)
         if (valid_move(color, r, c))
            return kSuccessful;
   return kUnsuccessful;
}


