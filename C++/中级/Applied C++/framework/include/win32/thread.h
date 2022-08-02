#ifndef _win32_thread_h_
#define _win32_thread_h_

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
//  win32 thread wrapper.

#ifndef WIN32
#error This version of apThread is only valid on win32 platforms
#endif


// We want this to be compatible with MFC and non-MFC apps
#ifdef _AFXDLL
#include <afx.h>
#else
#include <windows.h>
#endif

#include <process.h>    // _beginthread(), _endthread()


#include <iostream>

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
  apThread  () : threadid_ (-1) {}
  ~apThread () {if (threadid_ != -1) stop();}

  int threadid () const { return threadid_;}

  bool start () 
  {
    threadid_ = _beginthreadex (0, 0, thread_, this,
                                CREATE_SUSPENDED, (unsigned int*) &threadid_);
    if (threadid_ != 0)
      ResumeThread ((HANDLE)threadid_);
    return (threadid_ != 0);
  }
  // Start the thread running

  bool stop  () 
  {
    TerminateThread ((HANDLE) threadid_, -1);
    return true;
  }
  // Stop the thread. Ungraceful and may result in locking/resource problems.

  bool wait (unsigned int seconds = 0)
  {
    DWORD wait = seconds * 1000;
    if (wait == 0) wait = INFINITE;
    DWORD status = WaitForSingleObject ((HANDLE) threadid_, wait);
    return (status != WAIT_TIMEOUT);
  }
  // Wait for thread to complete

  void sleep (unsigned int msec) { Sleep (msec);}
  // Sleep for the specified amount of time.

protected:
  int threadid_;

  static unsigned int __stdcall thread_ (void* obj)
  {
    // Call the overriden thread function
    apThread* t = reinterpret_cast<apThread*>(obj);
    t->thread ();
    return 0;
  }

  virtual void thread () {
    _endthreadex (0);
    CloseHandle ((HANDLE) threadid_);
  }
  // Thread function, Override this in derived classes.
};



#endif // _win32_thread_h_
