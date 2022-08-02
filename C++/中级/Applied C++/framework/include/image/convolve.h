#ifndef _convolve_h_
#define _convolve_h_

// convolve.h
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
// Image convolution functions.
// This could have gone into imageFunc1.h but these functions are
// not needed in all applications


#ifdef WIN32
#pragma warning(disable:4244) // Don't show possible conversion error for op+= and related
#endif


#include "image/imageTmpl.h"
#include "image/imageTools.h"

#include <math.h>   // sqrt

// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


// *****************
// *               *
// *  convolution  *
// *               *
// *****************
//
// Given a kernel, compute the convolution of this kernel with 
// the source image. If a destination image is specified, the 
// destination boundary is intersected with the source boundary to
// determine which pixels to process. It is a little more 
// complicated than this since the size of the structuring element
// (i.e. the kernel) is taken into account. The kernel must be
// square, and odd (3x3, 5x5, ...). I could have made the kernel
// type configurable, but I haven't seen a case where a char 
// couldn't hold the values.



// *****************
// *               *
// *    generic    *
// *  convolution  *
// *               *
// *****************
//
// Takes a generic convolution kernel and computes the output image

template<class R, class T1, class T2, class S1, class S2>
void ap_convolve_generic (const R&, const apImage<T1,S1>& src1,
                          const char* kernel, unsigned int size, int divisor,
                          apImage<T2,S2>& dst1)
{
  typename apImage<T1,S1>::row_iterator i1 = src1.row_begin();
  typename apImage<T2,S2>::row_iterator i2 = dst1.row_begin();

  typename apImage<T1,S1>::row_iterator i1k;

  unsigned int h = src1.height() - (size-1);
  unsigned int w = src1.width()  - (size-1);

  const T1* pk;
  const char* k;
  T2* p2;
  R sum;
  unsigned int x, y, xk, yk;

  for (y=0; y<h; y++, i1++, i2++) {
    p2 = i2->p;
    for (x=0; x<w; x++) {
      sum = 0;
      i1k = i1;
      k = kernel;
      for (yk=0; yk<size; yk++) {
        pk = i1k->p + x;
        for (xk=0; xk<size; xk++)
          sum += static_cast<R>(*pk++) * (*k++);
        i1k++;
      }
      if (divisor == 1)
        *p2++ = apLimit<T2> (sum);
      else {
        sum /= divisor;
        *p2++ = apLimit<T2> (sum);
      }
    }
  }
}



template<class R, class T1, class T2, class S1, class S2>
void convolve (const apImage<T1,S1>& src1, 
               const char* kernel, int size, int divisor,
               apImage<T2,S2>& dst1)
{
  apFunction_s1d1Convolve<R,T1,T2,S1,S2> processor (ap_convolve_generic);
  processor.run (src1, kernel, size, divisor, dst1);
}



// *****************
// *               *
// *  3x3 Lapacian *
// *  convolution  *
// *               *
// *****************
//
//             -1 -1 -1
//   Kernel:   -1  8 -1
//             -1 -1 -1


template<class R, class T1, class T2, class S1, class S2>
void ap_convolve_3x3laplacian (const R&, const apImage<T1,S1>& src1,
                               const char* /*kernel*/, unsigned int /*size*/, int /*divisor*/,
                               apImage<T2,S2>& dst1)
{
  typename apImage<T1,S1>::row_iterator i1 = src1.row_begin();
  typename apImage<T2,S2>::row_iterator i2 = dst1.row_begin();

  unsigned int h = src1.height() - 2;
  unsigned int w = src1.width()  - 2;

  const T1* p1;
  const T1* pk;
  T2* p2;
  R sum;
  unsigned int x, y;

  // Elements to skip from end of one row to start of next
  unsigned int pitch = (i1->bytes / sizeof (T1)) - 3;

  for (y=0; y<h; y++, i1++, i2++) {
    p1 = i1->p;
    p2 = i2->p;
    for (x=0; x<w; x++) {
      sum = 0;
      pk = p1 + x;

      sum -= *pk++;
      sum -= *pk++;
      sum -= *pk++;
      pk += pitch;

      sum -= *pk++;
      sum += (*pk++) * 8;
      sum -= *pk++;
      pk += pitch;

      sum -= *pk++;
      sum -= *pk++;
      sum -= *pk++;

      *p2++ = apLimit<T2> (sum);
    }
  }
}


