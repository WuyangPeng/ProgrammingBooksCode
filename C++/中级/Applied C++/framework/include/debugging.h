#ifndef _debugging_h_
#define _debugging_h_

// debugging.h
//
// Copyright (c) 2003 Philip Romanik, Amy Muntz
//
// Permission to use, copy, modify, distribute, and sell this software and
// its documentation for any purpose is hereby granted without fee, provided
// that (i) the above copyright notices and this permission notice appear in
// all copies of the software and related documentation, and (ii) the names
// of Philip Romanik and Amy Muntz may not be used in any advertising or
// publicity relating to the software without the specific, prior written
// permission of Philip Romanik and Amy Muntz.
//
// Use of this software and/or its documentation will be deemed to be
// acceptance of these terms.
//
// THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
// EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
// WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
//
// IN NO EVENT SHALL PHILIP ROMANIK OR AMY MUNTZ BE LIABLE FOR
// ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
// OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
// WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
// LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
// OF THIS SOFTWARE.
//
//
// Debugging related classes


#include <bitset>


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


// *************
// *           *
// *  apDebug  *
// *           *
// *************

// DEBUGGING(level,statement) is used to define one or more c++
// statements to run when the current debugging level is >= the
// specified level. You can generate production releases with this
// code enabled, or you can #define NODEBUG to compile-out the code.
//
// For single line statements you might try this:
//   DEBUGGING(1, cdebug << "Hello World" << std::endl;)
//
// For longer statements, this looks more natrual:
//   DEBUGGING(1, {
//     for (int i=0; i<10; i++)
//       cdebug << "Hello World" << std::endl;
//   })
//

#ifdef NODEBUG
#define DEBUGGING(level,statements)
#else
#define DEBUGGING(level,statements)        \
  if (apDebug::gOnly().isDebug(level)) {   \
    statements                             \
  }
#endif


#if 0 // Version of apDebug that uses values to control debugging

class apDebug
{
public:
  static apDebug& gOnly ();

  int  debug   ()      { return debug_;}
  int  debug   (int d) { int cur = debug_; debug_ = d; return cur;}
  // Get/set the global debugging level

  bool isDebug (int level) { return debug_ >= level;}
  // Returns true if this level is enabled for debugging.

private:
  static apDebug* sOnly_;
  int debug_;

  apDebug ();
};

#endif


// This version uses bit settings, but no error checking is used
class apDebug
{
public:
  static apDebug& gOnly ();

  bool  debug   (int pos) { return debug_.test (pos);}
  bool  debug   (int pos, bool value) 
  { bool cur = debug_.test (pos); 
    if (value)
      debug_.set (pos);
    else
      debug_.reset (pos);
    return cur;
  }
  // Get/set the global debugging level

  bool set   (int pos) { bool cur = debug_.test (pos); debug_.set (pos); return cur;}
  bool clear (int pos) { bool cur = debug_.test (pos); debug_.reset (pos); return cur;}
  // Set/clear a specific bit and return the old state

  void reset () { debug_.reset ();}
  // Turns off all debugging

  bool isDebug (int pos) { return debug_.test (pos);}
  // Returns true if this level is enabled for debugging.

private:
  static apDebug* sOnly_;
  std::bitset<32> debug_;    // 32 is an arbitrary value, you can raise it or lower it

  apDebug ();
};




#endif // _debugging_h_
