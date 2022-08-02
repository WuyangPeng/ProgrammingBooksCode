#ifndef _geometry_h_
#define _geometry_h_

// geometry.h
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
// Geometric classes for our ap* classes


#include <utility>         // pair<>


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// ********************
// *                  *
// *  Pel Data Types  *
// *                  *
// ********************

// It is very useful to keep pixel types separate to improve
// readability and to make it easier to make changes.

typedef unsigned char  Pel8;     // 1-byte
typedef unsigned short Pel16;    // 2-bytes
typedef unsigned int   Pel32;    // 4-bytes  (Unsigned)
typedef int            Pel32s;   // 4-bytes  (Signed)




// *************
// *           *
// *  min/max  *
// *           *
// *************

template <class T> const T& apMin (const T& a, const T& b)
{ return (a<b) ? a : b;}

template <class T> const T& apMax (const T& a, const T& b)
{ return (a>b) ? a : b;}



// *************
// *           *
// *  apPoint  *
// *           *
// *************
//
// The stl pair<> class comes close to what I want, but I want
// it to look like a coordinate pair rather than two pieces of
// data.

class apPoint
{
public:
  apPoint () : x_ (0), y_ (0) {}
  apPoint (std::pair<int, int> p) 
    : x_ (p.first), y_ (p.second) {}
  apPoint (int x, int y) : x_ (x), y_ (y) {}

  int x () const { return x_;}
  int y () const { return y_;}
  std::pair<int, int> point () const 
  { return std::pair<int, int>(x_, y_);}

  bool  operator == (const apPoint& p) const
  { return x() == p.x() && y() == p.y();}

  apPoint& operator += (const apPoint& p)
  { x_ += p.x(); y_ += p.y(); return *this;}

  // Default copy constructor and assignment operators ok.
private:
  int x_, y_;
};


class apBString;  // Forward declaration.
apBString& operator<< (apBString& stream, const apPoint& point);
apBString& operator>> (apBString& stream, apPoint& point);




// ************
// *          *
// *  apRect  *
// *          *
// ************
//
// 

class apRect
{
public:
  apRect ();
  apRect (apPoint ul, unsigned int width, unsigned int height);
  apRect (apPoint ul, apPoint lr);
  apRect (int x0, int y0, unsigned int width, unsigned int height);

  const apPoint& ul () const { return ul_;}
  apPoint        lr () const;
  // Returns upper-left and lower-right coordinates

  int  x0     () const { return ul_.x();}
  int  y0     () const { return ul_.y();}
  int  x1     () const { return lr().x();}
  int  y1     () const { return lr().y();}

  unsigned int  width  () const { return width_;}
  unsigned int  height () const { return height_;}

  bool  isNull () const { return width_ == 0 || height_ == 0;}
  // Returns true if the rectangle is null

  bool  operator == (const apRect& r) const;
  bool  operator != (const apRect& r) const
  { return !operator== (r);}
  // Returns true if this rectangle is identical

  bool  within (const apPoint& p) const;
  // Returns true if the point is within the rectangle

  apRect intersect (const apRect& r) const;
  // Returns the intersection of two rectangles

  void expand (int x, int y);
  // Expand the size of the region in each dimension.
  // The width get 2x bigger, the height 2y bigger.
  // This can also be used to shrink a rectangle.

  // Default copy constructor and assignment operators ok.
private:
  apPoint ul_;          // Upper-left hand coordinates
  unsigned int width_;  // Image width
  unsigned int height_; // Image height
};


apBString& operator<< (apBString& stream, const apRect& rect);
apBString& operator>> (apBString& stream, apRect& rect);



#endif // _geometry_h_
