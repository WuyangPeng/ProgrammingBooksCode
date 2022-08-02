#ifndef _imageFuncs_h_
#define _imageFuncs_h_

// imageFuncs.h
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
// non-member image functions


#include "image/imageTmpl.h"
#include "image/imageTools.h"
#include "image/imageTypes.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// ******************************
// *                            *
// *  Mixed argument functions  *
// *                            *
// ******************************



// ******************
// *                *
// *  add (S1, D1)  *
// *  += (D1, S1)   *
// *                *
// ******************

template<class R, class T1, class T2, class S1, class S2>
void ap_accumulate (const R&, const apImage<T1,S1>& src1, apImage<T2,S2>& dst1)
{
  typename apImage<T1,S1>::row_iterator i1;
  typename apImage<T2,S2>::row_iterator i2;
  long w = src1.width ();
  const T1* p1;
  T2* p2;
  for (i1=src1.row_begin(), i2=dst1.row_begin(); i1 != src1.row_end(); i1++, i2++) {
    p1 = i1->p;
    p2 = i2->p;
    for (int x=0; x<w; x++)
      *p2++ += *p1++;
  }
}

template<class T1, class S1, class T2, class S2>
void add (const apImage<T1,S1>& src, apImage<T2,S2>& dst)
{
  apFunction_s1d1<T2,T1,T2,S1,S2> processor (ap_accumulate);
  processor.run (src, dst);
}


template<class T1, class S1, class T2, class S2>
apImage<T1,S1>& operator+= (apImage<T1,S1>& src1, 
                               const apImage<T2,S2>& src2)
{
  add (src2, src1);
  return src1;
}




// ***********************
// *                     *
// *  subtract (S1, D1)  *
// *  -= (D1, S1)        *
// *                     *
// ***********************

template<class R, class T1, class T2, class S1, class S2>
void ap_decumulate (const R&, const apImage<T1,S1>& src1, apImage<T2,S2>& dst1)
{
  typename apImage<T1,S1>::row_iterator i1;
  typename apImage<T2,S2>::row_iterator i2;
  long w = src1.width ();
  const T1* p1;
  T2* p2;
  for (i1=src1.row_begin(), i2=dst1.row_begin(); i1 != src1.row_end(); i1++, i2++) {
    p1 = i1->p;
    p2 = i2->p;
    for (int x=0; x<w; x++)
      *p2++ -= *p1++;
  }
}

template<class T1, class S1, class T2, class S2>
void sub (const apImage<T1,S1>& src, apImage<T2,S2>& dst)
{
  apFunction_s1d1<T2,T1,T2,S1,S2> processor (ap_decumulate);
  processor.run (src, dst);
}


template<class T1, class S1, class T2, class S2>
apImage<T1,S1>& operator-= (apImage<T1,S1>& src1, 
                            const apImage<T2,S2>& src2)
{
  sub (src2, src1);
  return src1;
}



#endif // _imageFuncs_h_
