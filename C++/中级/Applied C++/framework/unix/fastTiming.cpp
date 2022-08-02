// fasttiming.cpp
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
// Versions for unix or other systems that support gettimeofday()

#include "unix/fastTiming.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// ************************
// *                      *
// *  apHiResElapsedTime  *
// *                      *
// ************************

apHiResElapsedTime::apHiResElapsedTime () : starting_ (0)
{
  reset ();
}


double apHiResElapsedTime::usec () const
{
  return sec() * 1000000.;
}

double apHiResElapsedTime::msec () const
{
  return sec() * 1000;
}

double apHiResElapsedTime::sec () const
{
  struct timeval t;
  gettimeofday (&t, 0);

  double now = 1.e-6 * t.tv_usec + t.tv_sec;

  return (now - starting_);
}


void apHiResElapsedTime::reset ()
{
  struct timeval t;
  gettimeofday (&t, 0);

  starting_ = 1.e-6 * t.tv_usec + t.tv_sec;
}
