#ifndef _exception_h_
#define _exception_h_

// exception.h
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
//  Exception class for ap classes

#include <exception>
#include <stdexcept>

#include <string>

// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// *****************
// *               *
// *  apException  *
// *               *
// *****************
//
// The exception handling classes from the STL do what we want,
// so this is nothing more than a base class for any of our 
// derived exceptions. I have changed the constructor to take a
// std::string object, but this gets converted before calling
// std::exception.


class apException : public std::exception
{
public:
  apException (std::string name) throw()
    : std::exception (), name_ (name) {}

  virtual ~apException () throw () {}

  virtual const char* what () const throw()
  { return name_.c_str();}

protected:
  std::string name_;
};




// ************************
// *                      *
// *  Derived Exceptions  *
// *                      *
// ************************

class apBoundsException : public apException
{
public:
  apBoundsException (std::string name="") 
    : apException ("apBoundsException: " + name) {}
};


class apUnsupportedException : public apException
{
public:
  apUnsupportedException (std::string name="") 
    : apException ("apUnsupportedException: " + name) {}
};



#endif // _exception_h_
