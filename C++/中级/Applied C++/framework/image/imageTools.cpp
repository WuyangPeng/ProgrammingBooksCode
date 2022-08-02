// imageTools.cpp
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
// Tools for writing generic and specific image processing functions

#include "image/imageTools.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// *********************************
// *                               *
// *  Image Intersection Routines  *
// *                               *
// *********************************


apIntersectRects intersect (const apRect& src, const apRect& dst)
{
  apIntersectRects overlap;
  apRect srcOverlap = src;
  if (!dst.isNull())
    srcOverlap = srcOverlap.intersect (dst);

  overlap.src = srcOverlap;
  overlap.dst = srcOverlap;
  return overlap;
}


apIntersectRects intersect (const apRect& src, unsigned int xKernelSize, unsigned int yKernelSize, const apRect& dst)
{
  apIntersectRects overlap;
  if (xKernelSize < 1 || yKernelSize < 1)
    return overlap;

  // Expand the dst region to indicate pixels we would "like"
  // to have in our image.
  int xExpansion = (xKernelSize-1) / 2;
  int yExpansion = (yKernelSize-1) / 2;
  apRect dstRegion = dst;
  dstRegion.expand (xExpansion, yExpansion);

  // The source pixels we'll use are just the intersection
  apRect srcRegion = src;
  srcRegion = srcRegion.intersect (dstRegion);

  // We're done if there is no overlap or the overlap
  // area is not big enough.
  if (srcRegion.isNull() || 
      srcRegion.width() < xKernelSize || srcRegion.height() < yKernelSize)
    return overlap;

  // The destination pixels we'll have are handled by 
  // shrinking (i.e. eroding) the source region
  dstRegion = srcRegion;
  dstRegion.expand (-xExpansion, -yExpansion);

  overlap.src = srcRegion;
  overlap.dst = dstRegion;
  return overlap;
}


apIntersectRects intersect (const apRect& src1, const apRect& src2, const apRect& dst)
{
  apIntersectRects overlap;

  // Setup our src and dst regions we have to work with
  apRect srcOverlap = src1;
  srcOverlap = srcOverlap.intersect (src2);
  if (!dst.isNull())
    srcOverlap = srcOverlap.intersect (dst);

  overlap.src = srcOverlap;
  overlap.dst = srcOverlap;
  return overlap;
}

