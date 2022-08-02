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

#include "geometry.h"
#include "exception.h"
#include "allocTmpl.h"
#include "lock.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


// ************************
// *                      *
// *  apImageStorageBase  *
// *                      *
// ************************
//
// apImageStorageBase is the base class for all image storage. 
// The base object knows little more than the boundary, the
// enclosing rectangle, which represents the image. The
// actual image storage is left to derived classes.

class apImageStorageBase
{
public:
  apImageStorageBase ();
  apImageStorageBase (const apRect& boundary);

  virtual ~apImageStorageBase ();

  const apRect& boundary () const { return boundary_;}

  int  x0             () const { return boundary_.x0();}
  int  y0             () const { return boundary_.y0();}
  int  x1             () const { return boundary_.x1();}
  int  y1             () const { return boundary_.y1();}
  unsigned int width  () const { return boundary_.width();}
  unsigned int height () const { return boundary_.height();}

  // Default copy constructor and assignment operators ok.
protected:
  apRect boundary_;
};



// ************************
// *                      *
// *  apRectImageStorage  *
// *                      *
// ************************
//
// apRectImageStorage is an intermediate class for all image
// storage objects which allocate a rectangular block of memory.
// This is the most common storage class.  Memory is allocated
// as a number of Bytes (i.e. unsigned char) and later cast to 
// the appropriate type.
//
// Memory is aligned at specific boundaries for each row in the
// image. This allows image processing functions, especially 
// those written for a specific platform, to take advantage of
// this alignment.

class apRectImageStorage : public apImageStorageBase
{
public:
  enum eAlignment {eNoAlign=0, eWordAlign=2, eDoubleWordAlign=4, eQuadWordAlign=8,
                   e2ByteAlign=2, e4ByteAlign=4, e8ByteAlign=8, e16ByteAlign=16};
  // Memory alignment for each row in the image

  apRectImageStorage ();
  apRectImageStorage (const apRect& boundary, unsigned int bytesPerPixel,
                      eAlignment align);

  apRectImageStorage            (const apRectImageStorage& src);
  apRectImageStorage& operator= (const apRectImageStorage& src);
  // We need our own copy constructor and assignment operator.

  virtual ~apRectImageStorage ();

  bool isNull () const { return storage_.isNull();}
  // Returns true if this is a null image.

  int ref () const { return storage_.ref();}
  // Returns reference count for our storage object (for testing)

  bool lockState     () const { return lock_.lock();}
  bool unlockState   () const { return lock_.unlock();}
  // Lock/unlock our image state, but not the storage

  bool lockStorage   () const { return storage_.lockStorage ();}
  bool unlockStorage () const { return storage_.unlockStorage ();}
  // Lock/unlock our image storage

  bool lock   () const { return lockState() && lockStorage();}
  bool unlock () const { return unlockState() && unlockStorage();}
  // Lock/unlock our image state and storage

  int xoffset       () const { return xoffset_;}
  int yoffset       () const { return yoffset_;}
  int bytesPerPixel () const { return bytesPerPixel_;}
  int rowSpacing    () const { return rowSpacing_;}

  eAlignment alignment () const { return align_;}

  bool operator== (const apRectImageStorage& src) const
  { return storage_.data() == src.storage_.data();}
  bool operator!= (const apRectImageStorage& src) const
  { return storage_.data() != src.storage_.data();}
  // These objects are equal if they share the same underlying memory

  bool window (const apRect& window);
  // Intersect the window with our image to adjust its size. The
  // underlying pixel data is left unchanged.

  const Pel8* rowAddress_ (int y) const;
  Pel8*       rowAddress_ (int y);
  // Returns a pointer to the first pixel in the specified row
  // Throws apBoundsException it the argument is not in range

  const Pel8* getAddr (int x, int y) const;
  Pel8*       getAddr (int x, int y);
  // Returns a pointer to specified pixel.
  // Throws apBoundsException it the argument is not in range

  void rebase ();
  // Sets the image origin to (0,0) and copies the underlying storage if it
  // is shared by anyone. This function can simply multi-step operations because
  // image coordinates are easier to manipulate.

protected:

  const Pel8* getPixel (int x, int y) const;
  void        setPixel (int x, int y, const Pel8* pixel);
  // Get/set a single pixel
  // Throws apBoundsException it the argument is not in range

  void init ();
  // re-init the object as a null image

  mutable apLock lock_;          // Access control
  apAlloc<Pel8>  storage_;       // Pixel storage
  Pel8*          begin_;         // Pointer to first row
  Pel8*          end_;           // Pointer past last row
  eAlignment     align_;         // Alignment
  unsigned int   yoffset_;       // Row offset to first row
  unsigned int   xoffset_;       // Pixel offset in first row
  unsigned int   bytesPerPixel_; // Bytes per pixel
  unsigned int   rowSpacing_;    // Number of bytes between rows
};



// ******************************
// *                            *
// *  apRectImageStorageLocker  *
// *                            *
// ******************************
//
// Locking is an important issue in multi-threaded designs. This
// object will lock/unlock an apRectImageStorage object. Using a 
// temporary instance of apRectImageLocker means that the object
// is unlocked should an exception ever be thrown.

class apRectImageStorageLocker
{
public:
  apRectImageStorageLocker (const apRectImageStorage& image) : image_ (image) { image_.lockState();}
  ~apRectImageStorageLocker () { image_.unlockState();}
private:
  const apRectImageStorage& image_;

  // No copy or assignment is allowed
  apRectImageStorageLocker (const apRectImageStorageLocker&);
  apRectImageStorageLocker& operator= (const apRectImageStorageLocker&);
};



#endif // _imageStorage_h_
