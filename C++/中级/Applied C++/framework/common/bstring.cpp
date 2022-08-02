// bstring.cpp
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

#include "bstring.h"

// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


#include <stdio.h>  // For sprintf()

// ***************
// *             *
// *  apBString  *
// *             *
// ***************

apBString::apBString  () : offset_ (0), match_ (true) {}
apBString::~apBString () {}

apBString::apBString (const apBString& src) 
: offset_ (src.offset_), match_ (src.match_), 
  string_ (src.string_)
{}

apBString::apBString  (const void* data, unsigned int size)
: offset_ (0), match_ (true)
{
  string_.append (reinterpret_cast<const char*>(data), size);
}


apBString& apBString::operator= (const apBString& src)
{
  if (this != &src) {
    offset_ = src.offset_;
    match_  = src.match_;
    string_ = src.string_;
  }

  return *this;
}


void apBString::add (eTypes type, const void* data, unsigned int size)
{
  // Append the type
  Pel8 t = static_cast<Pel8>(type);
  string_.append (reinterpret_cast<char*>(&t), sizeof (Pel8));

  // Append the data
  string_.append (reinterpret_cast<const char*>(data), size);
}


const void* apBString::extract (eTypes& type)
{
  if (eof()) {
    type = eNone;
    return 0;
  }

  const Pel8* p = 
    reinterpret_cast<const Pel8*>(string_.c_str() + offset_);

  type = (eTypes) (*p++);

  int size = 0;
  switch (type) {
  case ePel8:
    size = sizeof (Pel8);
    break;
  case ePel16:
    size = sizeof (Pel16);
    break;
  case ePel32s:
    size = sizeof (Pel32s);
    break;
  case ePel32:
    size = sizeof (int);
    break;
  case eFloat:
    size = sizeof (float);
    break;
  case eDouble:
    size = sizeof (double);
    break;
  case eString:
  case eData:
  case eBstr:
    {
      Pel32s len;
      memcpy (&len, p, sizeof(Pel32s));
      size = sizeof (Pel32s) + len;
      break;
    }
  default:
    break;
  }

  offset_ += 1 + size;

  return p;
}


// Built-in insertion operators

apBString& apBString::operator<< (Pel8 b)
{
  add (ePel8, &b, sizeof (b));
  return *this;
}

apBString& apBString::operator<< (Pel16 w)
{
  add (ePel16, &w, sizeof (w));
  return *this;
}

apBString& apBString::operator<< (Pel32s l)
{
  add (ePel32s, &l, sizeof (l));
  return *this;
}

apBString& apBString::operator<< (Pel32 l)
{
  add (ePel32, &l, sizeof (l));
  return *this;
}

apBString& apBString::operator<< (float f)
{
  add (eFloat, &f, sizeof (f));
  return *this;
}

apBString& apBString::operator<< (double d)
{
  add (eDouble, &d, sizeof (d));
  return *this;
}

apBString& apBString::operator<< (const std::string& s)
{
  // Write a four byte length followed by the data
  size_t len = s.size ();
  add (eString, &len, sizeof (len));
  string_.append (reinterpret_cast<const char*>(s.c_str()), len);

  return *this;
}

apBString& apBString::operator<< (const apBString& bstr)
{
  // Extracting the string allows statements like
  // bstr << bstr;
  std::string s = bstr.string_;

  size_t len = s.size ();
  add (eBstr, &len, sizeof (len));
  string_.append (reinterpret_cast<const char*>(s.c_str()), len);

  return *this;
}

void apBString::append (const void* data, unsigned int size)
{
  add (eData, &size, sizeof (size));
  string_.append (reinterpret_cast<const char*>(data), size);
}




Pel8 apBString::readPel8 (const void* p)
{
  return *(reinterpret_cast<const Pel8*>(p));
}

Pel16 apBString::readPel16 (const void* p)
{
  Pel16 value;
  memcpy (&value, p, sizeof(Pel16));
  return value;
}
Pel32s apBString::readPel32s (const void* p)
{
  Pel32s value;
  memcpy (&value, p, sizeof(Pel32s));
  return value;
}
Pel32 apBString::readPel32 (const void* p)
{
  Pel32 value;
  memcpy (&value, p, sizeof(Pel32));
  return value;
}
float apBString::readFloat (const void* p)
{
  float value;
  memcpy (&value, p, sizeof(float));
  return value;
}
double apBString::readDouble (const void* p)
{
  double value;
  memcpy (&value, p, sizeof(double));
  return value;
}
std::string apBString::readString (const void* p)
{
  Pel32 size = readPel32 (p);
  const char* str = reinterpret_cast<const char*>(p);
  str += sizeof (Pel32);

  return std::string (str, size);
}

