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
// Image class prototype #3
//
// apImageStorageTmpl<> encapsulates image storage (handle)
// apImage<> contains an instance of apImageStorageTmpl<>
//   - Pel datatype
//   - Internal Pel computation (ex. for summing).

#include "imageStorageTmpl.h"




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


template<class T, class E> 
class apImage
{
public:
  apImage ();
  // Creates a null image, suitable for later assignment

  apImage (unsigned int width, unsigned int height) : pixels_ (width, height) {}
  // Creates an image of the specified size

  ~apImage () {}

  unsigned int width  () const { return pixels_->width();}
  unsigned int height () const { return pixels_->height();}

  const T* pixels () const { return pixels_->base();}
  T*       pixels ()       { return pixels_->base();}
  // Return pointer to start of pixel data
  
  const T& getPixel (unsigned int x, unsigned int y) const;
  void     setPixel (unsigned int x, unsigned int y, const T& pixel);
  // Get/set a single pixel

  // Image operations (only one for the prototype)
  apImage<T, E> thumbnail (unsigned int reduction) const;

  // Default copy ctor and assignment are ok
protected:
  apImage (apImageStorageTmpl<T>& storage);
  // Construct an image from the storage

  apImageStorageTmpl<T> pixels_;  // The actual image data
};





// ********************
// *                  *
// *  apImage inline  *
// *                  *
// ********************

template<class T, class E>
apImage<T,E>::apImage ()
{}


template<class T, class E>
apImage<T,E>::apImage (apImageStorageTmpl<T>& storage)
: pixels_ (storage)
{}



template<class T, class E>
const T& apImage<T,E>::getPixel (unsigned int x, unsigned int y) const
{
  return (pixels_->base())[y*width() + x];
}


template<class T, class E>
void apImage<T,E>::setPixel (unsigned int x, unsigned int y, 
                             const T& pixel)
{
  (pixels_->base())[y*width() + x] = pixel;
}


template<class T, class E>
apImage<T,E> apImage<T,E>::thumbnail (unsigned int reduction) const
{
  apImage<T,E> output(width()/reduction, height()/reduction);

  for (unsigned int ty=0; ty<output.height(); ty++) {
    for (unsigned int tx=0; tx<output.width(); tx++) {
      E sum = 0;
      for (unsigned int y=0; y<reduction; y++) {
        for (unsigned int x=0; x<reduction; x++)
          sum += getPixel (tx*reduction+x, ty*reduction+y);
      }
      output.setPixel (tx, ty, static_cast<T>(sum / (reduction*reduction)));
    }
  }

  return output;
}





#endif // _imageTmpl_h_

