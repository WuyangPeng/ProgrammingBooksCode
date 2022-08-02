#ifndef _imageTypes_h_
#define _imageTypes_h_

// imageTypes.h
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
// Definition of our supported image types

#ifdef WIN32
#pragma warning(disable:4786) // Disable warning regarding long symbol names caused by templates
#pragma warning(disable:4244) // Don't show possible conversion error for op+= and related
#endif


#include "geometry.h"

#include <iostream>


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


// *****************
// *               *
// *  apLimitInfo  *
// *               *
// *****************
//
// A generic image processing function needs to know certain
// information about data types. For example, the minimum value
// for a type is something which is difficult to decide at runtime.
// A apTypeInfo object should be defined for each datatype. This
// allows proper rounding, clamping, etc. to occur.
//
// One object is constructed per type. This object is similar to the
// numeric_limits<> defined in <limits>, except we only care about 
// min() and max().

template<class T> class apLimitInfo
{
public:
  static apLimitInfo<T> sType;

  T minValue;
  T maxValue;

private:
  apLimitInfo (T min, T max) : minValue (min), maxValue (max) {}
};


// Perform limit checking so pixel values don't wrap
// Usage: D dst = apLimit<D> (src); 
// Use this instead of 'dst= src'
// Some specializations are found elsewhere in this file
template<class D, class S> D apLimit (const S& src)
{
  return src < apLimitInfo<D>::sType.minValue ? apLimitInfo<D>::sType.minValue : 
        (src > apLimitInfo<D>::sType.maxValue ? apLimitInfo<D>::sType.maxValue : static_cast<D>(src));
}



// ***********************
// *                     *
// *  Generic Functions  *
// *                     *
// ***********************
//
// The image processing functions frequently call functions
// like this to perform basic operations. These do so with
// clamping.
//
// We would very much like to define a generic function template
// that looks like,
//
//    template<class D, class S1, class S2>
//    D add2 (const S1& s1, const S2& s2)
//    {
//      return static_cast<D>(s1) + s2;
//    }
//
// However, we aren't so fortunate, because we also want to 
// define a function that looks like this,
//
//    template<class D, class S1, class S2>
//    D add2 (const apClampedTmpl<S1>& s1, const apClampedTmpl<S2>& s2)
//    {
//      return apLimit<D> (s1.val + s2.val);   // d = s1 + s2;
//    }
//
// The problem is that these create an ambiguity when a template
// of the latter type (ie. apClampedTmpl<>) is instantiated. See
// the C++ standard, "Partial Ordering of Function Templates" 
// (section 5.5.2) and "Template Argument Deduction" (section 8.2).
//
// The behavior on various compilers is erratic. To avoid this problem,
// we explicitly define the common forms we'll need and let the compiler
// generate the other ones as needed. This avoid the ambiguity error.

#if 0
// early gcc can handle this without problem. For now, we'll define
// these by hand.

template<class D, class S1, class S2>
D add2 (const S1& s1, const S2& s2)
{
  return static_cast<D>(s1) + s2;
}


template<class D, class S1, class S2>
D sub2 (const S1& s1, const S2& s2)
{
  return static_cast<D>(s1) - s2;
}

template<class D, class S1, class S2>
D mul2 (const S1& s1, const S2& s2)
{
  return static_cast<D>(s1) * s2;
}

template<class D, class S1, class S2>
D div2 (const S1& s1, const S2& s2)
{
  return static_cast<D>(s1) / s2;
}

template<class D, class S>
D scale (S& s1, float scaling)
{
  return static_cast<D> (scaling * static_cast<float>(s1));
}


#else
// We define manual versions. If you encounter errors with missing versions
// of add2<>, sub2<>, mul2<>, div2<>, or scale<>, chances are you will need
// to add more entries here.

template<class D> D add2 (Pel32s s1, Pel32s s2)
{ return static_cast<D>(s1 + s2);}

template<class D> D sub2 (Pel32s s1, Pel32s s2)
{ return static_cast<D>(s1 - s2);}