// Specialization for RGB images (for speed)
template<>
void ap_convolve_3x3laplacian (const apRGBPel32s&, const apImage<apRGB>& src1,
                               const char* /*kernel*/, unsigned int /*size*/, int /*divisor*/,
                               apImage<apRGB>& dst1)
{
  apImage<apRGB>::row_iterator i1 = src1.row_begin();
  apImage<apRGB>::row_iterator i2 = dst1.row_begin();

  unsigned int h = src1.height() - 2;
  unsigned int w = src1.width()  - 2;

  const apRGB* p1;
  const apRGB* pk;
  apRGB* p2;
  apRGBPel32s sum;
  unsigned int x, y;

  // Elements to skip from end of one row to start of next
  unsigned int pitch = (i1->bytes / sizeof (apRGB)) - 3;

  for (y=0; y<h; y++, i1++, i2++) {
    p1 = i1->p;
    p2 = i2->p;
    for (x=0; x<w; x++) {
      sum = 0;
      pk = p1 + x;

      sum.red   -= pk->red;
      sum.green -= pk->green;
      sum.blue  -= pk->blue;
      pk++;
      sum.red   -= pk->red;
      sum.green -= pk->green;
      sum.blue  -= pk->blue;
      pk++;
      sum.red   -= pk->red;
      sum.green -= pk->green;
      sum.blue  -= pk->blue;
      pk++;

      pk += pitch;

      sum.red   -= pk->red;
      sum.green -= pk->green;
      sum.blue  -= pk->blue;
      pk++;
      sum.red   += 8*pk->red;
      sum.green += 8*pk->green;
      sum.blue  += 8*pk->blue;
      pk++;
      sum.red   -= pk->red;
      sum.green -= pk->green;
      sum.blue  -= pk->blue;
      pk++;

      pk += pitch;

      sum.red   -= pk->red;
      sum.green -= pk->green;
      sum.blue  -= pk->blue;
      pk++;
      sum.red   -= pk->red;
      sum.green -= pk->green;
      sum.blue  -= pk->blue;
      pk++;
      sum.red   -= pk->red;
      sum.green -= pk->green;
      sum.blue  -= pk->blue;
      pk++;

      *p2++ = apLimit<apRGB> (sum);  // Prevent wrapping
    }
  }
}


template<class R, class T1, class T2, class S1, class S2>
void laplacian3x3 (const apImage<T1,S1>& src1, 
                   apImage<T2,S2>& dst1)
{
  apFunction_s1d1Convolve<R,T1,T2,S1,S2> processor (ap_convolve_3x3laplacian);
  char* kernel = 0;
  unsigned int size = 3;
  int divisor = 1;
  processor.run (src1, kernel, size, divisor, dst1);
}




// ****************
// *              *
// *  3x3 Hipass  *
// *              *
// ****************
//
//             -1 -1 -1
//   Kernel:   -1  9 -1
//             -1 -1 -1

template<class R, class T1, class T2, class S1, class S2>
void ap_convolve_3x3hipass (const R&, const apImage<T1,S1>& src1,
                            const char* /*kernel*/, unsigned int /*size*/, int /*divisor*/,
                            apImage<T2,S2>& dst1)
{
  typename apImage<T1,S1>::row_iterator i1 = src1.row_begin();
  typename apImage<T2,S2>::row_iterator i2 = dst1.row_begin();

  unsigned int h = src1.height() - 2;
  unsigned int w = src1.width()  - 2;

  const T1* p1;
  const T1* pk;
  T2* p2;
  R sum;
  unsigned int x, y;

  // Elements to skip from end of one row to start of next
  unsigned int pitch = (i1->bytes / sizeof (T1)) - 3;

  for (y=0; y<h; y++, i1++, i2++) {
    p1 = i1->p;
    p2 = i2->p;
    for (x=0; x<w; x++) {
      sum = 0;
      pk = p1 + x;

      sum -= *pk++;
      sum -= *pk++;
      sum -= *pk++;
      pk += pitch;

      sum -= *pk++;
      sum += (*pk++) * 9;
      sum -= *pk++;
      pk += pitch;

      sum -= *pk++;
      sum -= *pk++;
      sum -= *pk++;

      *p2++ = apLimit<T2> (sum);
    }
  }
}


