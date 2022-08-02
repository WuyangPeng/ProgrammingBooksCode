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

#ifndef GAME_H
#define GAME_H

#include "Board.H"

struct BoardViewer;
struct Player;

struct Game {
   Game(Player *black, Player *white)
      : black_(black), white_(white) {}
   void select_viewer(BoardViewer *viewer)
      { viewer_ = viewer; }
   void play();
private:
   Player *black_, *white_;
   Board board_;
   BoardViewer *viewer_;
};
#endif