template<class D> D mul2 (Pel32s s1, Pel32s s2)
{ return static_cast<D>(s1 * s2);}

template<class D> D div2 (Pel32s s1, Pel32s s2)
{ return static_cast<D>(s1 / s2);}

template<class D> D scale (Pel32s s1, float scaling)
{ return static_cast<D> (scaling * s1);}

template<class D> D scale (Pel8 s1, float scaling)
{ return static_cast<D> (scaling * s1);}

template<class D> D scale (Pel16 s1, float scaling)
{ return static_cast<D> (scaling * s1);}

template<class D> D scale (double s1, float scaling)
{ return static_cast<D> (scaling * s1);}

#endif




// ************************
// *                      *
// *  Clamped pixel type  *
// *                      *
// ************************
//
// Built-in types, like char or short do not have
// any overflow checks built-in.  For example:
//   char c = 250;
//   c += 10;
// In this case, c has a value of 4. This wrapping will
// cause problems for image processing routines so we
// want something like this:
//   apClampedTmpl<char> c = 250;
//   c += 10;
// And in this case, c = 255. This doesn't come without
// doing a bit of work, but it is worth it.
//
// This list of supported operators is not necessarily 
// complete, but it is sufficient for our class right now.
//
// Everything is defined in the header file. The definitions are simple
// and win32 (at least VC6) has problems when you split the declaration
// from the definition (and use the 'export' keyword).

template<class T> class apClampedTmpl
{
public:
  T val;

  apClampedTmpl ()    : val(0) {}
  apClampedTmpl (T v) : val(v) {}

  operator T () const { return val;}

  apClampedTmpl (const apClampedTmpl& src)
  {
    val = apLimit<T> (src.val);
  }

  template<class T1>
  apClampedTmpl (const apClampedTmpl<T1>& src)
  {
    val = apLimit<T> (src.val);
  }


  apClampedTmpl<T>& operator= (const apClampedTmpl& src)
  {
    val = apLimit<T> (src.val);
    return *this;
  }

  /*
  template<class T1>
  apClampedTmpl<T>& operator= (const apClampedTmpl<T1>& src)
  {
    val = apLimit<T> (src.val);
    return *this;
  }
  */

  /*
  apClampedTmpl& operator= (const T& c)
  {
    val = c;
    return *this;
  }
  */


  apClampedTmpl<T>& operator+= (const apClampedTmpl<T>& s)
  {
    val = apLimit<T> (val + s.val);
    return *this;
  }

  apClampedTmpl<T>& operator-= (const apClampedTmpl<T>& s)
  {
    val = apLimit<T> (val - s.val);
    return *this;
  }

  apClampedTmpl<T>& operator*= (const apClampedTmpl<T>& s)
  {
    val = apLimit<T> (val * s.val);
    return *this;
  }

  apClampedTmpl<T>& operator/= (const apClampedTmpl<T>& s)
  {
    val = apLimit<T> (val / s.val);
    return *this;
  }

  template <class T2>
  apClampedTmpl<T> operator+ (const apClampedTmpl<T2>& s2)
  {
    apClampedTmpl<T> dst;
    dst.val = apLimit<T> (val + s2.val);
    return dst;
  }

};


// *************
// *           *
// *  typedef  *
// *           *
// *************
//
// Common types our applications might use

typedef apClampedTmpl<Pel8>   apClampedPel8;
typedef apClampedTmpl<Pel16>  apClampedPel16;
typedef apClampedTmpl<Pel32>  apClampedPel32;
typedef apClampedTmpl<Pel32s> apClampedPel32s;   // This is signed!!