// Specialization for RGB images (for speed)
template<>
void ap_convolve_3x3hipass (const apRGBPel32s&, const apImage<apRGB>& src1,
                            const char* /*kernel*/, unsigned int /*size*/, int /*divisor*/,
                            apImage<apRGB>& dst1)

{
  apImage<apRGB>::row_iterator i1 = src1.row_begin();
  apImage<apRGB>::row_iterator i2 = dst1.row_begin();

  unsigned int h = src1.height() - 2;
  unsigned int w = src1.width()  - 2;

  const apRGB* p1;
  const apRGB* pk;
  apRGB* p2;
  apRGBPel32s sum;
  unsigned int x, y;

  // Elements to skip from end of one row to start of next
  unsigned int pitch = (i1->bytes / sizeof (apRGB)) - 3;

  for (y=0; y<h; y++, i1++, i2++) {
    p1 = i1->p;
    p2 = i2->p;
    for (x=0; x<w; x++) {
      sum = 0;
      pk = p1 + x;

      sum.red   -= pk->red;
      sum.green -= pk->green;
      sum.blue  -= pk->blue;
      pk++;
      sum.red   -= pk->red;
      sum.green -= pk->green;
      sum.blue  -= pk->blue;
      pk++;
      sum.red   -= pk->red;
      sum.green -= pk->green;
      sum.blue  -= pk->blue;
      pk++;

      pk += pitch;

      sum.red   -= pk->red;
      sum.green -= pk->green;
      sum.blue  -= pk->blue;
      pk++;
      sum.red   += 9*pk->red;
      sum.green += 9*pk->green;
      sum.blue  += 9*pk->blue;
      pk++;
      sum.red   -= pk->red;
      sum.green -= pk->green;
      sum.blue  -= pk->blue;
      pk++;

      pk += pitch;

      sum.red   -= pk->red;
      sum.green -= pk->green;
      sum.blue  -= pk->blue;
      pk++;
      sum.red   -= pk->red;
      sum.green -= pk->green;
      sum.blue  -= pk->blue;
      pk++;
      sum.red   -= pk->red;
      sum.green -= pk->green;
      sum.blue  -= pk->blue;
      pk++;

      *p2++ = apLimit<apRGB> (sum);  // Prevent wrapping
    }
  }
}

template<class R, class T1, class T2, class S1, class S2>
void hipass3x3 (const apImage<T1,S1>& src1, 
                apImage<T2,S2>& dst1)
{
  apFunction_s1d1Convolve<R,T1,T2,S1,S2> processor (ap_convolve_3x3hipass);
  char* kernel = 0;
  unsigned int size = 3;
  int divisor = 1;
  processor.run (src1, kernel, size, divisor, dst1);
}


// ****************
// *              *
// *  3x3 Lopass  *
// *              *
// ****************
//
// Gaussian
//             1 2 1
//   Kernel:   2 4 2  / 16
//             1 2 1

template<class R, class T1, class T2, class S1, class S2>
void ap_convolve_3x3lopass (const R&, const apImage<T1,S1>& src1,
                            const char* /*kernel*/, unsigned int /*size*/, int /*divisor*/,
                            apImage<T2,S2>& dst1)
{
  typename apImage<T1,S1>::row_iterator i1 = src1.row_begin();
  typename apImage<T2,S2>::row_iterator i2 = dst1.row_begin();

  unsigned int h = src1.height() - 2;
  unsigned int w = src1.width()  - 2;

  const T1* p1;
  const T1* pk;
  T2* p2;
  R sum;
  unsigned int x, y;

  // Elements to skip from end of one row to start of next
  unsigned int pitch = (i1->bytes / sizeof (T1)) - 3;

  for (y=0; y<h; y++, i1++, i2++) {
    p1 = i1->p;
    p2 = i2->p;
    for (x=0; x<w; x++) {
      sum = 0;
      pk = p1 + x;

      sum += *pk++;
      sum += *pk++ * 2;
      sum += *pk++;
      pk += pitch;

      sum += *pk++ * 2;
      sum += *pk++ * 4;
      sum += *pk++ * 2;
      pk += pitch;

      sum += *pk++;
      sum += *pk++ * 2;
      sum += *pk++;

      sum /= 16;
      *p2++ = apLimit<T2> (sum);  // Prevent wrapping
    }
  }
}

