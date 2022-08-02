// geometry.cpp
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
// Created 11/30/2001



#include "geometry.h"
#include "bstring.h"

#include <vector>


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// *************
// *           *
// *  apPoint  *
// *           *
// *************

// Since this object won't change, we don't need any versioning

apBString& operator<< (apBString& stream, const apPoint& point)
{
  apBString bstr;
  bstr << point.x() << point.y();

  stream << bstr;
  return stream;
}


apBString& operator>> (apBString& stream, apPoint& point)
{
  apBString bstr;
  stream >> bstr;

  int x, y;
  bstr >> x >> y;

  point = apPoint (x, y);
  return stream;
}



// ************
// *          *
// *  apRect  *
// *          *
// ************

// Since this object won't change, we don't need any versioning

apRect::apRect () : ul_ (apPoint(0,0)), width_ (0), height_ (0)
{}

apRect::apRect (apPoint ul, unsigned int width, unsigned int height)
: ul_ (ul), width_ (width), height_ (height)
{}

apRect::apRect (apPoint ul, apPoint lr)
: ul_ (ul), width_ (lr.x()-ul.x()), height_ (lr.y()-ul.y())
{}

apRect::apRect (int x0, int y0, int unsigned width, unsigned int height)
: ul_ (apPoint(x0,y0)), width_ (width), height_ (height)
{}


apPoint apRect::lr () const 
{
  return apPoint (ul_.x() + width_, ul_.y() + height_);
}

bool apRect::operator == (const apRect& r) const
{
  return (ul() == r.ul() && 
          width() == r.width() && height() == r.height());
}


bool apRect::within (const apPoint& p) const
{
  apPoint lr (ul_.x() + width_, ul_.y()+height_);
  return (ul_.x() <= p.x()) && (lr.x() > p.x()) &&
         (ul_.y() <= p.y()) && (lr.y() > p.y());
}


apRect apRect::intersect (const apRect& r) const
{
  // Get the corner points.
  const apPoint& ul1 = ul ();
  const apPoint& ul2 = r.ul ();
  int x = apMax (ul1.x(), ul2.x());
  int y = apMax (ul1.y(), ul2.y());
  int w = apMin (ul1.x()+width(),  ul2.x()+r.width()) - x;
  int h = apMin (ul1.y()+height(), ul2.y()+r.height()) - y;
  if (w < 0 || h < 0) {
    // No intersection
    return apRect ();
  }

  return apRect (x, y, w, h);
}


void apRect::expand (int x, int y)
{
  if (!isNull()) {
    ul_     += apPoint (-x, -y);
    width_  += 2*x;
    height_ += 2*y;
  }
}


apBString& operator<< (apBString& stream, const apRect& point)
{
  apBString bstr;

  bstr << point.x0() << point.y0() << point.width() << point.height();

  stream << bstr;
  return stream;
}

apBString& operator>> (apBString& stream, apRect& rect)
{
  apBString bstr;
  stream >> bstr;

  int x, y;
  unsigned int w, h;
  bstr >> x >> y >> w >> h;

  rect = apRect (x, y, w, h);
  return stream;
}