// *********************************
// *                               *
// *  apClampedTmpl<T> non-member  *
// *                               *
// *********************************
//
// bool operator== (const apClampedTmpl<T>& s1, const apClampedTmpl<T>& s2);
// bool operator== (const apClampedTmpl<T>& s1, const T& s2);
// bool operator!= (const apClampedTmpl<T>& s1, const apClampedTmpl<T>& s2);
// bool operator!= (const apClampedTmpl<T>& s1, const T& s2);
//
// apClampedTmpl<T1> operator+ (const apClampedTmpl<T1>& s1, const T2& s2);
// apClampedTmpl<T1> operator- (const apClampedTmpl<T1>& s1, const T2& s2);
// apClampedTmpl<T1> operator* (const apClampedTmpl<T1>& s1, const T2& s2);
// apClampedTmpl<T1> operator/ (const apClampedTmpl<T1>& s1, const T2& s2);
//
// std::ostream& operator<< (std::ostream& stream, const apClampedTmpl<T>& val);


template<class T>
bool operator== (const apClampedTmpl<T>& s1, const apClampedTmpl<T>& s2)
{
  return s1.val == s2.val;
}

template<class T>
bool operator!= (const apClampedTmpl<T>& s1, const apClampedTmpl<T>& s2)
{
  return s1.val != s2.val;
}


template<class T>
bool operator== (const apClampedTmpl<T>& s1, const T& s2)
{
  return s1.val == s2;
}

template<class T>
bool operator!= (const apClampedTmpl<T>& s1, const T& s2)
{
  return s1.val != s2;
}


template<class T1, class T2>
apClampedTmpl<T1> operator+ (const apClampedTmpl<T1>& s1, const T2& s2)
{
  apClampedTmpl<T1> dst;
  dst.val = apLimit<T1> (s1.val + s2);
  return dst;
}

template<class T1, class T2>
apClampedTmpl<T1> operator- (const apClampedTmpl<T1>& s1, const T2& s2)
{
  apClampedTmpl<T1> dst;
  dst.val = apLimit<T1> (s1.val - s2);
  return dst;
}

template<class T1, class T2>
apClampedTmpl<T1> operator* (const apClampedTmpl<T1>& s1, const T2& s2)
{
  apClampedTmpl<T1> dst;
  dst.val = apLimit<T1> (s1.val * s2);
  return dst;
}

template<class T1, class T2>
apClampedTmpl<T1> operator/ (const apClampedTmpl<T1>& s1, const T2& s2)
{
  apClampedTmpl<T1> dst;
  dst.val = apLimit<T1> (s1.val / s2);
  return dst;
}


template<class T>
std::ostream& operator<< (std::ostream& stream, const apClampedTmpl<T>& val)
{
  stream << val.val;
  return stream;
}


template<> std::ostream& operator<< (std::ostream& stream, const apClampedTmpl<Pel8>& rgb);
// We want to display the pixel value as a number, not as a character
// Even though this is an unsigned quantity, some compilers make mistakes




// ****************************
// *                          *
// *  apClampedTmpl<T> mixed  *
// *                          *
// ****************************
//
// add2<D> (const apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2);
// sub2<D> (const apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2);
// mul2<D> (const apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2);
// div2<D> (const apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2);
// scale<D> (const apClampedTmpl<T1>& s1, float scaling);
//
// apClampedTmpl<T1> operator+ (const apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2);
// apClampedTmpl<T1> operator- (const apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2);
// apClampedTmpl<T1> operator* (const apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2);
// apClampedTmpl<T1> operator/ (const apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2);
//
// apClampedTmpl<T1>& operator+= (apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2);
// apClampedTmpl<T1>& operator-= (apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2);
// apClampedTmpl<T1>& operator*= (apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2);
// apClampedTmpl<T1>& operator/= (apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2);


// apLimit<> specializations
template<> apClampedPel8 apLimit<apClampedPel8, apClampedPel32s> (const apClampedPel32s& src);

template<> Pel8   apLimit<Pel8,   Pel32s> (const Pel32s& src);
template<> Pel8   apLimit<Pel8,   Pel8>   (const Pel8& src);
template<> Pel32s apLimit<Pel32s, Pel32s> (const Pel32s& src);
template<> Pel32s apLimit<Pel32s, Pel32>  (const Pel32& src);

template<> apClampedPel8 apLimit<apClampedPel8, apClampedPel8> (const apClampedPel8& src);

