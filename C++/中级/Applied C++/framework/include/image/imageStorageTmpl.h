#ifndef _imageStorageTmpl_h_
#define _imageStorageTmpl_h_

// imageStorageTmpl.h
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
// Image storage template class

#include "image/imageStorage.h"
#include <iterator>
#include <typeinfo>


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345




// *******************
// *                 *
// *  apRowIterator  *
// *                 *
// *******************
//
// iterator class for apImageStorage Forward and reverse
// operations are allowed.


template<class T> class apRowIterator
{
public:
  struct current
  {
    T*  p;      // Pointer to start of row y
    int x;      // x coordinate of start of row
    int y;      // y coordinate of current row
    int bytes;  // Number of bytes to offset to next row
  };

  apRowIterator () 
  { cur_.p = 0; cur_.x = 0; cur_.y = 0; cur_.bytes = 0;}
  apRowIterator (T* p, int bytes, int x, int y) 
  { cur_.p = p; cur_.bytes = bytes; cur_.x = x; cur_.y = y;}

  current*       operator->()       { return &cur_;}
  const current* operator->() const { return &cur_;}
  current&       operator* ()       { return cur_;}
  const current& operator* () const { return cur_;}

  apRowIterator& operator++ ()
  { 
    cur_.p = reinterpret_cast<T*>
      (reinterpret_cast<Pel8*>(cur_.p) + cur_.bytes);
    cur_.y++;
    return *this;
  }
  apRowIterator operator++ (int)
  {
    apRowIterator t = *this;
    cur_.p = reinterpret_cast<T*>
      (reinterpret_cast<Pel8*>(cur_.p) + cur_.bytes);
    cur_.y++;
    return t;
  }

  apRowIterator& operator-- ()
  { 
    cur_.p = reinterpret_cast<T*>
      (reinterpret_cast<Pel8*>(cur_.p) - cur_.bytes);
    cur_.y--;
    return *this;
  }
  apRowIterator operator-- (int)
  {
    apRowIterator t = *this;
    cur_.p = reinterpret_cast<T*>
      (reinterpret_cast<Pel8*>(cur_.p) - cur_.bytes);
    cur_.y--;
    return t;
  }

  apRowIterator& operator+= (int s)
  { 
    cur_.p = reinterpret_cast<T*>
      (reinterpret_cast<Pel8*>(cur_.p) + s*cur_.bytes);
    cur_.y += s;
    return *this;
  }

  apRowIterator& operator-= (int s)
  { 
    cur_.p = reinterpret_cast<T*>
      (reinterpret_cast<Pel8*>(cur_.p) - s*cur_.bytes);
    cur_.y -= s;
    return *this;
  }

  bool operator== (const apRowIterator& i) const
  { return (cur_.p == i.cur_.p);}
  bool operator!= (const apRowIterator& i) const
  { return (cur_.p != i.cur_.p);}

  // Default copy constructor and assignment operators ok.
private:
  current cur_;
};



// *********************
// *                   *
// *  apPixelIterator  *
// *                   *
// *********************
//
// Pixel iterator class for apImageStorage Forward and reverse
// operations are allowed. This iterator is suitable when you want
// to examine all pixels in the image.


