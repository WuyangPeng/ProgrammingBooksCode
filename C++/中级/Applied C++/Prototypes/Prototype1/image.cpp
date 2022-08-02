//  image.cpp
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
// Image class prototype


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


#include "image.h"




// **************
// *            *
// *  apImage8  *
// *            *
// **************

apImage8::apImage8 () : width_ (0), height_ (0)
{}

apImage8::apImage8 (int width, int height)
: width_ (width), height_ (height)
{
  pixels_ = apAlloc<Pel8> (width*height);
}

apImage8::~apImage8 ()
{}
  

// Just a prototype so no error checking on coordinates
Pel8 apImage8::getPixel (int x, int y) const
{
  return pixels_[y*width_ + x];
}

void apImage8::setPixel (int x, int y, Pel8 pixel)
{
  pixels_[y*width_ + x] = pixel;
}


// Each pixel in the output image is the average of a block
// of pixels in the current image
apImage8 apImage8::thumbnail (unsigned int reduction) const
{
  apImage8 output (width()/reduction, height()/reduction);

  for (unsigned int ty=0; ty<output.height(); ty++) {
    for (unsigned int tx=0; tx<output.width(); tx++) {
      unsigned int sum = 0;
      for (unsigned int y=0; y<reduction; y++) {
        for (unsigned int x=0; x<reduction; x++)
          sum += getPixel (tx*reduction+x, ty*reduction+y);
      }
      output.setPixel (tx, ty, static_cast<Pel8>(sum / (reduction*reduction)));
    }
  }

  return output;
}



// ***************
// *             *
// *  apImage32  *
// *             *
// ***************

apImage32::apImage32 () : width_ (0), height_ (0)
{}

apImage32::apImage32 (int width, int height)
: width_ (width), height_ (height)
{
  pixels_ = apAlloc<Pel32> (width*height);
}

apImage32::~apImage32 ()
{}
  

// Just a prototype so no error checking on coordinates
Pel32 apImage32::getPixel (int x, int y) const
{
  return pixels_[y*width_ + x];
}

void apImage32::setPixel (int x, int y, Pel32 pixel)
{
  pixels_[y*width_ + x] = pixel;
}


// Each pixel in the output image is the average of a block
// of pixels in the current image
apImage32 apImage32::thumbnail (unsigned int reduction) const
{
  apImage32 output (width()/reduction, height()/reduction);

  for (unsigned int ty=0; ty<output.height(); ty++) {
    for (unsigned int tx=0; tx<output.width(); tx++) {
      unsigned int sum = 0;
      for (unsigned int y=0; y<reduction; y++) {
        for (unsigned int x=0; x<reduction; x++)
          sum += getPixel (tx*reduction+x, ty*reduction+y);
      }
      output.setPixel (tx, ty, sum / (reduction*reduction));
    }
  }

  return output;
}