template<> apClampedPel32s apLimit<apClampedPel32s, apClampedPel32s> (const apClampedPel32s& src);


template<class D, class S1, class S2>
D add2 (const apClampedTmpl<S1>& s1, const apClampedTmpl<S2>& s2)
{
  return apLimit<D> (s1.val + s2.val);   // d = s1 + s2;
}

template<class D, class S1, class S2>
D sub2 (const apClampedTmpl<S1>& s1, const apClampedTmpl<S2>& s2)
{
  return apLimit<D> (s1.val - s2.val);   // d = s1 - s2;
}

template<class D, class S1, class S2>
D mul2 (const apClampedTmpl<S1>& s1, const apClampedTmpl<S2>& s2)
{
  return apLimit<D> (s1.val * s2.val);   // d = s1 * s2;
}

template<class D, class S1, class S2>
D div2 (const apClampedTmpl<S1>& s1, const apClampedTmpl<S2>& s2)
{
  return apLimit<D> (s1.val / s2.val);   // d = s1 / s2;
}

template<class D, class S1>
D scale (const apClampedTmpl<S1>& s1, float scaling)
{
  return apLimit<D> (scaling * static_cast<float>(s1.val));   // d = k1 * s1
}


template<class T1, class T2>
apClampedTmpl<T1> operator+ (const apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2)
{
  apClampedTmpl<T1> dst = add2<apClampedTmpl<T1>, apClampedTmpl<T1>, apClampedTmpl<T2> > (s1, s2);
  return dst;
}

template<class T1, class T2>
apClampedTmpl<T1> operator- (const apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2)
{
  apClampedTmpl<T1> dst = sub2<apClampedTmpl<T1>, apClampedTmpl<T1>, apClampedTmpl<T2> > (s1, s2);
  return dst;
}

template<class T1, class T2>
apClampedTmpl<T1> operator* (const apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2)
{
  apClampedTmpl<T1> dst = mul2<apClampedTmpl<T1>, apClampedTmpl<T1>, apClampedTmpl<T2> > (s1, s2);
  return dst;
}

template<class T1, class T2>
apClampedTmpl<T1> operator/ (const apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2)
{
  apClampedTmpl<T1> dst = div2<apClampedTmpl<T1>, apClampedTmpl<T1>, apClampedTmpl<T2> > (s1, s2);
  return dst;
}


template<class T1, class T2>
apClampedTmpl<T1>& operator+= (apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2)
{
  s1.val = apLimit<T1> (s1.val + s2.val);   // d = s1 + s2;
  return s1;
}

template<class T1, class T2>
apClampedTmpl<T1>& operator-= (apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2)
{
  s1.val = apLimit<T1> (s1.val - s2.val);   // d = s1 - s2;
  return s1;
}

template<class T1, class T2>
apClampedTmpl<T1>& operator*= (apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2)
{
  s1.val = apLimit<T1> (s1.val * s2.val);   // d = s1 * s2;
  return s1;
}

template<class T1, class T2>
apClampedTmpl<T1>& operator/= (apClampedTmpl<T1>& s1, const apClampedTmpl<T2>& s2)
{
  s1.val = apLimit<T1> (s1.val / s2.val);   // d = s1 / s2;
  return s1;
}



// ******************
// *                *
// *  apRGBTmpl<T>  *
// *                *
// ******************
//
// A generic rgb triplet. I originally wanted to name it RGB but
// this runs into problems with macros defined on some platforms
// (like win32). The data members are left public so it acts like
// a struct. There are no virtual functions so the size
// of this object matches how we want memory to be written in
// memory. Most operators are written as non-member functions.

