#ifndef _imageTransform_h_
#define _imageTransform_h_

// imageTransform.h
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
// Image transformations


#include "image/imageTmpl.h"



// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// ***************
// *             *
// *  thumbnail  *
// *             *
// ***************


template<class R, class T1, class S1>
apImage<T1,S1> thumbnail (const apImage<T1,S1>& src1, unsigned int factor)
{
  apImageLocker<T1,S1> srcLocking (src1);
  apImage<T1,S1> dst;

  if (src1.isNull())
    return dst;

  apRect boundary (src1.x0(), src1.y0(), 
                   src1.width()/factor, src1.height()/factor);
  dst = apImage<T1,S1> (boundary, src1.alignment());

  typename apImage<T1,S1>::row_iterator s;
  typename apImage<T1,S1>::row_iterator d;
  typename apImage<T1,S1>::row_iterator s1;
  // apImage<T1,S1>::row_iterator s2;
  unsigned int w = dst.width ();
  const T1* sp;
  T1* dp;
  R sum;

  // Iterate over pixels in the destination
  for (d=dst.row_begin(), s=src1.row_begin(); d != dst.row_end(); d++, s+=factor) {
    dp = d->p;
    for (unsigned int x=0; x<w; x++) {
      sum = 0;
      s1 = s;
      for (unsigned int dy=0; dy<factor; dy++, s1++) {
        sp = s1->p + x*factor;
        for (unsigned int dx=0; dx<factor; dx++)
          sum += *sp++;
      }
      *dp++ = apLimit<T1> (sum / (factor*factor));
    }
  }

  return dst;
}



// ************************************
// *                                  *
// *  Nearest Neighbor Interpolation  *
// *                                  *
// ************************************

template<class T, class S>
T fetchPixel_NN (const apImage<T,S>& image, double x, double y)
{
  // getPixel() will throw an error if the coordinates are out of range

  unsigned int x0 = static_cast<unsigned int>(x+.5);
  unsigned int y0 = static_cast<unsigned int>(y+.5);
  return image.getPixel (x0, y0);
}



// *****************************
// *                           *
// *  Bi-linear Interpolation  *
// *                           *
// *****************************

template<class T, class S>
T fetchPixel_BLI (const apImage<T,S>& image, double x, double y)
{
  // getPixel() will throw an error if the coordinates are out of range

  unsigned int x0 = static_cast<unsigned int>(x);
  unsigned int y0 = static_cast<unsigned int>(y);
  double dx = x-x0;
  double dy = y-y0;

  T p1 = image.getPixel (x0, y0);

  if (x >= image.width()-1 || y >= image.height()-1)
    return p1; // Overflow

  T p2 = image.getPixel (x0+1, y0);
  T p3 = image.getPixel (x0, y0+1);
  T p4 = image.getPixel (x0+1, y0+1);

  double pel = (1.-dy)*(1.-dx)*p1 + (1.-dy)*dx*p2 + dy*(1.-dx)*p3 + dx*dy*p4;
  return static_cast<T>(pel);
}

template<>
apRGB fetchPixel_BLI (const apImage<apRGB>& image, double x, double y)
{
  // getPixel() will throw an error if the coordinates are out of range

  unsigned int x0 = static_cast<unsigned int>(x);
  unsigned int y0 = static_cast<unsigned int>(y);
  double dx = x-x0;
  double dy = y-y0;

  apRGB p1 = image.getPixel (x0, y0);

  if (x >= image.width()-1 || y >= image.height()-1)
    return p1; // Overflow

  apRGB p2 = image.getPixel (x0+1, y0);
  apRGB p3 = image.getPixel (x0, y0+1);
  apRGB p4 = image.getPixel (x0+1, y0+1);

  double pelr = (1.-dy)*(1.-dx)*p1.red + (1.-dy)*dx*p2.red + dy*(1.-dx)*p3.red + dx*dy*p4.red;
  double pelg = (1.-dy)*(1.-dx)*p1.green + (1.-dy)*dx*p2.green + dy*(1.-dx)*p3.green + dx*dy*p4.green;
  double pelb = (1.-dy)*(1.-dx)*p1.blue + (1.-dy)*dx*p2.blue + dy*(1.-dx)*p3.blue + dx*dy*p4.blue;
  return apRGB (static_cast<Pel8>(pelr), static_cast<Pel8>(pelg), static_cast<Pel8>(pelb));
}



// ************
// *          *
// *  Resize  *
// *          *
// ************

template<class T, class S>
apImage<T,S> resize (const apImage<T,S>& src, unsigned int width, unsigned int height=0)
{
  if (width == 0 && height == 0)
    return src.sNull;
  
  if (src.width() == 0 || src.height() == 0)
    return src.sNull;

  // Maintain aspect ratio if only one value is given
  if (width == 0)
    width = src.width() * height / src.height();
  if (height == 0)
    height = src.height() * width / src.width();

  // Compute the destination window
  apRect boundary (src.x0(), src.y0(), width, height);
  apImage<T,S> dst (boundary);

  // Compute our starting point in the source image and the steps we use to traverse it
  double sx;
  double sy = src.y0();
  double xscale = static_cast<double>(src.width()) / width;
  double yscale = static_cast<double>(src.height()) / height;

  typename apImage<T,S>::row_iterator i;
  T* p;
  for (i=dst.row_begin(); i!=dst.row_end(); i++) {
    sx = src.x0();
    p = i->p;
    for (unsigned int x=0; x<width; x++) {
      *p++ = fetchPixel_BLI (src, sx, sy);
      sx += xscale;
    }
    sy += yscale;
  }
  return dst;
}


// Nearest Neighbor version, mainly for demonstration
template<class T, class S>
apImage<T,S> resize_NN (const apImage<T,S>& src, unsigned int width, unsigned int height=0)
{
  if (width == 0 && height == 0)
    return src.sNull;
  
  // Maintain aspect ratio if only one value is given
  if (width == 0)
    width = src.width() * height / src.height();
  if (height == 0)
    height = src.height() * width / src.width();

  // Compute the destination window
  apRect boundary (src.x0(), src.y0(), width, height);
  apImage<T,S> dst (boundary);

  // Compute our starting point in the souce image and the steps we use to traverse it
  double sx = src.x0();
  double sy = src.y0();
  double xscale = static_cast<double>(src.width()) / width;
  double yscale = static_cast<double>(src.height()) / height;

  typename apImage<T,S>::row_iterator i;
  T* p;
  for (i=dst.row_begin(); i!=dst.row_end(); i++) {
    sx = src.x0();
    p = i->p;
    for (unsigned int x=0; x<width; x++) {
      *p++ = fetchPixel_NN (src, sx, sy);
      sx += xscale;
    }
    sy += yscale;
  }
  return dst;
}



#endif // _imageTransform_h_