template<class T> class apPixelIterator
{
public:
  // Standard iteration typedef's
  typedef std::forward_iterator_tag iterator_category;
  typedef T value_type;
  typedef ptrdiff_t difference_type;
  typedef T* pointer;
  typedef T& reference;

  struct current
  {
    T*  p;      // Current pointer to pixel
    int x, y;   // Current pixel coordinates

    T*  end;    // Pointer past last pixel in current row
    int x0;     // x coordinate of start of row
    int width;  // Width of row
    int bytes;  // Number of bytes to offset to next row
  };

  apPixelIterator () 
  { cur_.p = 0; cur_.x = 0; cur_.y = 0; cur_.end = 0; cur_.x0 = 0; cur_.width = 0; cur_.bytes = 0;}
  apPixelIterator (T* p, int bytes, int x, int y, int width) 
  { 
    cur_.p     = p;
    cur_.x     = x;
    cur_.y     = y;
    cur_.x0    = x;
    cur_.bytes = bytes;
    cur_.width = width;
    cur_.end   = cur_.p + cur_.width;
  }

  T*       operator->()       { return cur_.p;}
  const T* operator->() const { return cur_.p;}
  T&       operator* ()       { return *cur_.p;}
  const T& operator* () const { return *cur_.p;}

  apPixelIterator& operator++ ()
  { 
    cur_.x++;
    cur_.p++;
    if (cur_.p >= cur_.end) {
      // Advance to the next row
      cur_.x = cur_.x0;
      cur_.y++;
      cur_.p = reinterpret_cast<T*>(reinterpret_cast<Pel8*>(cur_.p) + cur_.bytes - cur_.width*sizeof(T));
      cur_.end = cur_.p + cur_.width;
    }
  
    return *this;
  }

  apPixelIterator operator++ (int)
  { 
    apPixelIterator t = *this;

    cur_.x++;
    cur_.p++;
    if (cur_.p >= cur_.end) {
      // Advance to the next row
      cur_.x = cur_.x0;
      cur_.y++;
      cur_.p = reinterpret_cast<T*>(reinterpret_cast<Pel8*>(cur_.p) + cur_.bytes - cur_.width*sizeof(T));
      cur_.end = cur_.p + cur_.width;
    }
  
    return t;
  }

  bool operator== (const apPixelIterator& i) const
  { return (cur_.p == i.cur_.p);}
  bool operator!= (const apPixelIterator& i) const
  { return (cur_.p != i.cur_.p);}

  // Default copy constructor and assignment operators ok.
private:
  current cur_;
};



// ********************
// *                  *
// *  apImageStorage  *
// *                  *
// ********************
//
// apImageStorage are template objects constructed by the user.
// They utilize the capabilities of apRectImageStorage to handle
// memory allocation. Iterators are also added 


template<class T>
class apImageStorage : public apRectImageStorage
{
public:
  typedef apRowIterator<T>   row_iterator;
  typedef apPixelIterator<T> iterator;

  apImageStorage () {}
  apImageStorage (const apRect& boundary, 
                  eAlignment align = eNoAlign) 
  : apRectImageStorage (boundary, sizeof (T), align) {}

  const T* rowAddress (int y) const
  { return reinterpret_cast<const T*> (rowAddress_ (y));}
  T* rowAddress (int y)
  { return reinterpret_cast<T*> (rowAddress_ (y));}
  // Returns a pointer to the first pixel in the specified row
  // Not thread-safe. Clients need to lock storage
  // Throws apBoundsException if the argument is not in range

  const T& getPixel (int x, int y) const;
  const T& getPixel (const apPoint& point) const 
  { return getPixel (point.x(), point.y());}
  void     setPixel (int x, int y, const T& pixel);
  void     setPixel (const apPoint& point, const T& pixel)
  { setPixel (point.x(), point.y(), pixel);}
  // Gets or sets the specified pixel. Thread-safe.
  // Throws apBoundsException it the argument is not in range

  void setRow (int y, const T& pixel);
  void setCol (int x, const T& pixel);
  // Sets the values of an entire row of column to the specified pixel

  virtual ~apImageStorage () {}

  // row iterators. Not thread-safe. Clients need to lock storage
  row_iterator row_begin () 
  { return row_iterator 
      (reinterpret_cast<T*>(begin_), rowSpacing(), x0(), y0());}
  const row_iterator row_begin () const
  { return row_iterator 
      (reinterpret_cast<T*>(begin_), rowSpacing(), x0(), y0());}

  row_iterator row_end () 
  { return row_iterator 
      (reinterpret_cast<T*>(end_), rowSpacing(), x0(), y0());}
  const row_iterator row_end () const
  { return row_iterator 
      (reinterpret_cast<T*>(end_), rowSpacing(), x0(), y0());}

  // pixel iterators. Not thread-safe. Clients need to lock storage
  iterator begin () 
  { return iterator 
      (reinterpret_cast<T*>(begin_), rowSpacing(), x0(), y0(), width());}
  const iterator begin () const
  { return iterator 
      (reinterpret_cast<T*>(begin_), rowSpacing(), x0(), y0(), width());}