template<class T> class apRGBTmpl
{
public:
  T red;
  T green;
  T blue;

  apRGBTmpl ()              : red(0), green(0), blue(0) {}
  explicit apRGBTmpl (T v)  : red(v), green(v), blue(v) {}
  apRGBTmpl (T r, T g, T b) : red(r), green(g), blue(b) {} 

  T ts1 () const { return red;}
  T ts2 () const { return green;}
  T ts3 () const { return blue;}
  // Treat as generic tristimulas values

  apRGBTmpl (const apRGBTmpl& s)
  {
    red   = s.red;
    green = s.green;
    blue  = s.blue;
  }
  // Copy constructor

  apRGBTmpl<T>& operator= (const apRGBTmpl& src)
  {
    red   = src.red;
    green = src.green;
    blue  = src.blue;
    return *this;
  }

  template<class T1> apRGBTmpl (const apRGBTmpl<T1>& s)
  {
    red   = apLimit<T> (s.red);
    green = apLimit<T> (s.green);
    blue  = apLimit<T> (s.blue);
  }
  // Copy constructor

  template<class T1> apRGBTmpl<T>& operator= (const apRGBTmpl<T1>& src)
  {
    red   = apLimit<T> (src.red);
    green = apLimit<T> (src.green);
    blue  = apLimit<T> (src.blue);
    return *this;
  }

  apRGBTmpl& operator= (const T& c)
  {
    red   = c;
    green = c;
    blue  = c;
    return *this;
  }

  operator T () const
  { return (red + green + blue) / 3;}
  // Conversion to monochrome (averaging)

  // If you want the NTSC definition, use this
  //  double v = .299 * red + .587 * green + .114 * blue;
  //  return static_cast<T> (v);


  // A conversion operator is not needed because it does 
  // the same job as this:
  //  template<class T1> apRGBTmpl (const apRGBTmpl<T1>& s)
  //
  // Most compilers we tested did not complain about it.
  //
  //   template<class T2> operator apRGBTmpl<T2> () const
  //   {
  //      apRGBTmpl<T2> dst;
  //      dst.red   = apLimit<T> (red);
  //      dst.green = apLimit<T> (green);
  //      dst.blue  = apLimit<T> (blue);
  //      return dst;
  //    }


  apRGBTmpl<T>& operator+= (const apRGBTmpl<T>& s)
  {
    red   = apLimit<T> (red   + s.red);
    green = apLimit<T> (green + s.green);
    blue  = apLimit<T> (blue  + s.blue);
    return *this;
  }

  apRGBTmpl<T>& operator-= (const apRGBTmpl<T>& s)
  {
    red   = apLimit<T> (red   - s.red);
    green = apLimit<T> (green - s.green);
    blue  = apLimit<T> (blue  - s.blue);
    return *this;
  }

  apRGBTmpl<T>& operator*= (const apRGBTmpl<T>& s)
  {
    red   = apLimit<T> (red   * s.red);
    green = apLimit<T> (green * s.green);
    blue  = apLimit<T> (blue  * s.blue);
    return *this;
  }

  apRGBTmpl<T>& operator/= (const apRGBTmpl<T>& s)
  {
    red   = apLimit<T> (red   / s.red);
    green = apLimit<T> (green / s.green);
    blue  = apLimit<T> (blue  / s.blue);
    return *this;
  }


  apRGBTmpl<T>& operator+= (const T& s)
  {
    red   = apLimit<T> (red   + s);
    green = apLimit<T> (green + s);
    blue  = apLimit<T> (blue  + s);
    return *this;
  }

  apRGBTmpl<T>& operator-= (const T& s)
  {
    red   = apLimit<T> (red   - s);
    green = apLimit<T> (green - s);
    blue  = apLimit<T> (blue  - s);
    return *this;
  }

  apRGBTmpl<T>& operator*= (const T& s)
  {
    red   = apLimit<T> (red   * s);
    green = apLimit<T> (green * s);
    blue  = apLimit<T> (blue  * s);
    return *this;
  }

  apRGBTmpl<T>& operator/= (const T& s)
  {
    red   = apLimit<T> (red   / s);
    green = apLimit<T> (green / s);
    blue  = apLimit<T> (blue  / s);
    return *this;
  }
};




// *************
// *           *
// *  typedef  *
// *           *
// *************

