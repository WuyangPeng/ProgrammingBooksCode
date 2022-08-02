#ifndef _imageTmpl_h_
#define _imageTmpl_h_

// imageTmpl.h
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
// Image template class


#ifdef WIN32
#pragma warning(disable:4786) // Disable warning regarding long symbol names caused by templates
#pragma warning(disable:4244) // Don't show possible conversion error for op+= and related
#endif

#include "image/imageTypes.h"
#include "image/imageStorageTmpl.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345




// *************
// *           *
// *  apImage  *
// *           *
// *************

// ::set is referenced inside the class so it must be declared.
template<class T, class S> class apImage;
template<class T, class S> void set (apImage<T,S>& image, const T& value);


template<class T, class S=apImageStorage<T> >
class apImage
{
public:
  typedef typename S::row_iterator row_iterator;
  typedef typename S::iterator iterator;

  static apImage sNull;
  // A convient null image which is defined for every type

  apImage () {}
  apImage (const apRect& boundary, 
           apRectImageStorage::eAlignment align = 
           apRectImageStorage::eNoAlign) 
    : storage_ (boundary, align)
  {}

  apImage (S storage) : storage_ (storage) {}
  // Used when we do alignment

  virtual ~apImage () {}

  apImage            (const apImage& src);
  apImage& operator= (const apImage& src);
  // Our own copy constructor and assignment operator.

  template<class T1, class S1>
  apImage& operator= (const apImage<T1,S1>& src)
  {
    // Our copy() function does exactly what we want
    copy (src, *this);
    return *this;
  }
  // Assignment and image type conversion

  template<class T1, class S1>
  apImage (const apImage<T1,S1>& src)
  {
    // Our copy() function does exactly what we want
    copy (src, *this);
  }
  // Copy constructor with image type conversion


  bool lockImage   () const { return storage_.lock ();}
  bool unlockImage () const { return storage_.unlock ();}
  // Lock/unlock our image state (and our storage)

  bool lockState   () const { return storage_.lockState ();}
  bool unlockState () const { return storage_.unlockState ();}
  // Lock/unlock only our image state

  bool isNull      () const { return storage_.isNull();}
  int  ref         () const { return storage_.ref();}
  int xoffset      () const { return storage_.xoffset();}
  int yoffset      () const { return storage_.yoffset();}

  unsigned int bytesPerPixel () const { return storage_.bytesPerPixel();}
  unsigned int rowSpacing    () const { return storage_.rowSpacing();}

  apRectImageStorage::eAlignment alignment () const 
  { return storage_.alignment();}

  S&       storage ()       { return storage_;}
  const S& storage () const { return storage_;}

  const apRect& boundary () const { return storage_.boundary();}
  int           x0       () const { return storage_.x0();}
  int           y0       () const { return storage_.y0();}
  int           x1       () const { return storage_.x1();}
  int           y1       () const { return storage_.y1();}
  unsigned int  width    () const { return storage_.width();}
  unsigned int  height   () const { return storage_.height();}

  const T* base       ()      const  { return rowAddress (y0());}
  T*       base       ()             { return rowAddress (y0());}
  const T* rowAddress (int y) const  { return storage_.rowAddress (y);}
  T*       rowAddress (int y)        { return storage_.rowAddress (y);}

  const T& getPixel (int x, int y) const         { return storage_.getPixel (x, y);}
  const T& getPixel (const apPoint& point) const { return storage_.getPixel (point);}
  void     setPixel (int x, int y, const T& pixel)         { storage_.setPixel (x, y, pixel);}
  void     setPixel (const apPoint& point, const T& pixel) { storage_.setPixel (point, pixel);}
  // Gets or sets the specified pixel. Thread-safe

  void setRow (int y, const T& pixel) { return storage_.setRow (y, pixel);}
  void setCol (int x, const T& pixel) { return storage_.setCol (x, pixel);}
  // Set of row or columns to the specified pixel. Thread-safe

  // iterators
  row_iterator       row_begin ()       { return storage_.row_begin();}
  const row_iterator row_begin () const { return storage_.row_begin();}
  row_iterator       row_end   ()       { return storage_.row_end();}
  const row_iterator row_end   () const { return storage_.row_end();}

  iterator       begin ()       { return storage_.begin();}
  const iterator begin () const { return storage_.begin();}
  iterator       end   ()       { return storage_.end();}
  const iterator end   () const { return storage_.end();}

  // Image memory operations
  bool window (const apRect& window) 
  { return storage_.window (window);}

  void trim ();
  // Duplicate the image data, if it is shared, to use the
  // minimum amount of memory possible. Use this function to
  // duplicate the underlying image data. Thread-safe.

  void rebase ();
  // Calls trim() and then adjust the origin to be (0,0). This is
  // sometimes useful for multi-step algorithms because you don't have
  // to keep track of the origin after each step.

