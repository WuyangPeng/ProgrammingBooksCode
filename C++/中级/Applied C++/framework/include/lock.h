#ifndef _lock_h_
#define _lock_h_

// lock.h
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
//  Thread synchronization routines, or null objects for
//  platforms that do not support (or do not need) this
//  functionality.



// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345

// Decide which implementation to use
// Defining AP_NOTHREADS will use the default implementation in
// applications where threading isn't an issue.

#if !defined(AP_NOTHREADS) && defined(WIN32)
#include <win32/lock.h>
#elif !defined(AP_NOTHREADS) && defined(HasPTHREADS)
#include <unix/lock.h>
#else


// ************
// *          *
// *  apLock  *
// *          *
// ************
//
// apLock is a simple wrapper around a synchronization object
// that only allows a single thread access to a resource at a
// time. The default version does nothing and is suitable for
// platforms that do not support threading, or applications that
// do not need it.

class apLock
{
public:
  apLock  ()     {}
  ~apLock ()     {}

  bool lock   () { return true;}     // Get the lock
  bool unlock () { return true;}     // Release the lock
};

#endif



// **************
// *            *
// *  apLocker  *
// *            *
// **************
//
// apLocker is a generic version of RAII (resource acquisition is
// initialization).
//
//   1) Create a global lock that you will use for your resource
//         ex:  apLock coutLock;
//   2) Use an instance of apLocker to manage this resource
//         ex:
//         {
//           apLocker lock(coutLock);
//           std::cout << "Locked access to std::cout" << std::endl;
//         }

class apLocker
{
public:
  apLocker (apLock& lock) : lock_ (lock)  { lock_.lock();}
  ~apLocker () { lock_.unlock();}

private:
  apLock& lock_;

  // Prohibit copy and assignment
  apLocker            (const apLocker& src);
  apLocker& operator= (const apLocker& src);
};



#endif // _lock_h_