typedef apRGBTmpl<Pel8>   apRGB;
typedef apRGBTmpl<Pel32>  apRGBPel32;
typedef apRGBTmpl<Pel32s> apRGBPel32s;   // This is signed!!




// *****************************
// *                           *
// *  apRGBTmpl<T> non-member  *
// *                           *
// *****************************
//
//   operator== (const apRGBTmpl<T>& s1, const apRGBTmpl<T>& s2)
//   operator!= (const apRGBTmpl<T>& s1, const apRGBTmpl<T>& s2)
//
//   operator+ (const apRGBTmpl<T1>& s1, const T2& s2)
//   operator- (const apRGBTmpl<T1>& s1, const T2& s2)
//   operator* (const apRGBTmpl<T1>& s1, const T2& s2)
//   operator/ (const apRGBTmpl<T1>& s1, const T2& s2)
//
//   operator+ (const apRGBTmpl<T1>& s1, const double& s2)
//   operator- (const apRGBTmpl<T1>& s1, const double& s2)
//   operator* (const apRGBTmpl<T1>& s1, const double& s2)
//   operator/ (const apRGBTmpl<T1>& s1, const double& s2)

//   operator<< (std::ostream& stream, const apRGBTmpl<T>& rgb)

template<class T>
bool operator== (const apRGBTmpl<T>& s1, const apRGBTmpl<T>& s2)
{
  return (s1.red == s2.red) && (s1.green == s2.green) && (s1.blue == s2.blue);
}

template<class T>
bool operator!= (const apRGBTmpl<T>& s1, const apRGBTmpl<T>& s2)
{
  return (s1.red != s2.red) || (s1.green != s2.green) || (s1.blue != s2.blue);
}


template<class T1, class T2>
apRGBTmpl<T1> operator+ (const apRGBTmpl<T1>& s1, const T2& s2)
{
  apRGBTmpl<T1> dst;
  dst.red   = apLimit<T1> (s1.red   + s2);
  dst.green = apLimit<T1> (s1.green + s2);
  dst.blue  = apLimit<T1> (s1.blue  + s2);
  return dst;
}
// template <class S, class D> void apLimit (const S& src, D& dst)

template<class T1, class T2>
apRGBTmpl<T1> operator- (const apRGBTmpl<T1>& s1, const T2& s2)
{
  apRGBTmpl<T1> dst;
  dst.red   = apLimit<T1> (s1.red   - s2);
  dst.green = apLimit<T1> (s1.green - s2);
  dst.blue  = apLimit<T1> (s1.blue  - s2);
  return dst;
}

template<class T1, class T2>
apRGBTmpl<T1> operator* (const apRGBTmpl<T1>& s1, const T2& s2)
{
  apRGBTmpl<T1> dst;
  dst.red   = apLimit<T1> (s1.red   * s2);
  dst.green = apLimit<T1> (s1.green * s2);
  dst.blue  = apLimit<T1> (s1.blue  * s2);
  return dst;
}

template<class T1, class T2>
apRGBTmpl<T1> operator/ (const apRGBTmpl<T1>& s1, const T2& s2)
{
  apRGBTmpl<T1> dst;
  dst.red   = apLimit<T1> (s1.red   / s2);
  dst.green = apLimit<T1> (s1.green / s2);
  dst.blue  = apLimit<T1> (s1.blue  / s2);
  return dst;
}


template<class T1>
apRGBTmpl<T1> operator+ (const apRGBTmpl<T1>& s1, const double& d)
{
  apRGBTmpl<T1> dst;
  dst.red   = apLimit<T1> (d + s1.red);
  dst.green = apLimit<T1> (d + s1.green);
  dst.blue  = apLimit<T1> (d + s1.blue);
  return dst;
}

template<class T1>
apRGBTmpl<T1> operator- (const apRGBTmpl<T1>& s1, const double& d)
{
  apRGBTmpl<T1> dst;
  dst.red   = apLimit<T1> (d - s1.red);
  dst.green = apLimit<T1> (d - s1.green);
  dst.blue  = apLimit<T1> (d - s1.blue);
  return dst;
}

