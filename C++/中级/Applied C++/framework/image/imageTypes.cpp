// imageTypes.cpp
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

#include "image/imageTypes.h"
#include <limits.h>
#include <float.h>


// Note: Some compilers do not seem to have an implementation for
//       std::numeric_limits<>. Because of this, we have to fall back
//       to using limits.h to get our limit information
//
// Instead of writing,
//   template<> apLimitInfo<Pel8> apLimitInfo<Pel8>::sType (std::numeric_limits<Pel8>::min(), 
//                                                          std::numeric_limits<Pel8>::max());
//
// We use
//   template<> apLimitInfo<Pel8> apLimitInfo<Pel8>::sType (0, UCHAR_MAX);


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


// *****************
// *               *
// *  apLimitInfo  *
// *               *
// *****************

// Basic unsigned types
template<> apLimitInfo<Pel8> apLimitInfo<Pel8>::sType (0, UCHAR_MAX);
template<> apLimitInfo<Pel16> apLimitInfo<Pel16>::sType (0, USHRT_MAX);
template<> apLimitInfo<Pel32s> apLimitInfo<Pel32s>::sType (INT_MIN, INT_MAX);
template<> apLimitInfo<Pel32> apLimitInfo<Pel32>::sType (0, UINT_MAX);

// Basic signed types
template<> apLimitInfo<char>  apLimitInfo<char>::sType (SCHAR_MIN, SCHAR_MAX);
template<> apLimitInfo<short> apLimitInfo<short>::sType (SHRT_MIN, SHRT_MAX);

// Basic float types
template<> apLimitInfo<float>  apLimitInfo<float>::sType (FLT_MIN, FLT_MAX);
template<> apLimitInfo<double> apLimitInfo<double>::sType (DBL_MIN, DBL_MAX);

// Pel types
template<> apLimitInfo<apClampedPel8> apLimitInfo<apClampedPel8>::sType (0, UCHAR_MAX);
template<> apLimitInfo<apClampedPel16> apLimitInfo<apClampedPel16>::sType (0, USHRT_MAX);
template<> apLimitInfo<apClampedPel32s> apLimitInfo<apClampedPel32s>::sType (INT_MIN, INT_MAX);



// RGB
template<> apLimitInfo<apRGB> apLimitInfo<apRGB>::sType (apRGB(0), apRGB(UCHAR_MAX));
template<> apLimitInfo<apRGBPel32> apLimitInfo<apRGBPel32>::sType (apRGBPel32(0), apRGBPel32(UINT_MAX));

template<> apLimitInfo<apRGBPel32s> apLimitInfo<apRGBPel32s>::sType (apRGBPel32s(INT_MIN), apRGBPel32s(INT_MAX));


template<> Pel8 apLimit<Pel8, Pel32s> (const Pel32s& src)
{ return static_cast<Pel8> (src < 0 ? 0 : (src > 255 ? 255 : src));}

template<> Pel8 apLimit<Pel8, Pel8> (const Pel8& src)
{ return src;}

template<> Pel32s apLimit<Pel32s, Pel32s> (const Pel32s& src)
{ return src;}

template<> Pel32s apLimit<Pel32s, Pel32> (const Pel32& src)
{ return (src > INT_MAX) ? INT_MAX : src;}


template<> apClampedPel8 apLimit<apClampedPel8, apClampedPel32s> (const apClampedPel32s& src)
{ return static_cast<Pel8> (src.val < 0 ? 0 : (src.val > 255 ? 255 : src.val));}

template<> apClampedPel8 apLimit<apClampedPel8, apClampedPel8> (const apClampedPel8& src)
{ return src;}

template<> apClampedPel32s apLimit<apClampedPel32s, apClampedPel32s> (const apClampedPel32s& src)
{ return src;}


// This specialization of apLimit() will efficiently handle RGB values.
// It also prevents us from having to worry about what operator<
// means for an RGB value.
template<> apRGB apLimit<apRGB, apRGBPel32s> (const apRGBPel32s& src)
{
  apRGB dst;
  dst.red   = static_cast<Pel8> (src.red   < 0 ? 0 : (src.red   > 255 ? 255 : src.red));
  dst.green = static_cast<Pel8> (src.green < 0 ? 0 : (src.green > 255 ? 255 : src.green));
  dst.blue  = static_cast<Pel8> (src.blue  < 0 ? 0 : (src.blue  > 255 ? 255 : src.blue));
  return dst;
}

template<> apRGB apLimit<apRGB, apRGB> (const apRGB& src)
{ return src;}

template<> apRGBPel32s apLimit<apRGBPel32s, apRGBPel32s> (const apRGBPel32s& src)
{ return src;}



// *********************
// *                   *
// *  Specializations  *
// *                   *
// *********************

template<>
std::ostream& operator<< (std::ostream& stream, const apClampedTmpl<Pel8>& pel)
{
  stream << (Pel32s)pel.val;
  return stream;
}


template<>
std::ostream& operator<< (std::ostream& stream, const apRGBTmpl<Pel8>& rgb)
{
  stream << "(" << (Pel32s)rgb.red << "," << (Pel32s)rgb.green << "," << (Pel32s)rgb.blue << ")";
  return stream;
}


