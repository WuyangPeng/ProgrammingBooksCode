// widetools.cpp
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
// Wide (i.e. Unicode related) tools

#include "wideTools.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// *****************
// *               *
// *  apWideTools  *
// *               *
// *****************

apWideTools* apWideTools::sOnly_ = 0;

apWideTools& apWideTools::gOnly ()
{
  if (!sOnly_)
    sOnly_ = new apWideTools ();
  return *sOnly_;
}

apWideTools::apWideTools () : endian_ (eUnknownEndian)
{
  // Check our endian-ness
  endian_ = checkBOM (bom());
}


apWideTools::eBOM apWideTools::checkBOM (wchar_t value) const
{
  unsigned char* p = reinterpret_cast<unsigned char*> (&value);
  unsigned bom1      = *p++;
  unsigned char bom2 = *p;
  if (bom1 == 0xff && bom2 == 0xfe)
    return eLittleEndian;
  if (bom1 == 0xfe && bom2 == 0xff)
    return eBigEndian;

  return eUnknownEndian;
}

wchar_t apWideTools::swap (wchar_t value)
{
  return (((value >> 8) & 0x00ff) | 
          ((value << 8) & 0xff00));
}

unsigned long apWideTools::swap (unsigned long value)
{
  return (((value >>24) & 0x000000ff) | 
          ((value >> 8) & 0x0000ff00) | 
          ((value << 8) & 0x00ff0000) | 
          ((value <<24) & 0xff000000));
}


void apWideTools::swap (std::wstring& value)
{
  wchar_t* p = const_cast<wchar_t*> (value.c_str());
  for (unsigned int i=0; i<value.size(); i++)
    swap (*p++);
}
