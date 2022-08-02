#ifndef _widetools_h_
#define _widetools_h_

// widetools.h
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

#include <string>


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345




// *****************
// *               *
// *  apWideTools  *
// *               *
// *****************


class apWideTools
{
public:
  static apWideTools& gOnly ();

  enum eBOM { eUnknownEndian=0, eLittleEndian=1, eBigEndian=2};

  wchar_t bom () const { return 0xfeff;}
  // The byte-order mark to determine endian-ness

  eBOM endian () const { return endian_;}
  // Returns endian-ness of the system

  eBOM checkBOM (wchar_t value) const;
  // Checks the value to see if it is little or big endian.
  // little endian = (0xff 0xfe). Big endian = (0xfe 0xff)
  // The BOM is 0xfeff and is written to the start of files

  wchar_t       swap (wchar_t value);
  unsigned long swap (unsigned long value);
  void          swap (std::wstring& value);  // Done in place
  // Swap endian-ness of a value, or string

private:
  static apWideTools* sOnly_;

  eBOM endian_;          // Our endian type

  apWideTools ();
};


#endif // _widetools_h_
