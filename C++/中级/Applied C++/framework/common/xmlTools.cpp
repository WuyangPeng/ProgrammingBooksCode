// xmltools.cpp
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

#include "xmlTools.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345




// ****************
// *              *
// *  apXMLTools  *
// *              *
// ****************

apXMLTools::apXMLTools () {}


apXMLTools::apXMLTools (const std::wstring& xml, 
                        apWideTools::eBOM endian)
  : xml_ (xml), endian_ (endian)
{
  // Swap the endian-ness of our string if necessary
  // This is done in place!!
  if (endian_ != apWideTools::gOnly().endian())
    apWideTools::gOnly().swap (xml_);

  // Remove any comments in the data
  std::wstring data;
  do {
    data = parseTag (L"<!--", L"-->");
  } while (!data.empty());

  // Remove any declarations in the data
  do {
    data = parseTag (L"<?", L"?>");
  } while (!data.empty());
}


std::wstring apXMLTools::parseNextTag ()
{
  // Find the start of the next tag
  size_t p1 = xml_.find (L"<");
  if (p1 == std::wstring::npos) {
    xml_ = L"";
    return L"";
  }

  // Find the end of the tag
  size_t p2 = xml_.find (L">", p1);
  if (p2 == std::wstring::npos) {
    xml_ = L"";
    return L"";
  }

  // Extract the tag and move the string
  std::wstring tag = xml_.substr (p1, p2-p1+1);
  xml_ = xml_.substr (p2+1);

  return tag;
}


std::wstring apXMLTools::parseNextEndTag (std::wstring tag)
{
  // Convert this to an end tab (i.e. <tag> => </tag>)
  tag.insert (1, L"/");

  // Fetch everything up to the tag
  size_t p1 = xml_.find (tag);
  if (p1 == std::wstring::npos) {
    xml_ = L"";
    return L"";
  }

  std::wstring contents = xml_.substr (0, p1);
  xml_ = xml_.substr (p1 + tag.size());

  return contents;
}


std::wstring apXMLTools::parseTag (const std::wstring& start, 
                                   const std::wstring& stop)
{
  // Find the start tag
  size_t p1 = xml_.find (start);
  if (p1 == std::wstring::npos)
    return L"";

  // Find the stop tag
  size_t p2 = xml_.find (stop);
  if (p2 == std::wstring::npos)
    return L"";

  std::wstring contents = xml_.substr (p1, p2+stop.size()-p1);
  std::wstring pre, post;
  if (p1 > 0)
    pre = xml_.substr (0, p1);
  post = xml_.substr (p2+stop.size());
  xml_ = pre + post;

  return contents;
}


apXMLElement apXMLTools::parse ()
{
  apXMLElement element;

  element.name  = parseNextTag ();
  if (!element.name.empty())
    element.value = parseNextEndTag (element.name);

  return element;
}


void apXMLTools::writeResource (unsigned int id,
                                const std::wstring& str,
                                const std::wstring& notes)
{
  if (xml_.empty()) {
    // Write the BOM
    xml_.push_back (apWideTools::gOnly().bom());
    xml_ += L"<?xml version=\"1.0\" encoding=\"UTF-16\" ?>\n<resources>\n";
  }

  char idstring[32];
  sprintf (idstring, "%d", id);
  std::wstring widstring;
  for (unsigned int i=0; i<strlen(idstring); i++)
    widstring += idstring[i];

  xml_ += L"<phrase><id>" + widstring;
  xml_ += L"</id><string>" + str + L"</string>";
  if (!notes.empty())
    xml_ += L"<notes>" + notes + L"</notes>";
  xml_ += L"</phrase>\n";
}

void apXMLTools::writeTrailing ()
{
  xml_ += L"</resources>\n";
}
