// io.cpp
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
// Image I/O

#include "delegates/io.h"

#include <sstream>


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


// *******************
// *                 *
// *  apImageIOBase  *
// *                 *
// *******************
//
// Base class for all apImage storage delegates.

apImageIOBase::apImageIOBase ()   {}
apImageIOBase::~apImageIOBase ()  {}

apDelegateParams apImageIOBase::sNoParams;


// ***************************
// *                         *
// *  apImageIODelegateList  *
// *                         *
// ***************************

apImageIODelegateList* apImageIODelegateList::sOnly_ = 0;

apImageIODelegateList& apImageIODelegateList::gOnly ()
{
  if (!sOnly_) sOnly_ = new apImageIODelegateList ();
  return *sOnly_;
}

apImageIODelegateList::apImageIODelegateList ()
{

}


apImageIOBase* apImageIODelegateList::getDelegate (const std::string& type)
{
  return map_[type];
}

void apImageIODelegateList::setDelegate (const std::string& type, apImageIOBase* object)
{
  map_[type] = object;
}

apImageIOBase* apImageIODelegateList::findDelegate (const std::string& filename)
{
  iterator i;
  for (i=map_.begin(); i!=map_.end(); i++) {
    if (i->second->info(filename).isDelegate)
      return i->second;
  }

  return 0;
}

