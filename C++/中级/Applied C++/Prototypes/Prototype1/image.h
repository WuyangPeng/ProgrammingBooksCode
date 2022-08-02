#ifndef _image_h_
#define _image_h_

// image.h
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
//  Image class prototype #1
//
// Uses apAlloc<> to allocate memory
// apImage8 class only
// No templates

#include "allocTmpl.h"




// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


// Simplify how we specify what our image is made of
typedef unsigned char Pel8;
typedef unsigned int  Pel32;



// **************
// *            *
// *  apImage8  *
// *            *
// **************
//
// 8-bit (unsigned) image class

class apImage8
{
public:
  apImage8 ();
  // Creates a null image, suitable for later assignment

  apImage8 (int width, int height);
  // Creates an image of the specified size

  virtual ~apImage8 ();

  int width  () const { return width_;}
  int height () const { return height_;}

  const Pel8* pixels () const { return pixels_.data();}
  Pel8*       pixels ()       { return pixels_.data();}
  // Return pointer to start of pixel data
  
  Pel8 getPixel (int x, int y) const;
  void setPixel (int x, int y, Pel8 pixel);
  // Get/set a single pixel

  // Image operations (only one for the prototype)
  virtual apImage8 thumbnail (unsigned int reduction) const;

  // Default copy ctor and assignment are ok
protected:
  apAlloc<Pel8> pixels_; // Pixel data
  int           width_;  // Image dimensions
  int           height_;
};



// ***************
// *             *
// *  apImage32  *
// *             *
// *********(*****
//
// 32-bit (unsigned) image class

class apImage32
{
public:
  apImage32 ();
  // Creates a null image, suitable for later assignment

  apImage32 (int width, int height);
  // Creates an image of the specified size

  virtual ~apImage32 ();

  int width  () const { return width_;}
  int height () const { return height_;}

  const Pel32* pixels () const { return pixels_.data();}
  Pel32*       pixels ()       { return pixels_.data();}
  // Return pointer to start of pixel data
  
  Pel32 getPixel (int x, int y) const;
  void setPixel (int x, int y, Pel32 pixel);
  // Get/set a single pixel

  // Image operations (only one for the prototype)
  virtual apImage32 thumbnail (unsigned int reduction) const;

  // Default copy ctor and assignment are ok
protected:
  apAlloc<Pel32> pixels_; // Pixel data
  int            width_;  // Image dimensions
  int            height_;
};


#endif // _image_h_
