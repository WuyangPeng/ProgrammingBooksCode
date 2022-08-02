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


#include "image/imageStorage.h"
#include "image/../exception.h"



// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


// ************************
// *                      *
// *  apImageStorageBase  *
// *                      *
// ************************

apImageStorageBase::apImageStorageBase ()
{}

apImageStorageBase::apImageStorageBase (const apRect& boundary)
: boundary_ (boundary)
{}

apImageStorageBase::~apImageStorageBase ()
{}



// ************************
// *                      *
// *  apRectImageStorage  *
// *                      *
// ************************

apRectImageStorage::apRectImageStorage () : begin_ (0), end_ (0),
xoffset_ (0), yoffset_ (0), bytesPerPixel_ (0), rowSpacing_ (0),
align_ (eNoAlign)
{}

apRectImageStorage::apRectImageStorage (const apRect& boundary,
                                        unsigned int bytesPerPixel,
                                        eAlignment align)
: apImageStorageBase (boundary), begin_ (0), end_ (0), 
  xoffset_ (0), yoffset_ (0), bytesPerPixel_ (bytesPerPixel), 
  rowSpacing_ (0), align_ (align)
{
  // Round up our row size for alignment purposes. The
  // enumeration values match our alignment values so we can 
  // cast it and do some bit manipulation.
  rowSpacing_ = width () * bytesPerPixel_;
  if (align_ != eNoAlign) {
    int alignment = static_cast<int>(align_) - 1;
    rowSpacing_ = (rowSpacing_ + alignment) & (~alignment);
  }

  // Allocate our memory. Force our base address to start at a
  // 8-byte aligned boundary.
  storage_ = apAlloc<Pel8> (rowSpacing_ * boundary.height (), 8);
  begin_ = rowAddress_ (y0());
  end_   = begin_ + height() * rowSpacing_;
}

apRectImageStorage::~apRectImageStorage ()
{}


apRectImageStorage::apRectImageStorage 
(const apRectImageStorage& src) : apImageStorageBase (src)
{
  // We only need to hold on to the local locks
  apRectImageStorageLocker srcLocking (src); 

  // Copy our base data again because we now have a lock
  boundary_      = src.boundary_;

  storage_       = src.storage_;
  begin_         = src.begin_;
  end_           = src.end_;
  align_         = src.align_;
  yoffset_       = src.yoffset_;
  xoffset_       = src.xoffset_;
  bytesPerPixel_ = src.bytesPerPixel_;
  rowSpacing_    = src.rowSpacing_;
}

apRectImageStorage& apRectImageStorage::operator= 
  (const apRectImageStorage& src)
{
  // We only need to hold on to the local locks
  apRectImageStorageLocker locking (*this);

  if (this != &src) {
    apRectImageStorageLocker srcLocking (src); 
    // Don't forget our base class
    boundary_      = src.boundary_;

    storage_       = src.storage_;
    begin_         = src.begin_;
    end_           = src.end_;
    align_         = src.align_;
    yoffset_       = src.yoffset_;
    xoffset_       = src.xoffset_;
    bytesPerPixel_ = src.bytesPerPixel_;
    rowSpacing_    = src.rowSpacing_;
  }

  return *this;
}


bool apRectImageStorage::window (const apRect& window)
{
  apRectImageStorageLocker locking (*this);

  apRect intersect = boundary().intersect (window);
  if (intersect.isNull()) {
    // No intersection so make this a null image
    init ();
    return false;
  }

  // Adjust our boundary and compute the new offset to our
  // first pixel.
  xoffset_  += intersect.x0() - x0();
  yoffset_  += intersect.y0() - y0();
  boundary_  = intersect;
  begin_     = rowAddress_ (y0());
  end_       = begin_ + height() * rowSpacing_;

  return true;
}



void apRectImageStorage::init ()
{
  boundary_      = apRect ();
  xoffset_       = 0;
  yoffset_       = 0;
  bytesPerPixel_ = 0;
  rowSpacing_    = 0;
  storage_       = apAlloc<Pel8>();
  begin_         = 0;
  end_           = 0;
}


Pel8* apRectImageStorage::rowAddress_ (int y)
{
  if (y < y0() || y >= y1())
    throw apBoundsException ("apRectImageStorage::rowAddress_");

  y -= y0();
  int offset = (y + yoffset_) * rowSpacing_ 
                + xoffset_ * bytesPerPixel_;
  Pel8* p = storage_.data() + offset;
  return p;
}

// This is better than duplicating code
const Pel8* apRectImageStorage::rowAddress_ (int y) const
{
  return const_cast<apRectImageStorage*> (this)->rowAddress_ (y);
}

Pel8* apRectImageStorage::getAddr (int x, int y)
{ 
  if (x < x0() || x >= x1())
    throw apBoundsException ("apRectImageStorage::getAddr");
  return rowAddress_ (y) + (x-x0()) * bytesPerPixel_;
}

const Pel8* apRectImageStorage::getAddr (int x, int y) const
{
  return const_cast<apRectImageStorage*> (this)->getAddr (x, y);
}


const Pel8* apRectImageStorage::getPixel (int x, int y) const
{
  return getAddr (x, y);
}

void apRectImageStorage::setPixel (int x, int y, 
                                   const Pel8* pixel)
{
  Pel8* addr = getAddr (x, y);
  memcpy (addr, pixel, bytesPerPixel_);
}


void apRectImageStorage::rebase ()
{
  // Make sure we have our own copy if we are sharing the buffer
  storage_.duplicate ();

  // Change the origin point
  boundary_ = apRect (0, 0, width(), height());
  begin_    = rowAddress_ (y0());
  end_      = begin_ + height() * rowSpacing_;
}

