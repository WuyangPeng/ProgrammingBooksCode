#ifndef _imageStorageTmpl_h_
#define _imageStorageTmpl_h_

// imageStorageTmpl.h
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
// Image storage template class

#include "imageStorage.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


// ************************
// *                      *
// *  apImageStorageTmpl  *
// *                      *
// ************************
//
// apImageStorageTmpl<> is a template handle class and points to
// a specific apRectStorageRep<> object.

template<class T>
class apStorageRepTmpl;  // Forward declaration


template<class T>
class apImageStorageTmpl : public apImageStorage
{
public:
  apImageStorageTmpl () {}
  apImageStorageTmpl (unsigned int width, unsigned int height);

  virtual ~apImageStorageTmpl () {}

  const apStorageRepTmpl<T>* operator -> () const 
  { return static_cast<apStorageRepTmpl<T>*> (storage_);}
  apStorageRepTmpl<T>*       operator -> ()
  { return static_cast<apStorageRepTmpl<T>*> (storage_);}
  // Allow access to the rep object. These casts are safe.
};



// ******************
// *                *
// *  apStorageRep  *
// *                *
// ******************
//
// apRectStorageRep is the template rep class for 
// rectangular image storage.

template<class T>
class apStorageRepTmpl : public apStorageRep
{
  friend class apImageStorageTmpl<T>;
public:
  apStorageRepTmpl () {}
  apStorageRepTmpl (unsigned int width, unsigned int height)
    : apStorageRep (width, height, sizeof (T)) {}

  virtual ~apStorageRepTmpl () {}

  const T* base () const
  { return reinterpret_cast<const T*> (storage_.data());}
  T* base ()
  { return reinterpret_cast<T*> (storage_.data());}

protected:
};



// *******************************
// *                             *
// *  apImageStorageTmpl inline  *
// *                             *
// *******************************

template<class T>
apImageStorageTmpl<T>::apImageStorageTmpl (unsigned int width, unsigned int height)
: apImageStorage (new apStorageRepTmpl<T> (width, height))
{}


#endif // _imageStorageTmpl_h_
