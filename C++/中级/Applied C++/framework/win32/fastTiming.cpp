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



#ifndef WIN32
#error This version of fasttiming is only valid on win32 platforms
#endif


// We want this to be compatible with MFC and non-MFC apps
#ifdef _AFXDLL
#include <afx.h>
#else
#include <windows.h>
#endif


#include "win32/fastTiming.h"


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
  LARGE_INTEGER t, freq;
  QueryPerformanceCounter (&t);
  QueryPerformanceFrequency (&freq);

  return (double(t.QuadPart - starting_)) / freq.QuadPart;
}


void apHiResElapsedTime::reset ()
{
  LARGE_INTEGER t;
  QueryPerformanceCounter (&t);

  starting_ = t.QuadPart;
}
