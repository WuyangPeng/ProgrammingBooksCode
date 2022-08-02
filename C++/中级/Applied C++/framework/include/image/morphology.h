#ifndef _morphology_h_
#define _morphology_h_

// morphology.h
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
// Image morphology, especially using min/max operators


#include "image/imageTmpl.h"
#include "image/imageTools.h"
#include "image/imageTypes.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


// ****************
// *              *
// *  morphology  *
// *              *
// ****************

template<class R, class T1, class T2, class S1, class S2>
void ap_erode_cross (const R&, const apImage<T1,S1>& src1,
                     const char* /*kernel*/, unsigned int /*size*/, int /*divisor*/,
                     apImage<T2,S2>& dst1)
{
  typename apImage<T1,S1>::row_iterator i1 = src1.row_begin();
  typename apImage<T2,S2>::row_iterator i2 = dst1.row_begin();

  unsigned int h = src1.height() - 2;
  unsigned int w = src1.width()  - 2;

  const T1* p1;
  T2* p2;
  unsigned int x, y;

  // Elements to skip between rows
  unsigned int pitch = (i1->bytes / sizeof (T1));

  for (y=0; y<h; y++, i1++, i2++) {
    p1 = i1->p + (pitch + 1); // Center the pixel
    p2 = i2->p;
    for (x=0; x<w; x++) {
      *p2++ = apMin( apMin( apMin( apMin(*p1, *(p1-1)), *(p1+1)), 
                                 *(p1-pitch)), *(p1+pitch));
      *p1++;
    }
  }
}


template<class T1, class S1>
void erodeCross (const apImage<T1,S1>& src1, 
                 apImage<T1,S1>& dst1)
{
  apFunction_s1d1Convolve<T1,T1,T1,S1,S1> processor (ap_erode_cross);

  char* kernel = 0;
  unsigned int size = 3;
  int divisor = 1;
  processor.run (src1, kernel, size, divisor, dst1);
}


#endif // _morphology_h_
