// objectMgr.cpp
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

#include "objectMgr.h"
#include "object.h"
#include "debugStream.h"

#include <iostream>


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// ***************** 
// *               *
// *  apObjectMgr  *
// *               *
// *****************

apObjectMgr* apObjectMgr::sOnly_ = 0;

apObjectMgr& apObjectMgr::gOnly ()
{
  if (!sOnly_)
    sOnly_ = new apObjectMgr;

  return *sOnly_;
}


apObjectMgr::apObjectMgr ()
{}


void apObjectMgr::add (const std::string& name, apObjectInfoBase* obj)
{
  mapping_[name] = obj;
}

apObjectInfoBase* apObjectMgr::find (const std::string& name)
{
  OBJMAP::iterator i = mapping_.find (name);
  if (i == mapping_.end())
    return 0;
  return i->second;
}


void apObjectMgr::debugMessage (const std::string& header,
                                const std::string& msg)
{
  cdebug << header.c_str() << msg.c_str() << std::endl;
}


std::string apObjectMgr::dump ()
{
  std::string str;
  char buffer[16];

  OBJMAP::iterator i;
  for (i=mapping_.begin(); i != mapping_.end(); ++i) {
    sprintf (buffer, " %d:  ", i->second->debug());
    str += i->first + buffer;
    str += i->second->dump ();
    str += "\n";
  }

  return str;
}

std::string apObjectMgr::process (const std::string& command)
{
  std::string result;
  OBJMAP::iterator i;
  for (i=mapping_.begin(); i != mapping_.end(); ++i) {
    result += i->second->process (command);
    result += " ";
  }
  return result;
}
