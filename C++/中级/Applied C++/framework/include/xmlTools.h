#ifndef _xmltools_h_
#define _xmltools_h_

// xmltools.h
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
// XML tools
//
// This is not close to an XML parser. We did not want to be 
// dependent on an XML parser because we are in control of the
// format and a full parser can get pretty big.


#include "wideTools.h"

#include <string>


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345




// ****************
// *              *
// *  apXMLTools  *
// *              *
// ****************

struct apXMLElement
{
  std::wstring name;
  std::wstring value;
};


class apXMLTools
{
public:
  apXMLTools ();
  // Initialize our xml "parser" for generating xml

  apXMLTools (const std::wstring& xml, apWideTools::eBOM endian);
  // Initialize our "parser" with a string (which might be very big)
  // and the endian-ness of the data. If this endian does not match
  // the system value, the string is swapped in place before
  // processing.

  const std::wstring& xml    () const { return xml_;}
  apWideTools::eBOM   endian () const { return endian_;}

  apXMLElement parse ();
  // Parse and return the next element, which can consist of
  // many other elements. Removes the returned information
  // from xml_.

  std::wstring parseNextTag    ();
  // Returns the next element found, or "" if none

  std::wstring parseNextEndTag (std::wstring tag);
  // Returns the data between the specified element
  // Call after parseNextTag()

  std::wstring parseTag (const std::wstring& start, 
                         const std::wstring& stop);
  // Return the elements between the start and stop elements
  // The parsed data is removed from xml_.

  void writeResource (unsigned int id,
                      const std::wstring& str,
                      const std::wstring& notes);
  // Write this resource information to our internal string.
  // Header information is added if this is our first write.

  void writeTrailing ();
  // Write trailing information for our internal string. Called
  // after writeResource()

private:
  std::wstring      xml_;     // The string we are parsing (or writing)
  apWideTools::eBOM endian_;  // Endian-ness of the data


};


#endif // _xmltools_h_
