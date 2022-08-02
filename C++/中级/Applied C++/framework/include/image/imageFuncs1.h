#ifndef _imageFuncs1_h_
#define _imageFuncs1_h_

// imageFuncs1.h
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
// non-member image functions that take 1 image argument

#include "image/imageTmpl.h"
#include "image/imageTools.h"

#include <typeinfo>


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345




// **********
// *        *
// *  copy  *
// *        *
// **********

// ap_copy always does a pixel by pixel copy. This version
// makes no assumptions about the type of T1 or T2. The next 
// version, ap_copyfast, makes the assumption that memcpy 
// can be used to duplicate pixels (if T1 == T2).


template<class R, class T1, class T2, class S1, class S2>
void ap_copy (const R&, const apImage<T1,S1>& src1, apImage<T2,S2>& dst1)
{
  typename apImage<T1,S1>::row_iterator i1;
  typename apImage<T2,S2>::row_iterator i2;
  unsigned int w = src1.width ();
  const T1* p1;
  T2* p2;
  for (i1=src1.row_begin(), i2=dst1.row_begin(); i1 != src1.row_end(); i1++, i2++) {
    p1 = i1->p;
    p2 = i2->p;
    for (unsigned int x=0; x<w; x++)
      *p2++ = static_cast<T2>(*p1++);
  }
}


template<class R, class T1, class T2, class S1, class S2>
void ap_copyfast (const R&, const apImage<T1,S1>& src1, apImage<T2,S2>& dst1)
{
  typename apImage<T1,S1>::row_iterator i1 = src1.row_begin();
  typename apImage<T2,S2>::row_iterator i2 = dst1.row_begin();
  unsigned int w = src1.width();
  unsigned int bytes = w * src1.bytesPerPixel ();
  const T1* p1;
  T2* p2;

  if (typeid(T1) == typeid(T2)) {
    // We're copying like datatypes so use memcpy for speed
    // This assumes T1 and T2 are POD (plain old data) types
    for (; i1 != src1.row_end(); i1++, i2++) {
      p1 = i1->p;
      p2 = i2->p;
      memcpy (p2, p1, bytes);
    }
  }
  else {
    // We have to do a pixel by pixel copy
    for (; i1 != src1.row_end(); i1++, i2++) {
      p1 = i1->p;
      p2 = i2->p;
      for (unsigned int x=0; x<w; x++)
        *p2++ = static_cast<T2>(*p1++);
    }
  }
}



template<class T1, class S1, class T2, class S2>
void copy (const apImage<T1,S1>& src, apImage<T2,S2>& dst)
{
  apFunction_s1d1<T2,T1,T2,S1,S2> processor (ap_copy);
  processor.run (src, dst);
}

template<class T1, class S1>
apImage<T1,S1> copy (const apImage<T1,S1>& src)
{
  // Assume we can use memcpy if possible.
  apImage<T1,S1> dst;

  apFunction_s1d1<T1,T1,T1,S1,S1> processor (ap_copyfast);
  processor.run (src, dst);

  return dst;
}

// If you are curious about how the above version of copy() can
// be written using the STL way, here is a version that does it.
// Since we do not have input iterators in images, you must
// allocate the destination and then use std::copy.
template<class T1, class S1>
apImage<T1,S1> copy_stl (const apImage<T1,S1>& src)
{
  apImageLocker<T1,S1> srcLocking (src);

  apImage<T1,S1> dst (src.boundary(), src.alignment());
  std::copy (src.begin(), src.end(), dst.begin());

  return dst;
}



// ***************
// *             *
// *  duplicate  *
// *             *
// ***************


template<class T1, class S1>
apImage<T1,S1> duplicate (const apImage<T1,S1>& src, 
                          apRectImageStorage::eAlignment align)
{
  if (src.isNull())
    return src;

  apImage<T1,S1> dst (src.boundary(), align);

  apFunction_s1d1<T1,T1,T1,S1,S1> processor (ap_copyfast);
  processor.run (src, dst);

  return dst;
}




#endif // _imageFuncs1_h_
