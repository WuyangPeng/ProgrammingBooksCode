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
#include "VirtualPlayer.H"
#include "VirtualTextPlayer.H"

namespace { // unnamed namespace
   void print_color(std::ostream &output, Color color) {
      if (color==kBlack)
         output << "Black";
      else
         output << "White";
   }
} // end unnamed namespace

void VirtualTextPlayer::get_move(Board const &board,
                                 int &row, int &col) {
   VirtualPlayer machine(color_);
   machine.get_move(board, row, col);
   print_color(output_, color_);
   output_ << " plays ["
           << char('a'+row-1) << char('1'+col-1) << "]\n";
}

void VirtualTextPlayer::skip_move(Board const&) {
   print_color(output_, color_);
   output_ << ": no valid move possible.\n";
}

void VirtualTextPlayer::win() {
   print_color(output_, color_);
   output_ << " wins!\n";
}

void VirtualTextPlayer::tie() {
   if (color_==kBlack)
      output_ << "Game tied.\n";
   else
      output_ << "No winner!\n";
}

