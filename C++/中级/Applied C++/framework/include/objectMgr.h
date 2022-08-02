#ifndef _objectMgr_h_
#define _objectMgr_h_

// objectMgr.h
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
// Objectging template object

//Disable the warning regarding long template names
#ifdef WIN32
#pragma warning(disable:4786)
#pragma warning(disable:4503)
#endif

#include "debugging.h"

#include <map>
#include <string>



// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// ***************** 
// *               *
// *  apObjectMgr  *
// *               *
// *****************

class apObjectInfoBase; // Forward declaration


class apObjectMgr
{
 public:
  typedef std::map<std::string, apObjectInfoBase*> OBJMAP;

  static apObjectMgr& gOnly ();
  //singleton object

  std::string dump ();
  // Text dump of all objects in use

  void debugMessage (const std::string& header,
                     const std::string& msg);
  // Generate a debug message to cdebug

  void add (const std::string& name, apObjectInfoBase* obj);
  // Add an object to our list

  apObjectInfoBase* find (const std::string& name);
  // Returns a pointer to a specific apObjectInfoBase, or 0

  std::string process (const std::string& command);
  // Send the command to all object instances

private:
  static apObjectMgr* sOnly_;
  apObjectMgr ();

  OBJMAP mapping_;  // List of all managed classes
};


#endif // _objectMgr_h_
