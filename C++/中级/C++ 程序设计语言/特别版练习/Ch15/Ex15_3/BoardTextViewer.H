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

#ifndef BOARDTEXTVIEWER_H
#define BOARDTEXTVIEWER_H

#include "BoardViewer.H"
#include <iostream>

#if !defined(NOSTD)
using std::ostream;
#endif


struct BoardTextViewer: BoardViewer {
   BoardTextViewer(ostream &output): output_(output) {}
   virtual ~BoardTextViewer() {}
   virtual void draw(Board&);
private:
   ostream &output_;
};
#endif

