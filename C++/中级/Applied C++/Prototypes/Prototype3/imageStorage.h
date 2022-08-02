#ifndef _imageStorage_h_
#define _imageStorage_h_

// imageStorage.h
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

#include "allocTmpl.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// ********************
// *                  *
// *  apImageStorage  *
// *                  *
// ********************
//
// apImageStorage is a handle to a apStorageRep object which
// contains image pixel storage.


class apStorageRep;  // Forward declaration

class apImageStorage
{
public:
  apImageStorage ();
  // Creates a null image storage, suitable for later
  // assignment

  apImageStorage (apStorageRep* rep);
  // Construct an image from a rep instance

  virtual ~apImageStorage ();

  apImageStorage            (const apImageStorage& src);
  apImageStorage& operator= (const apImageStorage& src);
  // We need our own copy constructor and assignment operator.

  const apStorageRep* operator -> () const { return storage_;}
  apStorageRep*       operator -> ()       { return storage_;}
  // Allow access to the rep object

protected:
  apStorageRep* storage_; // The actual image storage
};




// ******************
// *                *
// *  apStorageRep  *
// *                *
// ******************
//
// apStorageRep is the base rep class for image pixel storage.
// Storage is allocated as a number of bytes and this is cast
// to the correct type by derived classes.

class apStorageRep
{
public:
  static apStorageRep* gNull ();
  // Representation of a null image storage.

  apStorageRep ();
  apStorageRep (unsigned int width, unsigned int height, unsigned int bytesPerPixel);
  // Construct an image of the given size and allocation per pixel

  virtual ~apStorageRep ();

  const unsigned char* base () const { return storage_.data();}
  unsigned char*       base ()       { return storage_.data();}
  // Access to base of memory

  unsigned int width         () const { return width_;}
  unsigned int height        () const { return height_;}
  unsigned int bytesPerPixel () const { return bytesPerPixel_;}
  unsigned int ref           () const { return ref_;}

  void addRef () { ref_++;}
  void subRef () { if (--ref_ == 0) delete this;}
  // Increment or decrement the reference count

  // Default copy constructor and assignment operators ok.
protected:
  apAlloc<unsigned char> storage_; // Pixel storage

  unsigned int bytesPerPixel_; // Bytes per pixel
  unsigned int width_;
  unsigned int height_;  
  unsigned int ref_;           // Current reference count

  static apStorageRep* sNull_;
};



#endif // _imageStorage_h_
