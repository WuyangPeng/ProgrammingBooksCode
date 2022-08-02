#ifndef _bstring_h_
#define _bstring_h_

// bstring.h
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
// Binary string class

#include "geometry.h"        // Our data types

#include <vector>
#include <string>


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345




// ***************
// *             *
// *  apBString  *
// *             *
// ***************


class apBString
{
public:
  apBString  ();
  ~apBString ();

  apBString            (const apBString& src);
  apBString& operator= (const apBString& src);

  size_t size () const { return string_.size();}
  const void*  base () const { return string_.c_str();}
  // Return pointer, and size of our data

  void rewind () { offset_ = 0;}
  // Reset our output pointer to the beginning

  bool eof () const { return offset_ >= string_.size();}
  // Return true if the stream is at the end

  bool match () const { return match_;}
  // Return true if all extraction resulted in a match between
  // the requested data type and the stored data type

  const std::string& str () const { return string_;}
  // Acess to our underlying string data


  // Insertion operators
  apBString& operator<< (Pel8   b);
  apBString& operator<< (Pel16  w);
  apBString& operator<< (Pel32s l);
  apBString& operator<< (Pel32  l);
  apBString& operator<< (float  f);
  apBString& operator<< (double d);
  apBString& operator<< (const std::string& s);
  apBString& operator<< (const apBString& bstr);

  void append (const void* data, unsigned int size);


  // Extraction operators
  apBString& operator>> (Pel8&   b);
  apBString& operator>> (Pel16&  w);
  apBString& operator>> (Pel32s& l);
  apBString& operator>> (Pel32&  l);
  apBString& operator>> (float&  f);
  apBString& operator>> (double& d);
  apBString& operator>> (std::string& s);
  apBString& operator>> (apBString& bstr);

  bool fetch (const void*& data, unsigned int& size);

  std::string dump ();
  // Ascii dump of data, from the current offset

private:
  std::string  string_;
  unsigned int offset_;
  bool         match_;

  enum eTypes {eNone=0, ePel8=1, ePel16=2, ePel32s=3, ePel32=4,
               eFloat=5, eDouble=6, eString=7, 
               eData=8, eBstr=9};
  // Supported datatypes. These values can never be changed but
  // more can be added

  apBString  (const void* data, unsigned int size);

  void add (eTypes type, const void* data, unsigned int size);
  // Add the specified data to our buffer

  const void* extract (eTypes& type);
  // Return a pointer to the next data type and return its type.
  // Returns null if you attempt to read past the end

  Pel8        readPel8   (const void* p);
  Pel16       readPel16  (const void* p);
  Pel32s      readPel32s (const void* p);
  Pel32       readPel32  (const void* p);
  float       readFloat  (const void* p);
  double      readDouble (const void* p);
  std::string readString (const void* p);
  // Read a particular quantity from our string.

  std::string dumpBString (unsigned int indent);
  // Text dump the contents from a single BString

};



#endif // _bstring_h_

