#ifndef _imageFuncs2_h_
#define _imageFuncs2_h_

// imageFuncs2.h
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
// non-member image functions that take 2 image arguments


#include "image/imageTmpl.h"
#include "image/imageTools.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345




// ********************
// *                  *
// *  2 argument add  *
// *                  *
// ********************


template<class R, class T1, class T2, class T3,
         class S1, class S2, class S3>
void ap_add2 (const R&, const apImage<T1,S1>& src1, const apImage<T2,S2>& src2, apImage<T3,S3>& dst1)
{
  // Operate on each pixel 
  typename apImage<T1,S1>::row_iterator i1 = src1.row_begin();
  typename apImage<T2,S2>::row_iterator i2 = src2.row_begin();
  typename apImage<T3,S3>::row_iterator i3 = dst1.row_begin();
  unsigned int w = src1.width ();
  const T1* p1;
  const T2* p2;
  T3* p3;
  for (; i1 != src1.row_end(); i1++, i2++, i3++) {
    p1 = i1->p;
    p2 = i2->p;
    p3 = i3->p;
    for (unsigned int x=0; x<w; x++)
      *p3++ = add2<T3> (*p1++, *p2++);   // *p3++ = *p1++ + *p2++;
//      add2 (*p1++, *p2++, *p3++);  // *p3++ = *p1++ + *p2++;
  }
}


template<class T1, class T2, class T3, 
         class S1, class S2, class S3>
void add (const apImage<T1,S1>& src1, 
          const apImage<T2,S2>& src2,
          apImage<T3,S3>& dst1)
{
  apFunction_s1s2d1<T3,T1,T2,T3,S1,S2,S3> processor (ap_add2);
  processor.run (src1, src2, dst1);
}



template<class T1, class T2, class S1, class S2>
apImage<T1,S1> operator+ (const apImage<T1,S1>& src1, 
                             const apImage<T2,S2>& src2)
{
  // Get our types from the first parameter
  apImage<T1,S1> dst;
  add (src1, src2, dst);
  return dst;
}



// ********************
// *                  *
// *  2 argument sub  *
// *                  *
// ********************

template<class R, class T1, class T2, class T3,
         class S1, class S2, class S3>
void ap_sub2 (const R&, const apImage<T1,S1>& src1, const apImage<T2,S2>& src2, apImage<T3,S3>& dst1)
{
  // Operate on each pixel 
  typename apImage<T1,S1>::row_iterator i1 = src1.row_begin();
  typename apImage<T2,S2>::row_iterator i2 = src2.row_begin();
  typename apImage<T3,S3>::row_iterator i3 = dst1.row_begin();
  unsigned int w = src1.width ();
  const T1* p1;
  const T2* p2;
  T3* p3;
  for (; i1 != src1.row_end(); i1++, i2++, i3++) {
    p1 = i1->p;
    p2 = i2->p;
    p3 = i3->p;
    for (unsigned int x=0; x<w; x++)
      *p3++ = sub2<T3> (*p1++, *p2++);   // *p3++ = *p1++ - *p2++;
//      sub2 (*p1++, *p2++, *p3++);  // *p3++ = *p1++ - *p2++;
  }
}


template<class T1, class T2, class T3, 
         class S1, class S2, class S3>
void sub (const apImage<T1,S1>& src1, 
          const apImage<T2,S2>& src2,
          apImage<T3,S3>& dst1)
{
  apFunction_s1s2d1<T3,T1,T2,T3,S1,S2,S3> processor (ap_sub2);
  processor.run (src1, src2, dst1);
}



template<class T1, class T2, class S1, class S2>
apImage<T1,S1> operator- (const apImage<T1,S1>& src1, 
                             const apImage<T2,S2>& src2)
{
  // Get are types from the first parameter
  apImage<T1,S1> dst;
  sub (src1, src2, dst);
  return dst;
}


#endif // _imageFuncs2_h_
