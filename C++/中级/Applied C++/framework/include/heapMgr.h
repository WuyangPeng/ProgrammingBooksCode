#ifndef _heapMgr_h_
#define _heapMgr_h_

// heapMgr.h
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
// Simple heap manager to reserve heap memory for low memory conditions



// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345

#include <new>


// ***************
// *             *
// *  apHeapMgr  *
// *             *
// ***************
//
// apHeapMgr will initially allocate a block of memory to keep
// in reserve. The size of this block is application dependent
// and should be sized such that the memory is sufficient to
// perform critical duties.
//
// In addition to being activated when new fails to allocate
// memory, it can be manually called to release its memory.

class apHeapMgr
{
public:
  static apHeapMgr& gOnly ();

  int  allocate (int desiredSize);
  void release  () { cleanup();}
  // Allocate or release the heap memory. This can be done
  // manually or in response to a low memory condition.
  // allocate() returns the number of bytes reserved

  void automatic (bool state) { state_ = state;}
  // When set to true (the default), a low memory condition
  // will automatically release any reserved memory.

private:
  static void newHandler ();
  // Our memory handler when new cannot allocate the desired memory

  static apHeapMgr* sOnly_;

  apHeapMgr ();

  void releaseMemory (); // Release reserve memory
  void cleanup ();       // Release our reserve and unhook our handler

  new_handler oldHandler_; // Previous handler
  bool        state_;      // true if we will automatically release memory
  bool        nested_;     // Detects if newHandler() is nested
  int         size_;       // Amount of memory (bytes) in reserve
  char*       reserve_;    // Reserve memory we keep
};


#endif // _heapMgr_h_
