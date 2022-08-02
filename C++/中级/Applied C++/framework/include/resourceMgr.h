#ifndef _resourceMgr_h_
#define _resourceMgr_h_

// resourceMgr.h
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


//  Notes:
//
// These objects allow the developer to localize strings
// in a flexible way. It is not applicable for a very large project
// that has many strings, but is ideal for small to medium
// applications.
//
// A string resource consists of an id (unsigned long) and a phrase
// (std::wstring). At any given time, a single language is active and
// a request for a phrase, by id, will return the current phrase.
// An optional notes field can be used to specify additional
// information. These notes are hidden from the user but available to
// a translator or whoever maintains the resources.
//
// Method 1:
//
// The first way to use the resource manager is to specify a file to
// load with one or more sets of localized strings. This file format
// uses Unicode (utf-16) and XML. We decided not to use a general 
// XML parser because these can get large and some users will already
// have an XML parser embedded in their application. Only a few tags
// are supported.
//
// Method 2:
//
// The user can embed apStringResource objects directly in the code.
// Each entry the user makes will create a global variable which 
// contains a phrase. If you have an application with a moderate
// number of strings, this can be a nice way to get the best of
// both worlds. You will be able to access your strings by a
// variable name, and you will have the string itself stored in
// your code. You should put this string in your native language.
// In our case, we would use English strings.
//
// You will use method 1 to overlay other language strings and
// replace the strings embedded in your code. During development
// you can export a list of used strings in native format. This file
// can then be translated into other languages.
//
// You can assign your own string ids, or the system will use a
// simple hash function to assign one to the string. This means that
// if you change your embedded strings, the id will change. The
// system will report any invalid ids when the file is read so this
// problem can be detected during development and testing.
//
// XML Layout
//   - File starts with a BOM (Byte Order Mark, 0xfeff) to determine
//     the endian-ness.
//   - <?...?> elements are ignored. If you produce an XML file from
//     this object, <?xml version="1.0" encoding="UTF16" ?> will be
//     written immediately after the BOM.
//   - <!--...--> comments are ignored.
//   - <resources>...</resources>
//       Surrounds all <phrase> instances. One per file.
//   - <phrase>...</phrase>
//       A single phrase. Consists of <id>, <string>, and <notes>
//   - <id>id</id>
//       Specifies the id for a phrase
//   - <string>string</string>
//       The string that is associated with this phrase.
//   - <notes>notes</notes>
//       Optional notes which can act as guidelines for translators

#include "wideTools.h"

#include <string>
#include <map>


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// ******************
// *                *
// *  apStringData  *
// *                *
// ******************

struct apStringData
{
  std::wstring str;     // Current string value
  std::wstring notes;   // Optional notes describing value
};



// **********************
// *                    *
// *  apStringResource  *
// *                    *
// **********************
//
// An apStringResource allows a string to be embedded in an
// object and later replaced with an alternate string.

class apStringResource
{
public:  
  static std::string  sNullString;
  static std::wstring sNullWString;

  apStringResource (const std::wstring& str, 
                    const std::wstring& notes=sNullWString, 
                    unsigned int id=0);
  // The given string is added to a global string list. Multiple
  // instances of the same string is only supported if the user
  // specifies the id.
  //
  //  str    The string to be managed
  //  notes  Optional notes to translators and maintainers of strings
  //  id     Optional unique id. If you do not specify one, the
  //         object will assign one based on the hash of the string.

  std::wstring string () const;
  operator std::wstring () const { return string ();}
  // Return the string. This may be the string set by the user or one
  // from a different language.

  unsigned int id () const { return id_;}

private:
  unsigned int id_;        // Id of this string

  apStringResource (const apStringResource&) {}
  apStringResource& operator= (const apStringResource&) { return *this;}
  // Prevent copy and assignment
};




// *******************
// *                 *
// *  apResourceMgr  *
// *                 *
// *******************

typedef std::map<unsigned int /*id*/, apStringData /*data*/>    stringmap;

class apResourceMgr
{
public:
  static apResourceMgr& gOnly ();  // Singleton object

  void reset ();
  // Re-initialize the element;

  const stringmap& strings () const { return strings_;}
  // Allow users access to the string map for exporting data

  bool exportStrings (const std::string& file);
  bool importStrings (const std::string& file);
  // Export/import the string list. Export is mainly for generating
  // a list of strings to localize. Import can be used to import the
  // localized list at runtime. The strings will overlay any strings
  // stored. To start from a clean slate, call reset() first.

  unsigned int addString (const std::wstring& str, 
                          const std::wstring& notes, 
                          unsigned int id=0, bool overlay=false);
  // Add a native string to our string list. If overlay is false,
  // a duplicate id will be ignored and the string will not be 
  // replaced.

  std::wstring fetchString (unsigned int id);
  // Given an id, fetch the string for the current language. If not
  // available, the default string will be fetched.

private:
  static apResourceMgr* sOnly_;

  unsigned int id_;      // Language id in use
  stringmap    strings_; // List of all managed strings

  unsigned int hash (const std::wstring& str);
  // Compute a simple hash value from a wide string. This is
  // platform independent.

  void parseElement (const std::wstring& data, apWideTools::eBOM endian);
  // Called from importStrings to parse an xml document piece by piece.
  // This function is recursively called to handle all nested elements.

  apResourceMgr ();
};




#endif // _resourceMgr_h_