  iterator end () 
  { return iterator 
      (reinterpret_cast<T*>(end_), rowSpacing(), x0(), y0(), width());}
  const iterator end () const
  { return iterator 
      (reinterpret_cast<T*>(end_), rowSpacing(), x0(), y0(), width());}
};



// **************************
// *                        *
// *  apImageStorageLocker  *
// *                        *
// **************************
//
// Locking is an important issue in multi-threaded designs. This
// object will lock/unlock an apImageStorage<> object. Using a 
// temporary instance of apImageLocker means that the object
// is unlocked should an exception ever be thrown. The template
// object must have lock() and unlock() methods. We could have
// written a very generic object, but it is easy for users to
// remember to call this because of its name.

template<class T> class apImageStorageLocker
{
public:
  apImageStorageLocker (const apImageStorage<T>& image) : image_ (image) { image_.lock();}
  ~apImageStorageLocker () { image_.unlock();}
private:
  const apImageStorage<T>& image_;

  // No copy or assignment is allowed
  apImageStorageLocker (const apImageStorageLocker&);
  apImageStorageLocker& operator= (const apImageStorageLocker&);
};




template<class T>
const T& apImageStorage<T>::getPixel (int x, int y) const
{ 
  static T pixel;

  apImageStorageLocker<T> locker (*this); // Exception-safe locking

  const Pel8* p = apRectImageStorage::getPixel (x, y);
  memcpy (&pixel, p, sizeof (T));

  return pixel;
}

template<class T>
void apImageStorage<T>::setPixel (int x, int y, const T& pixel)
{ 
  apImageStorageLocker<T> locker (*this); // Exception-safe locking

  const Pel8* p = reinterpret_cast<const Pel8*> (&pixel);
  apRectImageStorage::setPixel (x, y, p);
}

template<class T>
void apImageStorage<T>::setRow (int y, const T& pixel)
{
  apImageStorageLocker<T> locker (*this); // Exception-safe locking

  T* p = rowAddress (y);
  for (unsigned int i=0; i<width(); i++)
    *p++ = pixel;
}

template<class T>
void apImageStorage<T>::setCol (int x, const T& pixel)
{
  apImageStorageLocker<T> locker (*this); // Exception-safe locking

  T* p = reinterpret_cast<T*>(getAddr (x, y0()));
  // A little more complicated because we step vertically
  for (unsigned int i=0; i<height(); i++) {
    *p = pixel;
    p  = reinterpret_cast<T*> (reinterpret_cast<Pel8*>(p) + rowSpacing_);
  }
}



// **************************
// *                        *
// *  non-member functions  *
// *                        *
// **************************


template <class T1, class T2>
void copy (const apImageStorage<T1>& src, apImageStorage<T2>& dst, 
           bool fastCopy = true)
{
  if (src == dst)
    return;

  // Exception-safe locking
  apImageStorageLocker<T1> srcLocker (src);

  if (src.boundary() != dst.boundary())
    dst = apImageStorage<T2> (src.boundary(), src.alignment());

  apImageStorageLocker<T2> dstLocker (dst);

  typename apImageStorage<T1>::row_iterator i1;
  typename apImageStorage<T2>::row_iterator i2;
  unsigned int w = src.width ();
  int bytes = w * src.bytesPerPixel ();

  const T1* p1;
  T2* p2;

  if (typeid(T1) == typeid(T2) && fastCopy) {
    // We're copying like datatypes so use memcpy for speed
    for (i1=src.row_begin(), i2=dst.row_begin(); i1 != src.row_end(); 
         i1++, i2++) {
      p1 = i1->p;
      p2 = i2->p;
      memcpy (p2, p1, bytes);
    }
  }
  else {
    // We have to do a pixel by pixel copy
    for (i1=src.row_begin(), i2=dst.row_begin(); i1 != src.row_end(); 
         i1++, i2++) {
      p1 = i1->p;
      p2 = i2->p;
      for (unsigned int x=0; x<w; x++)
        *p2++ = static_cast<T2>(*p1++);
    }
  }
}


template <class T>
apImageStorage<T> duplicate (const apImageStorage<T>& src, 
                             apRectImageStorage::eAlignment align)
{
  apImageStorage<T> dst (src.boundary(), align);

  copy (src, dst);
  return dst;
}



#endif // _imageStorageTmpl_h_
