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

#include "BoardViewer.H"
#include "Game.H"
#include "Player.H"

void Game::play() {
   bool more_moves;
   viewer_->draw(board_);
   do {
      int r, c;
      more_moves = false;
      if (board_.get_possible_move(kBlack, r, c)) {
         more_moves = true;
         black_->get_move(board_, r, c);
         board_.move(kBlack, r, c);
         viewer_->draw(board_);
      } else
         black_->skip_move(board_);
      if (board_.get_possible_move(kWhite, r, c)) {
         more_moves = true;
         white_->get_move(board_, r, c);
         board_.move(kWhite, r, c);
         viewer_->draw(board_);
      } else
         white_->skip_move(board_);
   } while (more_moves);
   if (board_.score(kWhite)>board_.score(kBlack)) {
      white_->win(); black_->lose();
   } else
   if (board_.score(kBlack)>board_.score(kWhite)) {
      black_->win(); white_->lose();
   } else {
      black_->tie(); white_->tie();
   }
}