  apRectImageStorage::eAlignment bestAlignment () const;
  // Return best alignment of this image. This is a measured
  // quantity so it will work with all images.

  apImage<T,S> align (apRectImageStorage::eAlignment align = 
                      apRectImageStorage::eNoAlign);
  // Return an image that has the specified alignment. This
  // may return a new image

  apImage<T,S> duplicate (apRectImageStorage::eAlignment align = 
                          apRectImageStorage::eNoAlign) const;
  // Duplicate the image data such that it has the specified alignment.
  // The image data is always duplicated, unlike align()

  // Image operations with constants. Thread-safe
void set (const T& value) { ::set (*this, value);}
  void add (const T& value);
  void sub (const T& value);
  void mul (const T& value);
  void div (const T& value);
  void scale (float scaling);

  // Conditionals
  bool isIdentical (const apImage& src) const;
  // Checks for same boundary and identical image storage only

  bool operator== (const apImage& src) const;
  bool operator!= (const apImage& src) const 
  { return !operator== (src);}

protected:
  S       storage_;  // Image storage
};


// *******************
// *                 *
// *  apImageLocker  *
// *                 *
// *******************
//
// Locking is an important issue in multi-threaded designs. This
// object will lock/unlock an apImage<> object. Using a 
// temporary instance of apImageLocker means that the object
// is unlocked should an exception ever be thrown. By default, full
// locking is employed unless the user specifies that only the state
// must be loacked.
//
// There are some special cases, so this object can be told to unlock
// and lock itself.

template<class T, class S=apImageStorage<T> >
class apImageLocker
{
public:
  apImageLocker (const apImage<T,S>& image, bool fullLocking = true) 
    : image_ (image), fullLocking_ (fullLocking), locked_ (false)
    { lock();}
  ~apImageLocker () { unlock();}

  void lock ()
  {
    if (!locked_)
      fullLocking_ ? image_.lockImage() : image_.lockState();
    locked_ = true;
  }
  void unlock ()
  {
    if (locked_)
      fullLocking_ ? image_.unlockImage() : image_.unlockState();
    locked_ = false;
  }
private:
  bool                fullLocking_;
  bool                locked_;
  const apImage<T,S>& image_;

  // No copy or assignment is allowed
  apImageLocker (const apImageLocker&);
  apImageLocker& operator= (const apImageLocker&);
};




template<class T, class S>
apImage<T,S> apImage<T,S>::sNull;

template<class T, class S>
apImage<T,S>::apImage (const apImage& src)
{
  apImageLocker<T,S> srcLocking (src, false); // Lock state
  storage_ = src.storage_;
}

template<class T, class S>
apImage<T,S>& apImage<T,S>::operator= (const apImage& src)
{
  apImageLocker<T,S> srcLocking (src, false); // Lock state

  // Make sure we don't copy ourself!
  if (storage_ != src.storage_) {
    apImageLocker<T,S> locking (*this, false); // Lock our state
    storage_ = src.storage_;
  }

  return *this;
}



template<class T, class S>
void apImage<T,S>::trim ()
{
  apImageLocker<T,S> srcLocking (*this, false); // Lock state

  if (isNull() || ref() == 1)
    return;

  // Copy our image
  S storage;
  copy (storage_, storage);
  storage_ = storage;
}


template<class T, class S>
void apImage<T,S>::rebase ()
{
  trim ();
  storage_.rebase ();
}



template<class T, class S>
apRectImageStorage::eAlignment apImage<T,S>::bestAlignment () const
{
  if (isNull())
    return apRectImageStorage::eNoAlign;

  lockImage ();
  const T* p1 = rowAddress (y0());
  const T* p2 = p1;
  if (height() > 1)
    p2 = rowAddress (y0()+1);
  unlockImage ();

  uintptr_t addr1 = reinterpret_cast<uintptr_t>(p1);
  uintptr_t addr2 = reinterpret_cast<uintptr_t>(p2);

  if (addr1 % apRectImageStorage::eQuadWordAlign == 0 &&
      addr2 % apRectImageStorage::eQuadWordAlign == 0)
    return apRectImageStorage::eQuadWordAlign;

  else if (addr1 % apRectImageStorage::eDoubleWordAlign == 0 &&
      addr2 % apRectImageStorage::eDoubleWordAlign == 0)
    return apRectImageStorage::eDoubleWordAlign;

  else if (addr1 % apRectImageStorage::eWordAlign == 0 &&
      addr2 % apRectImageStorage::eWordAlign == 0)
    return apRectImageStorage::eWordAlign;

  return apRectImageStorage::eNoAlign;
}



