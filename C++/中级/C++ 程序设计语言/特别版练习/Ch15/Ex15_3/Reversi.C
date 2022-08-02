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

#include "BoardTextViewer.H"
#include "Game.H"
#include "HumanTextPlayer.H"
#include "VirtualTextPlayer.H"
#include <iostream>

#if !defined(NOSTD)
using std::cout;
using std::cin;
#endif

Player* select_player(Color color) {
   cout << (color==kWhite? "White: ": "Black: ")
        << "[H]uman or [C]omputer? ";
   char answer;
   cin >> answer;
   if (answer=='h' || answer=='H')
      return new HumanTextPlayer(cout, cin, color);
   else
      return new VirtualTextPlayer(cout, color);
}

int main() {
   Game game(select_player(kBlack), select_player(kWhite));
   game.select_viewer(new BoardTextViewer(cout));
   game.play();
   return 0;
}