// Specialization for RGB images (for speed)
template<>
void ap_convolve_3x3lopass (const apRGBPel32s&, const apImage<apRGB>& src1,
                            const char* /*kernel*/, unsigned int /*size*/, int /*divisor*/,
                            apImage<apRGB>& dst1)

{
  apImage<apRGB>::row_iterator i1 = src1.row_begin();
  apImage<apRGB>::row_iterator i2 = dst1.row_begin();

  unsigned int h = src1.height() - 2;
  unsigned int w = src1.width()  - 2;

  const apRGB* p1;
  const apRGB* pk;
  apRGB* p2;
  apRGBPel32s sum;
  unsigned int x, y;

  // Elements to skip from end of one row to start of next
  unsigned int pitch = (i1->bytes / sizeof (apRGB)) - 3;

  for (y=0; y<h; y++, i1++, i2++) {
    p1 = i1->p;
    p2 = i2->p;
    for (x=0; x<w; x++) {
      sum = 0;
      pk = p1 + x;

      sum.red   += pk->red;
      sum.green += pk->green;
      sum.blue  += pk->blue;
      pk++;
      sum.red   += 2*pk->red;
      sum.green += 2*pk->green;
      sum.blue  += 2*pk->blue;
      pk++;
      sum.red   += pk->red;
      sum.green += pk->green;
      sum.blue  += pk->blue;
      pk++;

      pk += pitch;

      sum.red   += 2*pk->red;
      sum.green += 2*pk->green;
      sum.blue  += 2*pk->blue;
      pk++;
      sum.red   += 4*pk->red;
      sum.green += 4*pk->green;
      sum.blue  += 4*pk->blue;
      pk++;
      sum.red   += 2*pk->red;
      sum.green += 2*pk->green;
      sum.blue  += 2*pk->blue;
      pk++;

      pk += pitch;

      sum.red   += pk->red;
      sum.green += pk->green;
      sum.blue  += pk->blue;
      pk++;
      sum.red   += 2*pk->red;
      sum.green += 2*pk->green;
      sum.blue  += 2*pk->blue;
      pk++;
      sum.red   += pk->red;
      sum.green += pk->green;
      sum.blue  += pk->blue;
      pk++;

      sum.red   /= 16;
      sum.green /= 16;
      sum.blue  /= 16;
      *p2++ = apLimit<apRGB> (sum);  // Prevent wrapping
    }
  }
}

template<class R, class T1, class T2, class S1, class S2>
void lopass3x3 (const apImage<T1,S1>& src1, 
                apImage<T2,S2>& dst1)
{
  apFunction_s1d1Convolve<R,T1,T2,S1,S2> processor (ap_convolve_3x3lopass);
  char* kernel = 0;
  unsigned int size = 3;
  int divisor = 1;
  processor.run (src1, kernel, size, divisor, dst1);
}




// ***************
// *             *
// *  3x3 Sobel  *
// *             *
// ***************
//
//              -1 0 1              1  2  1
//   X Kernel:  -2 0 2   Y Kernel:  0  0  0
//              -1 0 1             -1 -2 -1

template<class R, class T1, class T2, class S1, class S2>
void ap_convolve_3x3sobelmag (const R&, const apImage<T1,S1>& src1,
                              const char* /*kernel*/, unsigned int /*size*/, int /*divisor*/,
                              apImage<T2,S2>& dst1)
{
  typename apImage<T1,S1>::row_iterator i1 = src1.row_begin();
  typename apImage<T2,S2>::row_iterator i2 = dst1.row_begin();

  unsigned int h = src1.height() - 2;
  unsigned int w = src1.width()  - 2;

  const T1* p1;
  const T1* pk;
  T2* p2;
  R sumx, sumy;
  R pel;
  unsigned int x, y;

  // Elements to skip from end of one row to start of next
  unsigned int pitch = (i1->bytes / sizeof (T1)) - 3;

  for (y=0; y<h; y++, i1++, i2++) {
    p1 = i1->p;
    p2 = i2->p;
    for (x=0; x<w; x++) {
      sumx = sumy = 0;
      pk = p1 + x;

      pel = *pk++;
      sumx -= pel;
      sumy += pel;
      sumy += 2 * (*pk++);
      pel = *pk++;
      sumx += pel;
      sumy += pel;
      pk += pitch;

      sumx -= 2 * (*pk++);
      pk++; // Skip this pixel
      sumx += 2 * (*pk++);
      pk += pitch;

      pel = *pk++;
      sumx -= pel;
      sumy -= pel;
      sumy -= 2 * (*pk++);
      pel = *pk++;
      sumx += pel;
      sumy -= pel;

      sumx = static_cast<R>(sqrt(static_cast<double>(sumx*sumx + sumy*sumy)));
      *p2++ = apLimit<T2> (sumx);  // Prevent wrapping
    }
  }
}

