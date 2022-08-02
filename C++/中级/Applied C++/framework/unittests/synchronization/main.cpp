// main.cpp
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
// Unit Test for synchronization

#include "lock.h"
#include "thread.h"

#include "unitTest.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345

class thread1 : public apThread
{
  void thread ();
};

void thread1::thread ()
{
  for (int i=0; i<10; i++) {
    std::cout << i << std::endl;
    sleep (100);
  }
}



UTFUNC(threads)
{
  setDescription ("threads");

  thread1 threadInst1, threadInst2;
  threadInst1.start ();
  threadInst2.start ();

  // We can call WaitForMultipleObjects, but in case this is on
  // unix.
//  HANDLE handles[2];
//  handles[0] = (HANDLE) thread1.threadid ();
//  handles[1] = (HANDLE) thread2.threadid ();
//  WaitForMultipleObjects (2, handles, TRUE, INFINITE);

  threadInst1.wait ();
  threadInst2.wait ();
}


// Chapter 4 (pg 129) comment regarding RAII
class apConsoleLocker
{
public:
  apConsoleLocker () { consoleLock_.lock();}
  ~apConsoleLocker () { consoleLock_.unlock();}

private:
  static apLock consoleLock_;

  // Prohibit copy and assignment
  apConsoleLocker            (const apConsoleLocker& src);
  apConsoleLocker& operator= (const apConsoleLocker& src);
};
apLock apConsoleLocker::consoleLock_;


UTFUNC(consoleLocker)
{
  setDescription ("Console locking");

  {
    apConsoleLocker lock;
    std::cout << "Wow!" << std::endl;
  }

  VERIFY (true);
}


apLock mylock;

UTFUNC(apLocker)
{
  setDescription ("apLocker");

  {
    apLocker lock(mylock);
    std::cout << "Wow!" << std::endl;
  }

  VERIFY (true);
}



// Our main function is trivial
int main()
{
  bool state = apUnitTest::gOnly().run ();
  apUnitTest::gOnly().dumpResults (std::cout);
  return state;
}
