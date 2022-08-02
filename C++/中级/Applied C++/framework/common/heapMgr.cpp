// heapMgr.cpp
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
//  Simple heap manager to reserve heap memory for low memory conditions


#include "heapMgr.h"
#include "debugstream.h"
#include <iostream>


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// ***************
// *             *
// *  apHeapMgr  *
// *             *
// ***************

apHeapMgr* apHeapMgr::sOnly_ = 0;
apHeapMgr& apHeapMgr::gOnly()
{
  if (!sOnly_) sOnly_ = new apHeapMgr ();
  return *sOnly_;
}

apHeapMgr::apHeapMgr () 
  : oldHandler_ (0), reserve_ (0), size_ (0), state_ (true), nested_ (false)
{}


void apHeapMgr::releaseMemory ()
{
  if (reserve_) {
    delete [] reserve_;
    reserve_ = 0;
    cdebug << "apHeapMgr::releaseMemory() has released " << size_ << " bytes" << std::endl;
    size_ = 0;
  }
}

void apHeapMgr::cleanup ()
{
  releaseMemory ();

  if (oldHandler_) {
    std::set_new_handler (oldHandler_);
    oldHandler_ = 0;
  }
}


int apHeapMgr::allocate (int desiredSize)
{
  cleanup ();

  while (reserve_ == 0 && desiredSize > 0) {
    try {
      reserve_ = new char [desiredSize];
      size_ = desiredSize;
    }
    catch (std::bad_alloc&) {
      desiredSize /= 2;
    }
  }

  // Install our handler
  if (reserve_)
    oldHandler_ = std::set_new_handler (newHandler);

  cdebug << "apHeapMgr::allocate() has reserved " << size_ << " bytes" << std::endl;

  return desiredSize;
}

// newHandler() is called when heap cannot be allocated
void apHeapMgr::newHandler ()
{
  if (apHeapMgr::gOnly().nested_) {
    // We have recursed into our handler which is a catastrophic bug
    // We cannot generate a message because this is how we probably
    // got here in the first place.
    throw std::bad_alloc ();
  }

  apHeapMgr::gOnly().nested_ = true;

  if (apHeapMgr::gOnly().state_) {
    // Free our memory if we have not already done so
    if (apHeapMgr::gOnly().reserve_) {
      apHeapMgr::gOnly().releaseMemory ();
      apHeapMgr::gOnly().nested_ = false;
      return;
    }
  }
 
  cdebug << "Throwing bad_alloc from newHandler" << std::endl;
  apHeapMgr::gOnly().nested_ = false;
  throw std::bad_alloc ();
}


