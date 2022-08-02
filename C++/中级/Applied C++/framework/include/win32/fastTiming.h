#ifndef _win32_fasttiming_h_
#define _win32_fasttiming_h_

// fasttiming.h
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


#ifndef WIN32
#error This version of fasttiming is only valid on win32 platforms
#endif


#ifndef LONGLONG
typedef __int64 LONGLONG;
#endif

#include <time.h>   // For time()


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// ************************
// *                      *
// *  apHiResElapsedTime  *
// *                      *
// ************************

// High-resolution Simple elapsed time class

class apHiResElapsedTime
{
public:
  apHiResElapsedTime ();
  // Record the current time

  double usec () const;
  // Return elapsed time, in microseconds.

  double msec () const;
  // Return elapsed time, in milliseconds.

  double sec () const;
  // Return elapsed time, in seconds

  void reset ();
  // Reset the current time

private:
  LONGLONG starting_;     // Starting time
};



#endif  // _win32_fasttiming_h_
