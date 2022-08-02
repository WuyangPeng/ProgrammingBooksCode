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
#include "HumanTextPlayer.H"

namespace { // anonymous namespace
   void convert(char &ch, int upper) {
      if (ch>='a' and ch<'a'+upper)
         ch = ch-'a'+1;
      else if (ch>='A' and ch<'A'+upper)
         ch = ch-'A'+1;
      else if (ch>='1' and ch<'1'+upper)
         ch = ch-'1'+1;
   }

   bool in_board(int row, int col) {
      return (row>0) and (row<=Board::kNRows)
         and (col>0) and (col<=Board::kNCols);
   }

   void print_color(ostream &output, Color color) {
      if (color==kBlack)
         output << "Black";
      else
         output << "White";
   }
} // end anonymous namespace

void HumanTextPlayer::get_move(Board const &board,
                               int &r, int &c) {
   char row, col;
   do {
      print_color(output_, color_);
      output_ << ", enter your move (e.g., a7) : ";
      input_ >> row >> col;
      convert(row, Board::kNRows);
      convert(col, Board::kNCols);
      if (in_board(row, col)
      and board.valid_move(color_, row, col))
         break;
      board.get_possible_move(color_, r, c);
      output_ << "Invalid move. Please try again.\n" 
              << char('a'+r-1) << char('1'+c-1)
              << " is a valid example,"
                 " but other moves may be better.\n";
   } while (1);
   r = row; c = col;
}

void HumanTextPlayer::skip_move(Board const&) {
   print_color(output_, color_);
   output_ << ": no valid move possible.\n";
}

void HumanTextPlayer::win() {
   print_color(output_, color_);
   output_ << " wins!\n";
}

void HumanTextPlayer::tie() {
   if (color_==kBlack)
      output_ << "Game tied.\n";
   else
      output_ << "No winner!\n";
}


