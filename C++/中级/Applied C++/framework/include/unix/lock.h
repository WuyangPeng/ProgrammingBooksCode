#ifndef _unix_lock_h_
#define _unix_lock_h_

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
//  Unix mutex wrapper.

#ifndef HasPTHREADS
#error This version of apLock is only valid on unix platforms with pthreads
#endif


#include <pthread.h>


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// **********************
// *                    *
// *  apMutexAttribute  *
// *                    *
// **********************

// Our version of apLock resuses the same pthread_mutexattr_t object
// each time. This object initializes it. The value() method returns
// a pointer that you can pass to pthread_mutex_init

class apMutexAttribute
{
public:
  static apMutexAttribute& gOnly ();

  pthread_mutexattr_t* value () { return &attr_;}

private:
  static apMutexAttribute* sOnly_;

  pthread_mutexattr_t attr_;

  apMutexAttribute ();
  ~apMutexAttribute ();
};




// ************
// *          *
// *  apLock  *
// *          *
// ************

class apLock
{
public:
  apLock  ()     
  {
    pthread_mutex_init (&lock_, apMutexAttribute::gOnly().value());
  }
  ~apLock ()     { pthread_mutex_destroy (&lock_);}

  apLock (const apLock&) 
  {
    pthread_mutex_init (&lock_, apMutexAttribute::gOnly().value());
  }

  apLock& operator= (const apLock&) { return *this;}


  // Get the lock
  bool lock () const 
  { return pthread_mutex_lock (&lock_) == 0;}

  // Release the lock
  bool unlock () const 
  { return pthread_mutex_unlock (&lock_) == 0;}

private:
  mutable pthread_mutex_t lock_;
};


#endif // _unix_lock_h_