// Specialization for RGB images (for speed)
template<>
void ap_convolve_3x3sobelmag (const apRGBPel32s&, const apImage<apRGB>& src1,
                              const char* /*kernel*/, unsigned int /*size*/, int /*divisor*/,
                              apImage<apRGB>& dst1)

{
  apImage<apRGB>::row_iterator i1 = src1.row_begin();
  apImage<apRGB>::row_iterator i2 = dst1.row_begin();

  unsigned int h = src1.height() - 2;
  unsigned int w = src1.width()  - 2;

  const apRGB* p1;
  const apRGB* pk;
  apRGB* p2;
  apRGBPel32s sumx, sumy;
  apRGBPel32s pel;
  unsigned int x, y;

  // Elements to skip from end of one row to start of next
  unsigned int pitch = (i1->bytes / sizeof (apRGB)) - 3;

  for (y=0; y<h; y++, i1++, i2++) {
    p1 = i1->p;
    p2 = i2->p;
    for (x=0; x<w; x++) {
      sumx = sumy = 0;
      pk = p1 + x;

      // row 1
      pel = *pk++;
      sumx.red   -= pel.red;
      sumx.green -= pel.green;
      sumx.blue  -= pel.blue;
      sumy.red   += pel.red;
      sumy.green += pel.green;
      sumy.blue  += pel.blue;

      pel = *pk++;
      sumy.red   += 2*pel.red;
      sumy.green += 2*pel.green;
      sumy.blue  += 2*pel.blue;

      pel = *pk++;
      sumx.red   += pel.red;
      sumx.green += pel.green;
      sumx.blue  += pel.blue;
      sumy.red   += pel.red;
      sumy.green += pel.green;
      sumy.blue  += pel.blue;
      pk += pitch;

      // row 2
      pel = *pk++;
      sumx.red   -= 2*pel.red;
      sumx.green -= 2*pel.green;
      sumx.blue  -= 2*pel.blue;
      pk++;
      pel = *pk++;
      sumx.red   += 2*pel.red;
      sumx.green += 2*pel.green;
      sumx.blue  += 2*pel.blue;
      pk += pitch;

      // row 3
      pel = *pk++;
      sumx.red   -= pel.red;
      sumx.green -= pel.green;
      sumx.blue  -= pel.blue;
      sumy.red   -= pel.red;
      sumy.green -= pel.green;
      sumy.blue  -= pel.blue;

      pel = *pk++;
      sumy.red   -= 2*pel.red;
      sumy.green -= 2*pel.green;
      sumy.blue  -= 2*pel.blue;

      pel = *pk++;
      sumx.red   += pel.red;
      sumx.green += pel.green;
      sumx.blue  += pel.blue;
      sumy.red   -= pel.red;
      sumy.green -= pel.green;
      sumy.blue  -= pel.blue;

      sumx.red   = static_cast<Pel32s>(sqrt(static_cast<double>(sumx.red*sumx.red     + sumy.red*sumy.red)));
      sumx.green = static_cast<Pel32s>(sqrt(static_cast<double>(sumx.green*sumx.green + sumy.green*sumy.green)));
      sumx.blue  = static_cast<Pel32s>(sqrt(static_cast<double>(sumx.blue*sumx.blue   + sumy.blue*sumy.blue)));

      *p2++ = apLimit<apRGB> (sumx);  // Prevent wrapping
    }
  }
}

template<class R, class T1, class T2, class S1, class S2>
void sobel3x3mag (const apImage<T1,S1>& src1, 
                  apImage<T2,S2>& dst1)
{
  apFunction_s1d1Convolve<R,T1,T2,S1,S2> processor (ap_convolve_3x3sobelmag);
  char* kernel = 0;
  unsigned int size = 3;
  int divisor = 1;
  processor.run (src1, kernel, size, divisor, dst1);
}



