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
// Image class prototype #2
//
// Uses apAlloc<> to allocate memory
// Template on two parameters
//   - Pel datatype
//   - Internal Pel computation type(ex. for summing).
// Handle to the current image. apImage is the user-created
// object, and apImageRep is the object that is allocated
// and performs all the work.

#include "allocTmpl.h"



// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


// *************
// *           *
// *  apImage  *
// *           *
// *************
//
// Image class, using templates
//
//   Template type T:  type of each pixel
//   Template type E:  internal type used during pixel operations


// Forward declaration
template<class T, class E> class apImageRep;


template<class T, class E> 
class apImage
{
public:
  friend class apImageRep<T, E>;

  apImage ();
  // Creates a null image, suitable for later assignment

  apImage (unsigned int width, unsigned int height);
  // Creates an image of the specified size

  ~apImage () { image_->subRef ();}

  apImage            (const apImage& src);
  apImage& operator= (const apImage& src);
  // We need our own copy constructor and assignment operator.

  const apImageRep<T, E>* operator -> () const { return image_;}
  apImageRep<T, E>*       operator -> ()       { return image_;}
  // Allow access to the rep object

protected:
  apImage (apImageRep<T, E>* rep);
  // Construct an image from a rep instance

  apImageRep<T, E>* image_; // The actual image data
};



// ****************
// *              *
// *  apImageRep  *
// *              *
// ****************
//
// Image class, using templates

template<class T, class E> 
class apImageRep
{
public:

  static apImageRep* gNull ();
  // Representation of a null image. This actually allocates
  // a 1 element.

  apImageRep () : width_ (0), height_ (0), ref_ (0) {}
  // Creates a null image, suitable for later assignment

  apImageRep (unsigned int width, unsigned int height);
  // Creates an image of the specified size

  ~apImageRep () {}

  unsigned int width  () const { return width_;}
  unsigned int height () const { return height_;}

  const T* pixels () const { return pixels_.data();}
  T*       pixels ()       { return pixels_.data();}
  // Return pointer to start of pixel data
  
  const T& getPixel (unsigned int x, unsigned int y) const;
  void     setPixel (unsigned int x, unsigned int y, const T& pixel);
  // Get/set a single pixel

  // Reference counting related
  unsigned int ref () const { return ref_;}   // Number of references
  void addRef      () { ref_++;}
  void subRef      () { if (--ref_ == 0) delete this;}

  // Image operations (only one for the prototype)
  apImage<T, E> thumbnail (unsigned int reduction) const;

  // Default copy ctor and assignment are ok
protected:
  apAlloc<T>   pixels_; // Pixel data
  unsigned int width_;  // Image dimensions
  unsigned int height_;
  unsigned int ref_;    // Reference count

  static apImageRep* sNull_;   // Our null image object
};




// ********************
// *                  *
// *  apImage inline  *
// *                  *
// ********************

template<class T, class E>
apImage<T,E>::apImage () : image_ (0)
{
  // Point ourself at our null rep
  image_ = apImageRep<T,E>::gNull ();
  image_->addRef ();
}

template<class T, class E>
apImage<T,E>::apImage (unsigned int width, unsigned int height)
: image_ (0)
{
  image_ = new apImageRep<T,E> (width, height);
  image_->addRef ();
}


template<class T, class E>
apImage<T,E>::apImage (apImageRep<T,E>* rep)
: image_ (rep)
{
  image_->addRef ();
}



template<class T, class E>
apImage<T,E>::apImage (const apImage& src)
{
  image_ = src.image_;
  image_->addRef ();
}

template<class T, class E>
apImage<T,E>& apImage<T,E>::operator= (const apImage& src)
{
  // Make sure we don't copy ourself!
  if (image_ == src.image_) return *this;

  image_->subRef ();  // Remove reference from existing object
  image_ = src.image_;
  image_->addRef ();  // Add reference to our new object

  return *this;
}



// ***********************
// *                     *
// *  apImageRep inline  *
// *                     *
// ***********************

template<class T, class E>
apImageRep<T,E>* apImageRep<T,E>::sNull_ = 0;

template<class T, class E>
apImageRep<T,E>* apImageRep<T,E>::gNull ()
{
  if (!sNull_) {
    sNull_ = new apImageRep (0, 0);
    sNull_->addRef ();  // We never want to delete the null object
  }
  return sNull_;
}


template<class T, class E>
apImageRep<T,E>::apImageRep (unsigned int width, unsigned int height)
: width_ (width), height_ (height), ref_ (0)
{
  pixels_ = apAlloc<T> (width*height);
}

  
template<class T, class E>
const T& apImageRep<T,E>::getPixel (unsigned int x, unsigned int y) const
{
  return pixels_[y*width_ + x];
}


template<class T, class E>
void apImageRep<T,E>::setPixel (unsigned int x, unsigned int y, 
                                const T& pixel)
{
  pixels_[y*width_ + x] = pixel;
}


template<class T, class E>
apImage<T,E> apImageRep<T,E>::thumbnail (unsigned int reduction) const
{
  apImageRep<T,E>* output = 
    new apImageRep<T,E> (width()/reduction, 
                         height()/reduction);

  for (unsigned int ty=0; ty<output->height(); ty++) {
    for (unsigned int tx=0; tx<output->width(); tx++) {
      E sum = 0;
      for (unsigned int y=0; y<reduction; y++) {
        for (unsigned int x=0; x<reduction; x++)
          sum += getPixel (tx*reduction+x, ty*reduction+y);
      }
      output->setPixel (tx, ty, static_cast<T>(sum / (reduction*reduction)));
    }
  }

  // Convert to apImage via the protected constructor
  return output;
}





#endif // _imageTmpl_h_