template<class T, class S>
apImage<T,S> apImage<T,S>::align (apRectImageStorage::eAlignment align)
{
  apImageLocker<T,S> locking (*this); // Lock image

  if (isNull() || align == apRectImageStorage::eNoAlign)
    return *this;

  // Check the alignment on two rows as a check. Just because the
  // image was created with the proper alignment, does not mean that
  // a window of this image will be properly aligned.
  const T* p1 = rowAddress (y0());
  const T* p2 = p1;
  if (height() > 1)
    p2 = rowAddress (y0()+1);

  // Verify the alignment on each row
  if (reinterpret_cast<uintptr_t>(p1) % align == 0 &&
      reinterpret_cast<uintptr_t>(p2) % align == 0)
    return *this;

  // We need to duplicate our underlying data.
  apImage<T,S> dup (::duplicate (storage_, align));

  return dup;
}

template<class T, class S>
apImage<T,S> apImage<T,S>::duplicate (apRectImageStorage::eAlignment align) const
{
  apImageLocker<T,S> locking (*this); // Lock image
  apImage<T,S> dup (::duplicate (storage_, align));

  return dup;
}


template<class T, class S>
void set (apImage<T,S>& image, const T& value)
{
  apImageLocker<T,S> srcLocking (image); // Lock image

  typename apImage<T,S>::row_iterator i;
  unsigned int w = image.width ();
  T* p;
  for (i=image.row_begin(); i != image.row_end(); i++) {
    p = i->p;
    for (unsigned int x=0; x<w; x++)
      *p++ = value;
  }
}

template<> void set  (apImage<Pel8>& s,   const Pel8& value);
template<> void set  (apImage<Pel32s>& s, const Pel32s& value);
template<> void set  (apImage<apRGB>& s,  const apRGB& value);




template<class T, class S>
void apImage<T,S>::add (const T& value)
{
  apImageLocker<T,S> locking (*this); // Lock image

  typename apImage<T,S>::row_iterator i;
  unsigned int w = width ();
  T* p;
  for (i=row_begin(); i != row_end(); i++) {
    p = i->p;
    for (unsigned int x=0; x<w; x++)
      *p++ += value;
  }
}

template<class T, class S>
void apImage<T,S>::sub (const T& value)
{
  apImageLocker<T,S> locking (*this); // Lock image

  typename apImage<T,S>::row_iterator i;
  unsigned int w = width ();
  T* p;
  for (i=row_begin(); i != row_end(); i++) {
    p = i->p;
    for (unsigned int x=0; x<w; x++)
      *p++ -= value;
  }
}

template<class T, class S>
void apImage<T,S>::mul (const T& value)
{
  apImageLocker<T,S> locking (*this); // Lock image

  typename apImage<T,S>::row_iterator i;
  unsigned int w = width ();
  T* p;
  for (i=row_begin(); i != row_end(); i++) {
    p = i->p;
    for (unsigned int x=0; x<w; x++)
      *p++ *= value;
  }
}

template<class T, class S>
void apImage<T,S>::div (const T& value)
{
  apImageLocker<T,S> locking (*this); // Lock image

  typename apImage<T,S>::row_iterator i;
  unsigned int w = width ();
  T* p;
  for (i=row_begin(); i != row_end(); i++) {
    p = i->p;
    for (unsigned int x=0; x<w; x++)
      *p++ /= value;
  }
}

template<class T, class S>
void apImage<T,S>::scale (float scaling)
{
  apImageLocker<T,S> locking (*this); // Lock image

  typename apImage<T,S>::row_iterator i;
  unsigned int w = width ();
  T* p;
  for (i=row_begin(); i != row_end(); i++) {
    p = i->p;
    for (unsigned int x=0; x<w; x++)
      *p++ = ::scale<T> (*p, scaling);
  }
}

template<class T, class S>
bool apImage<T,S>::isIdentical (const apImage& src) const
{
  apImageLocker<T,S> locking (*this);
  apImageLocker<T,S> srcLocking (src);

  bool state = true;
  if (boundary() != src.boundary() ||
      base() != src.base())
    state = false;

  return state;
}


template<class T, class S>
bool apImage<T,S>::operator== (const apImage<T,S>& src) const
{
  apImageLocker<T,S> locking (*this);
  apImageLocker<T,S> srcLocking (src);

  if (boundary() != src.boundary())
    return false;

  typename apImage<T,S>::row_iterator i1;
  typename apImage<T,S>::row_iterator i2;
  unsigned int w = width ();
  const T* p1;
  const T* p2;
  for (i1=row_begin(), i2=row_begin(); i1 != row_end(); i1++, i2++) {
    p1 = i1->p;
    p2 = i2->p;
    for (unsigned int x=0; x<w; x++)
      if (*p1++ != *p2++)
        return false;
  }

  return true;
}



#endif // _imageTmpl_h_
