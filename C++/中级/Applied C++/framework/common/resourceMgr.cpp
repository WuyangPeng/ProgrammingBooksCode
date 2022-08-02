// resourceMgr.cpp
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
// General purpose string resource manager


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345

#include "resourceMgr.h"
#include "xmlTools.h"
#include "debugStream.h"



// **********************
// *                    *
// *  apStringResource  *
// *                    *
// **********************

std::string  apStringResource::sNullString;
std::wstring apStringResource::sNullWString;


apStringResource::apStringResource (const std::wstring& str, 
                                    const std::wstring& notes, 
                                    unsigned int id) : id_ (0)
{
  id_ = apResourceMgr::gOnly().addString (str, notes, id);
}

std::wstring apStringResource::string () const
{
  return apResourceMgr::gOnly().fetchString (id_);
}



// *******************
// *                 *
// *  apResourceMgr  *
// *                 *
// *******************

apResourceMgr* apResourceMgr::sOnly_ = 0;

apResourceMgr& apResourceMgr::gOnly ()
{
  if (!sOnly_) sOnly_ = new apResourceMgr ();
  return *sOnly_;
}

apResourceMgr::apResourceMgr () : id_ (0)
{}

void apResourceMgr::reset ()
{
  id_ = 0;
  strings_.clear ();
}


unsigned int apResourceMgr::hash (const std::wstring& str)
{
  // The hash must respect the endian-ness of the system. The
  // computation will be based on little-endian.
  const wchar_t* p = str.c_str();
  unsigned int id = 0;
  unsigned int i;

  if (apWideTools::gOnly().endian () == apWideTools::eBigEndian) {
    // Flip each character to make it look little Endian
    for (i=0; i<str.size(); i++)
      id = id * 797 + apWideTools::gOnly().swap (*p++);
  }
  else {
    for (i=0; i<str.size(); i++)
      id = id * 797 + (*p++);  // 797 is a nice prime number
  }

  return id;
}



unsigned int apResourceMgr::addString (const std::wstring& str, 
                                       const std::wstring& notes, 
                                       unsigned int id, bool overlay)
{
  if (id == 0) {
    id = hash (str);    // Get a hash value, look at each byte
  }

  if (id == 0)
    return id;  // null string. These can be safely ignored.

  // Ignore the string if overlay is false and the string already exists
  if (!overlay) {
    stringmap::iterator i = strings_.find (id);
    if (i != strings_.end()) {
      cdebug << "apResourceMgr::addString. duplicate string" << str.c_str() << std::endl;
      return id;
    }
  }

  apStringData data;
  data.str   = str;
  data.notes = notes;
  strings_[id] = data;

  return id;
}


std::wstring apResourceMgr::fetchString (unsigned int id)
{
  stringmap::iterator i = strings_.find (id);
  if (i == strings_.end())
    return L"";

  return (*i).second.str;
}


bool apResourceMgr::exportStrings (const std::string& file)
{
  apXMLTools xml;

  apStringData data;
  stringmap::iterator i;

  for (i=strings_.begin(); i != strings_.end(); i++) {
    data = i->second;
    xml.writeResource ((*i).first, data.str, data.notes);
  }
  // We don't write empty files
  if (xml.xml().empty())
    return false;

  xml.writeTrailing ();

  // NOTE:
  // At least on MSVC, std::wofstream had trouble writing a binary
  // string (the BOM). Write as a byte stream instead, using
  // appropriate casting.
  std::ofstream output (file.c_str(), std::ios_base::binary);
  const std::wstring& str = xml.xml();
  output.write (reinterpret_cast<const char*>(str.c_str()), 
                str.size()*sizeof(wchar_t));

  return true;
}

bool apResourceMgr::importStrings (const std::string& file)
{
  // NOTE:
  // At least on MSVC, std::wifstream had trouble reading a binary
  // string (the BOM). Read as a byte stream in a single operation.
  // We use C-style I/O operations so fseek/ftell will tell us the
  // size of the file. fread() reads the data into a wide string.

  // Get size of file
  FILE* fp = fopen (file.c_str(), "rb");
  if (fp == 0)
    return false;

  fseek (fp, 0L, SEEK_END);
  long size = ftell (fp) / 2; // Number of wide characters
  rewind (fp);

  // Read the data into a properly sized wide string
  std::wstring data;
  data.resize (size-1);
  wchar_t* p = const_cast<wchar_t*>(data.c_str());

  wchar_t bom;
  fread (&bom, sizeof(wchar_t), 1, fp);
  fread (p, sizeof(wchar_t), size, fp);
  fclose (fp);

  // This will call itself recursively until it is done
  parseElement (data, apWideTools::gOnly().checkBOM (bom));

  return true;
}

void apResourceMgr::parseElement (const std::wstring& data, apWideTools::eBOM endian)
{
  // Local, static copies of id, str, and notes are stored here and filled in when
  // the tags are received.
  static unsigned long id;
  static std::wstring  str;
  static std::wstring  notes;

  apXMLTools xml (data, endian);
  while (true) {
    apXMLElement element = xml.parse ();
    if (element.name.empty()) return;

    if (element.name == L"<resources>") {
      parseElement (element.value, endian);
    }
    else if (element.name == L"<phrase>") {
      parseElement (element.value, endian);
      // New values of id, str, notes should be available.
      addString (str, notes, id, true);
    }
    else if (element.name == L"<id>") {
      id = wcstol (element.value.c_str(), 0, 10);
    }
    else if (element.name == L"<string>") {
      str = element.value;
    }
    else if (element.name == L"<notes>") {
      notes = element.value;
    }
  }
}