// Built-in extraction operators

apBString& apBString::operator>> (Pel8& b)
{
  eTypes type;
  b = 0;

  bool match = false;
  const void* p = extract (type);
  if (p == 0) return *this;

  switch (type) {
  case ePel8:
    b = readPel8 (p);
    match = true;
    break;
  case ePel16:
    b = (Pel8) readPel16 (p);
    break;
  case ePel32s:
    b = (Pel8) readPel32s (p);
    break;
  case ePel32:
    b = (Pel8) readPel32 (p);
    break;
  case eFloat:
    b = (Pel8) readFloat (p);
    break;
  case eDouble:
    b = (Pel8) readDouble (p);
    break;
  case eString:
    b = (Pel8) atoi (readString(p).c_str());
    break;
  default:
    // Unsupported type. We don't have to do anything
    break;
  }

  match_ &= match;
  return *this;
}

apBString& apBString::operator>> (Pel16& w)
{
  eTypes type;
  w = 0;

  bool match = false;
  const void* p = extract (type);
  if (p == 0) return *this;

  switch (type) {
  case ePel8:
    w = readPel8 (p);
    break;
  case ePel16:
    w = readPel16 (p);
    match = true;
    break;
  case ePel32s:
    w = (Pel16) readPel32s (p);
    break;
  case ePel32:
    w = (Pel16) readPel32 (p);
    break;
  case eFloat:
    w = (Pel16) readFloat (p);
    break;
  case eDouble:
    w = (Pel16) readDouble (p);
    break;
  case eString:
    w = (Pel16) atoi (readString(p).c_str());
    break;
  default:
    // Unsupported type. We don't have to do anything
    break;
  }

  match_ &= match;
  return *this;
}

apBString& apBString::operator>> (Pel32s& l)
{
  eTypes type;
  l = 0;

  bool match = false;
  const void* p = extract (type);
  if (p == 0) return *this;

  switch (type) {
  case ePel8:
    l = readPel8 (p);
    break;
  case ePel16:
    l = readPel16 (p);
    break;
  case ePel32s:
    l = readPel32s (p);
    match = true;
    break;
  case ePel32:
    l = (Pel32s) readPel32 (p);
    match = true;
    break;
  case eFloat:
    l = (Pel32s) readFloat (p);
    break;
  case eDouble:
    l = (Pel32s) readDouble (p);
    break;
  case eString:
    l = (Pel32s) atoi (readString(p).c_str());
    break;
  default:
    // Unsupported type. We don't have to do anything
    break;
  }

  match_ &= match;
  return *this;
}

apBString& apBString::operator>> (Pel32& l)
{
  eTypes type;
  l = 0;

  bool match = false;
  const void* p = extract (type);
  if (p == 0) return *this;

  switch (type) {
  case ePel8:
    l = readPel8 (p);
    break;
  case ePel16:
    l = readPel16 (p);
    break;
  case ePel32s:
    l = (Pel32) readPel32s (p);
    match = true;
    break;
  case ePel32:
    l = readPel32 (p);
    match = true;
    break;
  case eFloat:
    l = (Pel32) readFloat (p);
    break;
  case eDouble:
    l = (Pel32) readDouble (p);
    break;
  case eString:
    l = (Pel32) atoi (readString(p).c_str());
    break;
  default:
    // Unsupported type. We don't have to do anything
    break;
  }

  match_ &= match;
  return *this;
}

apBString& apBString::operator>> (float& f)
{
  eTypes type;
  f = 0;

  bool match = false;
  const void* p = extract (type);
  if (p == 0) return *this;

  switch (type) {
  case ePel8:
    f = readPel8 (p);
    break;
  case ePel16:
    f = readPel16 (p);
    break;
  case ePel32s:
    f = static_cast<float>(readPel32s (p));
    break;
  case ePel32:
    f = static_cast<float>(readPel32 (p));
    break;
  case eFloat:
    f = readFloat (p);
    match = true;
    break;
  case eDouble:
    f = (float) readDouble (p);
    break;
  case eString:
    f = (float) atof (readString(p).c_str());
    break;
  default:
    // Unsupported type. We don't have to do anything
    break;
  }

  match_ &= match;
  return *this;
}

