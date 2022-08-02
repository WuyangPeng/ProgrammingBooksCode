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

#include "VirtualPlayer.H"
#include <limits>

void VirtualPlayer::get_move(Board const &board,
                             int &row, int &col) {
   int best = std::numeric_limits<int>::min(),
       worst = std::numeric_limits<int>::max();
   row = col = 0;
   for (int r = 1; r!=Board::kNRows+1; ++r)
      for (int c = 1; c!=Board::kNCols+1; ++c)
         if (board.valid_move(color_, r, c)) {
            int score = eval_self(board, r, c,
                                  best, worst, 1);
            if (score>=best) {
               best = score;
               row = r; col = c;
            }
         }
}

int VirtualPlayer::eval_self(Board const &board,
                             int row, int col,
                             int best, int worst, int d) {
   if (d==maxdepth_) // Maximum depth of exploration?
      return value_of(board);
   Board copy(board);
   if (row>0)
      copy.move(color_, row, col);
   bool move_result = kUnsuccessful;
   for (int r = 1; r!=Board::kNRows+1; ++r)
      for (int c = 1; c!=Board::kNCols+1; ++c)
         if (copy.valid_move(opponent_of(color_), r, c)) {
            move_result = kSuccessful;
            int score = eval_opponent(copy, r, c,
                                      best, worst, d+1);
            if (score<=best) // This won't get any better:
               return score; // "prune" this branch now.
            if (score<worst)
               worst = score;
         }
   if (move_result==kSuccessful)
      return worst;
   else // The opponent had no valid response
      if (copy.get_possible_move(color_, row, col)
               ==kSuccessful)
         return eval_opponent(copy, 0, 0, best, worst, d+1);
      else // We reached an end-of-game situation
         return eval_end_of_game(copy);
}


int VirtualPlayer::eval_opponent(Board const &board,
                                 int row, int col,
                                 int best, int worst, int d)
{
   if (d==maxdepth_) // Maximum depth of exploration reached?
      return value_of(board);
   Board copy(board);
   if (row>0) // Row==0 when we have no valid move
      copy.move(opponent_of(color_), row, col);
   bool move_result = kUnsuccessful;
   // Explore own possible responses:
   for (int r = 1; r!=Board::kNRows+1; ++r)
      for (int c = 1; c!=Board::kNCols+1; ++c)
         if (copy.valid_move(color_, r, c)) {
            move_result = kSuccessful;
            int score = eval_self(copy, r, c,
                                  best, worst, d+1);
            if (score>=worst) // This won't get any better:
               return score;  // "prune" this branch now.
            if (score>best)
               best = score;
         }
   if (move_result==kSuccessful)
      return best;
   else // We have no valid response
      if (copy.get_possible_move(opponent_of(color_),
                                 row, col)==kSuccessful)
         return eval_self(copy, 0, 0, best, worst, d+1);
      else // We reached an end-of-game situation
         return eval_end_of_game(copy);
}


int VirtualPlayer::eval_end_of_game(Board const &board) {
   if (board.score(color_)
          >board.score(opponent_of(color_)))
      return std::numeric_limits<int>::max()-1;
   if (board.score(color_)
          >board.score(opponent_of(color_)))
      return std::numeric_limits<int>::min()+1;
   else
      return 0; // The value of a tie could be biased
}               // if desired.

namespace { // unnamed namespace
   int corner_value(Color player, Color corner,
                    Color p1, Color p2, Color p3) {
      Color opp = opponent_of(player);
      if (corner==player)
         return 30;
      if (corner==opp)
         return -30;
      int value = 0;
      if ((p1==player) || (p2==player) || (p3==player))
         value -= 30;
      if ((p1==opp) || (p2==opp) || (p3==opp))
         value += 30;
      return value;
   }
} // end unnamed namespace

int VirtualPlayer::value_of(Board const &s) {
   Color opponent = opponent_of(color_);
   // First component: material advantage
   int value = s.score(color_)-s.score(opponent);
   // Second component: corner positions
   int t = 1, l = 1, r = Board::kNCols, b = Board::kNRows;
   value += corner_value(color_, s(t, l),
                         s(t+1, l), s(t, l+1), s(t+1, l+1));
   value += corner_value(color_, s(t, r),
                         s(t+1, r), s(t, r-1), s(t+1, r-1));
   value += corner_value(color_, s(b, r),
                         s(b-1, r), s(b, r-1), s(b-1, r-1));
   value += corner_value(color_, s(b, l),
                         s(b-1, l), s(b, l+1), s(b-1, l+1));
   return value;
}