template<class T1>
apRGBTmpl<T1> operator* (const apRGBTmpl<T1>& s1, const double& d)
{
  apRGBTmpl<T1> dst;
  dst.red   = apLimit<T1> (d * s1.red);
  dst.green = apLimit<T1> (d * s1.green);
  dst.blue  = apLimit<T1> (d * s1.blue);
  return dst;
}

template<class T1>
apRGBTmpl<T1> operator/ (const apRGBTmpl<T1>& s1, const double& d)
{
  apRGBTmpl<T1> dst;
  dst.red   = apLimit<T1> (d / s1.red);
  dst.green = apLimit<T1> (d / s1.green);
  dst.blue  = apLimit<T1> (d / s1.blue);
  return dst;
}


template<class T>
std::ostream& operator<< (std::ostream& stream, const apRGBTmpl<T>& rgb)
{
  stream << "(" << rgb.red << "," << rgb.green << "," << rgb.blue << ")";
  return stream;
}

template<> std::ostream& operator<< (std::ostream& stream, const apRGBTmpl<Pel8>& rgb);
// We want to display the pixel value as a number, not as a character
// Even though this is an unsigned quantity, some compilers make mistakes



// ************************
// *                      *
// *  apRGBTmpl<T> mixed  *
// *                      *
// ************************
//
//   apLimit<RGBPel32s, RGB> (const RGBPel32s& src, RGB& dst);
//
//   3 parameter operations
//   add2<D> (const apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
//   sub2<D> (const apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
//   mul2<D> (const apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
//   div2<D> (const apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
//
//   operator+ (const apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
//   operator- (const apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
//   operator* (const apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
//   operator/ (const apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
//
//   operator+= (const apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
//   operator-= (const apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
//   operator*= (const apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
//   operator/= (const apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
//

template<> apRGB     apLimit<apRGB,     apRGBPel32s> (const apRGBPel32s& src);
template<> apRGB     apLimit<apRGB,     apRGB>       (const apRGB& src);
template<> apRGBPel32s apLimit<apRGBPel32s, apRGBPel32s> (const apRGBPel32s& src);


template<class D, class S1, class S2>
apRGBTmpl<D> apMin (const apRGBTmpl<S1>& s1, const apRGBTmpl<S2>& s2)
{
  apRGBTmpl<D> d;
  d.red   = apLimit<D> (apMin (s1.red,   s2.red));
  d.green = apLimit<D> (apMin (s1.green, s2.green));
  d.blue  = apLimit<D> (apMin (s1.blue,  s2.blue));
  return d;
}


template<class D, class S1, class S2>
apRGBTmpl<D> add2 (const apRGBTmpl<S1>& s1, const apRGBTmpl<S2>& s2)
{
  apRGBTmpl<D> d;
  d.red   = apLimit<D> (s1.red   + s2.red);
  d.green = apLimit<D> (s1.green + s2.green);
  d.blue  = apLimit<D> (s1.blue  + s2.blue);
  return d;
}

template<class D, class S1, class S2>
apRGBTmpl<D> sub2 (const apRGBTmpl<S1>& s1, const apRGBTmpl<S2>& s2)
{
  apRGBTmpl<D> d;
  d.red   = apLimit<D> (s1.red   - s2.red);
  d.green = apLimit<D> (s1.green - s2.green);
  d.blue  = apLimit<D> (s1.blue  - s2.blue);
  return d;
}

template<class D, class S1, class S2>
apRGBTmpl<D> mul2 (const apRGBTmpl<S1>& s1, const apRGBTmpl<S2>& s2)
{
  apRGBTmpl<D> d;
  d.red   = apLimit<D> (s1.red   * s2.red);
  d.green = apLimit<D> (s1.green * s2.green);
  d.blue  = apLimit<D> (s1.blue  * s2.blue);
  return d;
}