apBString& apBString::operator>> (double& d)
{
  eTypes type;
  d = 0;

  bool match = false;
  const void* p = extract (type);
  if (p == 0) return *this;

  switch (type) {
  case ePel8:
    d = readPel8 (p);
    break;
  case ePel16:
    d = readPel16 (p);
    break;
  case ePel32s:
    d = readPel32s (p);
    break;
  case ePel32:
    d = readPel32 (p);
    break;
  case eFloat:
    d = readFloat (p);
    break;
  case eDouble:
    d = readDouble (p);
    match = true;
    break;
  case eString:
    d = atof (readString(p).c_str());
    break;
  default:
    // Unsupported type. We don't have to do anything
    break;
  }

  match_ &= match;
  return *this;
}

apBString& apBString::operator>> (std::string& s)
{
  eTypes type;
  s = "";

  bool match = false;
  const void* p = extract (type);
  if (p == 0) return *this;

  char buffer[128];

  switch (type) {
  case ePel8:
    sprintf (buffer, "%d", readPel8 (p));
    s = buffer;
    break;
  case ePel16:
    sprintf (buffer, "%d", readPel16 (p));
    s = buffer;
    break;
  case ePel32s:
    sprintf (buffer, "%d", readPel32s (p));
    s = buffer;
    break;
  case ePel32:
    sprintf (buffer, "%d", readPel32 (p));
    s = buffer;
    break;
  case eFloat:
    sprintf (buffer, "%f", readFloat (p));
    s = buffer;
    break;
  case eDouble:
    sprintf (buffer, "%f", readDouble (p));
    s = buffer;
    match = true;
    break;
  case eString:
    s = readString(p);
    break;
  default:
    // Unsupported type. We don't have to do anything
    break;
  }

  match_ &= match;
  return *this;
}

apBString& apBString::operator>> (apBString& bstr)
{
  eTypes type;

  const void* p = extract (type);
  if (p == 0) {
    bstr = apBString ();
    return *this;
  }

  if (type == eBstr) {
    unsigned int size = readPel32s (p);
    bstr = apBString (reinterpret_cast<const char*>(p) + sizeof (size), size);
  }
  else
    match_ = false;

  return *this;
}

bool apBString::fetch (const void*& data, unsigned int& size)
{
  eTypes type;
  size = 0;

  const void* p = extract (type);
  if (p == 0) return false;

  if (type == eData) {
    size = readPel32s (p);
    data = reinterpret_cast<const char*>(p) + sizeof (size);
    return true;
  }

  match_ = false;
  return false;
}


std::string apBString::dump ()
{
  // save and restore our offset
  unsigned int offset = offset_;

  std::string str = dumpBString (0);
  offset_ = offset;

  return str;
}


std::string apBString::dumpBString (unsigned int indent)
{
  std::string str;
  eTypes      type;
  const void* p;

  char buffer[128];

  while ((p = extract (type)) != 0) {
    if (indent > 0)
      str += std::string (indent, ' ');

    switch (type) {
    case eNone:
      str += "None:";
      break;
    case ePel8:
      sprintf (buffer, "Pel8:   %d\n", readPel8  (p));
      str += buffer;
      break;
    case ePel16:
      sprintf (buffer, "Pel16:   %d\n", readPel16 (p));
      str += buffer;
      break;
    case ePel32s:
      sprintf (buffer, "Pel32s:   %d\n", readPel32s (p));
      str += buffer;
      break;
    case ePel32:
      sprintf (buffer, "int:   %d\n", readPel32 (p));
      str += buffer;
      break;
    case eFloat:
      sprintf (buffer, "float:  %f\n", readFloat (p));
      str += buffer;
      break;
    case eDouble:
      sprintf (buffer, "double: %f\n", readDouble (p));
      str += buffer;
      break;
    case eString:
      str += "string: " + readString(p) + "\n";
      break;
    case eData:
      {
        std::string s = readString (p);
        str += "data:   ";
        sprintf (buffer, "(%d): ", s.size());
        str += buffer;
        size_t len = s.size();
        if (len > 10) len = 10;
        for (unsigned int i=0; i<len; i++) {
          sprintf (buffer, "0x%02x ", s[i]);
          str += buffer;
        }
        if (s.size() > len)
          str += "...";
        str += "\n";
      }
      break;
    case eBstr:
      {
        str += "bstring:\n";
        apBString bstr;
        bstr.string_ = readString (p);
        str += bstr.dumpBString (indent+2);
        break;
      }
    default:
      str += "UNKNOWN: \n";
      break;
    }
  }

  return str;
}

