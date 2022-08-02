#ifndef _colorspace_h_
#define _colorspace_h_

// colorspace.h
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
//  Color space conversion functions


#include "image/imageTypes.h"

#include <math.h>  // acos

// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


// *****************
// *               *
// *  Color Plane  *
// *               *
// *****************

template<class T>
apImage<T> colorPlane1 (apImage<apRGBTmpl<T> >& image)
{
  apImage<T> dst (image.boundary());

  typename apImage<apRGBTmpl<T> >::row_iterator i1 = image.row_begin();
  typename apImage<T>::row_iterator i2 = dst.row_begin();

  int width = image.width();
  int x;

  const apRGBTmpl<T>* pels;
  T* peld;

  for (; i1!=image.row_end(); i1++, i2++) {
    pels = i1->p;
    peld = i2->p;
    for (x=0; x<width; x++) {
      *peld++ = pels->red;
      pels++;
    }
  }
  return dst;
}

template<class T>
apImage<T> colorPlane2 (apImage<apRGBTmpl<T> >& image)
{
  apImage<T> dst (image.boundary());

  typename apImage<apRGBTmpl<T> >::row_iterator i1 = image.row_begin();
  typename apImage<T>::row_iterator i2 = dst.row_begin();

  int width = image.width();
  int x;

  const apRGBTmpl<T>* pels;
  T* peld;

  for (; i1!=image.row_end(); i1++, i2++) {
    pels = i1->p;
    peld = i2->p;
    for (x=0; x<width; x++) {
      *peld++ = pels->green;
      pels++;
    }
  }
  return dst;
}

template<class T>
apImage<T> colorPlane3 (apImage<apRGBTmpl<T> >& image)
{
  apImage<T> dst (image.boundary());

  typename apImage<apRGBTmpl<T> >::row_iterator i1 = image.row_begin();
  typename apImage<T>::row_iterator i2 = dst.row_begin();

  int width = image.width();
  int x;

  const apRGBTmpl<T>* pels;
  T* peld;

  for (; i1!=image.row_end(); i1++, i2++) {
    pels = i1->p;
    peld = i2->p;
    for (x=0; x<width; x++) {
      *peld++ = pels->blue;
      pels++;
    }
  }
  return dst;
}



// *********
// *       *
// *  HSI  *
// *       *
// *********

typedef apRGBTmpl<Pel8>   apHSI;
typedef apRGBTmpl<Pel32>  apHSIPel32;
typedef apRGBTmpl<Pel32s> apHSIPel32s;   // This is signed!!

template<class T>
apRGBTmpl<T> RGB2HSI (const apRGBTmpl<T>& pel)
{
  static double twoPi = asin(1.) * 4.;

  apRGBTmpl<T> hsi;
  double t;
  
  T r = pel.red;
  T g = pel.green;
  T b = pel.blue;

  if (r==g && r==b && g==b) // Degenerate case. Grayscale
    return apRGBTmpl<T> (0, 0, r);

  // Hue
  t = acos(.5 * ((r-g)+(r-b)) / sqrt((r-g)*(r-g) + (r-b)*(g-b)));
  double sum = r+g+b;
  if (b > g) t = twoPi - t;  // 2*pi - t; Gives us 4 quadrant answer
  hsi.red = static_cast<T>(t * apLimitInfo<T>::sType.maxValue / twoPi);

  // Saturation
  t = 1. - 3. * min(r, min(g, b)) / sum;
  hsi.green = static_cast<T>(t * apLimitInfo<T>::sType.maxValue);

  // Intensity
  hsi.blue = (r + g + b) / 3;

  return hsi;
}


template<class T>
void RGB2HSI (apImage<apRGBTmpl<T> >& image)
{
  typename apImage<apRGBTmpl<T> >::row_iterator i;

  unsigned int width = image.width();
  unsigned int x;
  apRGBTmpl<T>* p;
  apRGBTmpl<T> pel;
  for (i=image.row_begin(); i!=image.row_end(); i++) {
    p = i->p;
    for (x=0; x<width; x++) {
      pel = *p;
      *p++ = RGB2HSI (pel);
//      *p++ = *p;
//      *p++ = RGB2HSI (*p);
    }
  }
}



#endif // _colorspace_h_