// *********************
// *                   *
// *  Unsharp Masking  *
// *                   *
// *********************
//
// Simple, fixed unsharp masking
// The intermediate image is scaled before adding it to the
// output image.


template<class R, class T1, class S1>
apImage<T1,S1> unsharpMask (const apImage<T1,S1>& src, 
			    double strength=2.0)
{
  if (src.isNull())
    return src;

  // Compute our 5x5 gaussian (lopass) filter
  char kernel[] = { 0,  0,  1,  0, 0,
                    0,  8, 21,  8, 0,
                    1, 21, 59, 21, 1,
                    0,  8, 21,  8, 0,
                    0,  0,  1,  0, 0};
  apImage<T1,S1> gaussian;
  convolve<R> (src, kernel, 5, 179, gaussian);

  // Window our source image to be the same size
  apImage<T1,S1> srcWindow = src;
  srcWindow.window (gaussian.boundary());

  // Our destination is the same size as the gaussian
  apImage<T1,S1> dst (gaussian.boundary());

  // Compute our output using
  // strength * srcWindow + (1-strength) * gaussian
  typename apImage<T1,S1>::row_iterator s = srcWindow.row_begin ();
  typename apImage<T1,S1>::row_iterator d = dst.row_begin ();
  typename apImage<T1,S1>::row_iterator g = gaussian.row_begin ();

  unsigned int h = dst.height ();
  unsigned int w = dst.width ();

  unsigned int x, y;
  R sum;
  const T1* ps;
  const T1* pg;
  T1* pd;

  R pels, pelg;
  double gstrength = 1. - strength;

  for (y=0; y<h; y++, s++, d++, g++) {
    ps = s->p;
    pg = g->p;
    pd = d->p;

    for (x=0; x<w; x++) {
      pels = *ps++;
      pelg = *pg++;
      // The order is very important
      sum = static_cast<R>((pels * strength) + (pelg * gstrength));
      *pd++ = apLimit<T1> (sum);
    }
  }

  return dst;
}


// Note: We define as unsharpMask<apRGBPel32s> because some compilers must be
//       told about the first parameter, although it is not used anywhere
//       in the function. Microsoft Visual Studio for example does not need
//       this. gcc v3.0.4 complains.

template<>
apImage<apRGB> unsharpMask<apRGBPel32s> (const apImage<apRGB>& src, 
					 double strength)
{
  if (src.isNull())
    return src;

  // Compute our 5x5 gaussian (lopass) filter
  char kernel[] = { 0,  0,  1,  0, 0,
                    0,  8, 21,  8, 0,
                    1, 21, 59, 21, 1,   // Divisor is 179
                    0,  8, 21,  8, 0,
                    0,  0,  1,  0, 0};
  apImage<apRGB> gaussian;
  convolve<apRGBPel32s> (src, kernel, 5, 179, gaussian);

  // All of images are the same size as the gaussian
  apImage<apRGB> srcWindow = src;
  srcWindow.window (gaussian.boundary());
  apImage<apRGB> dst (gaussian.boundary());

  // Compute our output using
  // strength * srcWindow + (1-strength) * gaussian
  apImage<apRGB>::row_iterator s = srcWindow.row_begin ();
  apImage<apRGB>::row_iterator d = dst.row_begin ();
  apImage<apRGB>::row_iterator g = gaussian.row_begin ();

  unsigned int h = dst.height ();
  unsigned int w = dst.width ();

  unsigned int x, y;
  apRGBPel32s sum;
  const apRGB* ps;
  const apRGB* pg;
  apRGB* pd;

  apRGB pels, pelg;
  double gstrength = 1. - strength;

  for (y=0; y<h; y++, s++, d++, g++) {
    ps = s->p;
    pg = g->p;
    pd = d->p;

    for (x=0; x<w; x++) {
      pels = *ps++;
      pelg = *pg++;
      sum.red   = static_cast<Pel32s>(strength * pels.red  + gstrength * pelg.red);
      sum.green = static_cast<Pel32s>(strength * pels.green + gstrength * pelg.green);
      sum.blue  = static_cast<Pel32s>(strength * pels.blue  + gstrength * pelg.blue);

      *pd++ = apLimit<apRGB> (sum);  // Prevent wrapping
    }
  }

  return dst;
}




#endif // _convolve_h_
