// imageStorage.cpp
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
// Image class storage

#include "imageStorage.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// ********************
// *                  *
// *  apImageStorage  *
// *                  *
// ********************

apImageStorage::apImageStorage ()
{
//  storage_ = gNull().storage_;
  storage_ = apStorageRep::gNull ();
  storage_->addRef ();
}


apImageStorage::apImageStorage (apStorageRep* rep)
: storage_ (rep)
{
  storage_->addRef ();
}

apImageStorage::~apImageStorage () 
{ 
  storage_->subRef ();
}


apImageStorage::apImageStorage (const apImageStorage& src)
{
  storage_ = src.storage_;
  storage_->addRef ();
}

apImageStorage& 
apImageStorage::operator= (const apImageStorage& src)
{
  // Make sure we don't copy ourself!
  if (storage_ == src.storage_) return *this;

  storage_->subRef ();  // Remove reference from existing object
  storage_ = src.storage_;
  storage_->addRef ();  // Add reference to our new object

  return *this;
}



// ******************
// *                *
// *  apStorageRep  *
// *                *
// ******************

apStorageRep* apStorageRep::sNull_ = 0;

apStorageRep* apStorageRep::gNull ()
{
  if (!sNull_) {
    sNull_ = new apStorageRep ();
    sNull_->addRef (); // We never want this to become 0
  }

  return sNull_;
}


apStorageRep::apStorageRep ()
: width_ (0), height_ (0), bytesPerPixel_ (0), ref_ (0)
{
  // Don't allow a zero byte allocation
  storage_ = apAlloc<unsigned char> (1);
}

apStorageRep::apStorageRep (unsigned int width, unsigned int height, 
                            unsigned int bytesPerPixel)
: width_ (width), height_ (height), 
  bytesPerPixel_ (bytesPerPixel), ref_ (0)
{
  // Compute allocation size and don't let it be zero
  unsigned int allocation = width_ * height_ * bytesPerPixel_;
  if (allocation == 0) allocation = 1;

  storage_ = apAlloc<unsigned char> (allocation);
}

apStorageRep::~apStorageRep ()
{}

