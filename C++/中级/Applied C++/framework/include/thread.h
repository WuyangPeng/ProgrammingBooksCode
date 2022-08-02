#ifndef _thread_h_
#define _thread_h_

// thread.h
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
// Threading functionality, or null for platforms that
// do not support (or do not need) this functionality



// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345

// Decide which implementation to use
// Defining AP_NOTHREADS will use the default implementation in
// applications where threading isn't an issue.

#if !defined(AP_NOTHREADS) && defined(WIN32)
#include <win32/thread.h>
#elif !defined(AP_NOTHREADS) && defined(HasPTHREADS)
#include <unix/thread.h>
#else


// **************
// *            *
// *  apThread  *
// *            *
// **************
//
// apThread is a simple wrapper around a threading object to
// start and execute a thread. This default version does nothing and
// is suitable for platforms that do not support threading, or
// applications that do not require it.

class apThread
{
public:
  apThread  ()     {}
  ~apThread ()     {}

  int threadid () const { return 0;}
  // Return thread id

  bool start () { return false;}
  // Start the thread running. return false on error

  bool stop  () { return false;}
  // Stop the thread. Ungraceful and may result in locking/resource problems.

  bool wait (unsigned int seconds = 0) { return false;}
  // Wait for thread to complete. Return true if thread is finished

  void sleep (unsigned int msec) {}
  // Sleep for the specified amount of time.

protected:
  virtual void thread () {}        // Thread function, never returns
};

#endif


#endif // _thread_h_