template<class D, class S1, class S2>
apRGBTmpl<D> div2 (const apRGBTmpl<S1>& s1, const apRGBTmpl<S2>& s2)
{
  apRGBTmpl<D> d;
  d.red   = apLimit<D> (s1.red   / s2.red);
  d.green = apLimit<D> (s1.green / s2.green);
  d.blue  = apLimit<D> (s1.blue  / s2.blue);
  return d;
}

template<class D, class S1>
apRGBTmpl<D> scale (const apRGBTmpl<S1>& s1, float scaling)
{
  apRGBTmpl<D> d;
  d.red   = apLimit<D> (scaling * static_cast<float>(s1.red));
  d.green = apLimit<D> (scaling * static_cast<float>(s1.green));
  d.blue  = apLimit<D> (scaling * static_cast<float>(s1.blue));
  return d;
}


template<class T1, class T2>
apRGBTmpl<T1> operator+ (const apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
{
  apRGBTmpl<T1> d;
  d.red   = apLimit<T1> (s1.red   + s2.red);
  d.green = apLimit<T1> (s1.green + s2.green);
  d.blue  = apLimit<T1> (s1.blue  + s2.blue);
  return d;

  // On many platforms, a single line can be used, but some versions of
  // gcc have trouble figuring out which version of add2<> to use.
  // return add2<apRGBTmpl<T1> > (s1, s2);
}


template<class T1, class T2>
apRGBTmpl<T1> operator- (const apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
{
  apRGBTmpl<T1> d;
  d.red   = apLimit<T1> (s1.red   - s2.red);
  d.green = apLimit<T1> (s1.green - s2.green);
  d.blue  = apLimit<T1> (s1.blue  - s2.blue);
  return d;

  // See comment under operator+ (above)
  //return sub2<apRGBTmpl<T1> > (s1, s2);
}

template<class T1, class T2>
apRGBTmpl<T1> operator* (const apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
{
  apRGBTmpl<T1> d;
  d.red   = apLimit<T1> (s1.red   * s2.red);
  d.green = apLimit<T1> (s1.green * s2.green);
  d.blue  = apLimit<T1> (s1.blue  * s2.blue);
  return d;

  // See comment under operator+ (above)
  // return mul2<apRGBTmpl<T1> > (s1, s2);
}

template<class T1, class T2>
apRGBTmpl<T1> operator/ (const apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
{
  apRGBTmpl<T1> d;
  d.red   = apLimit<T1> (s1.red   / s2.red);
  d.green = apLimit<T1> (s1.green / s2.green);
  d.blue  = apLimit<T1> (s1.blue  / s2.blue);
  return d;

  // See comment under operator+ (above)
  // return div2<apRGBTmpl<T1> > (s1, s2);
}


template<class T1, class T2>
apRGBTmpl<T1>& operator+= (apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
{
  s1.red   = apLimit<T1> (s1.red   + s2.red);
  s1.green = apLimit<T1> (s1.green + s2.green);
  s1.blue  = apLimit<T1> (s1.blue  + s2.blue);
  return s1;
}

template<class T1, class T2>
apRGBTmpl<T1>& operator-= (apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
{
  s1.red   = apLimit<T1> (s1.red   - s2.red);
  s1.green = apLimit<T1> (s1.green - s2.green);
  s1.blue  = apLimit<T1> (s1.blue  - s2.blue);
  return s1;
}

template<class T1, class T2>
apRGBTmpl<T1>& operator*= (apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
{
  s1.red   = apLimit<T1> (s1.red   * s2.red);
  s1.green = apLimit<T1> (s1.green * s2.green);
  s1.blue  = apLimit<T1> (s1.blue  * s2.blue);
  return s1;
}

template<class T1, class T2>
apRGBTmpl<T1>& operator/= (apRGBTmpl<T1>& s1, const apRGBTmpl<T2>& s2)
{
  s1.red   = apLimit<T1> (s1.red   / s2.red);
  s1.green = apLimit<T1> (s1.green / s2.green);
  s1.blue  = apLimit<T1> (s1.blue  / s2.blue);
  return s1;
}



#endif // _imageTypes_h_

