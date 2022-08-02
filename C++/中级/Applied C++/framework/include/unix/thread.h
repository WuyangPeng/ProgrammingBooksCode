#ifndef _unix_thread_h_
#define _unix_thread_h_

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
// unix thread wrapper.


#ifndef HasPTHREADS
#error This version of apThread is only valid on unix platforms with pthreads
#endif


#include <pthread.h>
#include <time.h>


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// **************
// *            *
// *  apThread  *
// *            *
// **************

class apThread
{
public:
  apThread  () : threadid_ (0) {}
  ~apThread () {if (threadid_ != 0) stop();}

  int threadid () const { return (int)threadid_;}

  bool start () 
  {
    int status;
    status = pthread_create (&threadid_, 0, thread_, this);
    return (status == 0);
  }
  // Start the thread running

  bool stop  () 
  {
    pthread_cancel (threadid_);
    return true;
  }
  // Stop the thread. Ungraceful and may result in locking/resource problems.

  bool wait (unsigned int seconds = 0)
  {
    // Time is ignored here
    char* rc;
    pthread_join (threadid_, (void**) &rc);
    return true;
  }
  // Wait for thread to complete

  void sleep (unsigned int msec) 
  {
    struct timespec spec, rspec;
    spec.tv_sec = msec / 1000;
    spec.tv_nsec = (msec % 1000) * 1000000;
    nanosleep (&spec, &rspec);
  }
  // Sleep for the specified amount of time.

protected:
  pthread_t threadid_;

  static void* thread_ (void* obj)
  {
    // Call the overriden thread function
    apThread* t = reinterpret_cast<apThread*>(obj);
    t->thread ();
    return 0;
  }

  virtual void thread () {}

  // Thread function, Override this in derived classes.
};



#endif // _unix_thread_h_
