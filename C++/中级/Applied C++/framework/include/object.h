#ifndef _object_h_
#define _object_h_

// object.h
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
//  Base class to add debugging to user objects

//Disable the warning regarding long template names
#ifdef WIN32
#pragma warning(disable:4786)
#pragma warning(disable:4503)
#endif


#include "objectMgr.h"
#include "stringTools.h"

#include <string>
#include <map>
#include <iostream>
#include <typeinfo>

#include <stdio.h> // sprintf()


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// **********************
// *                    *
// *  apObjectInfoBase  *
// *                    *
// **********************
//
// Base class for apObjectInfo. A single map<> template is used
// to prevent a proliferation of unnecessary template objects.


class apObjectInfoBase
{
public:
  typedef std::map<void*, char> INSTANCEMAP;

  apObjectInfoBase () : debug_ (0) {}

  int  debug ()      { return debug_;}
  void debug (int d) { debug_ = d;}
  // Get/set the debugging level for this object

  bool isDebug (int level) { return debug_ >= level;}
  // Return true if debugging is enabled for this object

  void addInstance    (void* obj) { mapping_[obj] = 1;}
  void removeInstance (void* obj) { mapping_.erase (obj);}
  // Add/remove an object from our instance list

  virtual std::string process (const std::string& command) = 0;
  // Command processor. apObjectMgr can send a command
  // string and expects a response string in return.

  virtual std::string dump () = 0;
  // Allow derived classes to produce a list of managed objects
  // This is abstract because our derived class has the
  // implementation, but apObjectMgr has a pointer to a
  // apObjectInfoBase object.

protected:
  int         debug_;   // Debug level for this object
  INSTANCEMAP mapping_; // List of all current objects
};



// ******************
// *                *
// *  apObjectInfo  *
// *                *
// ******************
//
// A single apObjectInfo class is created for each apObject class
// (if configured). This object contains debug information for
// the local class as well as hooks itself onto the apObjectMgr
// list.

template <class T>
class apObjectInfo : public apObjectInfoBase
{
public:
  static apObjectInfo<T>& gOnly ();
  //singleton object

  const std::string& name () const { return name_;}
  // Return our object name. This might be as simple
  // as what typeid() returns, but it also can be
  // modified as necessary.

  virtual std::string process (const std::string& command);
  // Process the debugging command and return results.
  // Strings are used to keep the interface generic.
  // The base class version ignores everything

  virtual std::string dump ();
  // Produce a space separated list of object instances

private:
  static apObjectInfo<T>* sOnly_;
  std::string name_;

  apObjectInfo ();
};


template <class T>
apObjectInfo<T>* apObjectInfo<T>::sOnly_ = 0;

template <class T>
apObjectInfo<T>& apObjectInfo<T>::gOnly ()
{
  if (!sOnly_)
    sOnly_ = new apObjectInfo;

  return *sOnly_;
}


template <class T>
apObjectInfo<T>::apObjectInfo ()
{
  // Setup our object name. This is compiler and platform
  // dependent so this function can be modified to create
  // a more uniform string
  name_ = typeid(T).name();

  // Add this class to our apObjectMgr list
  apObjectMgr::gOnly().add (name_, this);
}



template <class T>
std::string apObjectInfo<T>::dump ()
{
  std::string str;
  char buffer[16];

  INSTANCEMAP::iterator i;
  for (i=mapping_.begin(); i != mapping_.end(); i++) {
    sprintf (buffer, " %d", i->first);
    str += buffer;
  }

  return str;
}


// Our original stub version
// template <class T>
// std::string apObjectInfo<T>::process (const std::string& command)
// {
//   //TODO
//   return "";
// }


template <class T>
std::string apObjectInfo<T>::process (const std::string& command)
{
  // Parse our command
  apToken token = apStringTools::sParse (command);

  // Decide what to do with it. With only a few commands just use
  // if statements.
  INSTANCEMAP::iterator i;
  std::string result;       // Our result string
  char buffer[16];          // Buffer for sprintf()

  if (token.parsed == "list") {
    // "list" Return a space separated list of all instances (by address)
    for (i=mapping_.begin(); i != mapping_.end(); i++) {
      sprintf (buffer, "%x ", i->first);
      result += buffer;
    }
  }
  else if (token.parsed == "execute") {
    // "execute <command>" Send the remainder of the string to all instances
    for (i=mapping_.begin(); i != mapping_.end(); i++) {
      T* obj = reinterpret_cast<T*>(i->first);
      result += obj->process (token.remainder);
      result += " ";
    }
  }
  else if (token.parsed == "to") {
    // "to <instance> <command>" Send the remainder of the string to a
    // specific instance. Our match will be by string because the list
    // command returns a list of strings
    apToken instance = apStringTools::sParse (token.remainder);
    for (i=mapping_.begin(); i != mapping_.end(); i++) {
      sprintf (buffer, "%x", i->first);
      if (instance.parsed == buffer) {
        T* obj = reinterpret_cast<T*>(i->first);
        result += obj->process (instance.remainder);
      }
    }
  }
  else {
    // Unknown command. Don't do anything
  }

  return result;
}



// ************** 
// *            *
// *  apObject  *
// *            *
// **************
//
// Options:
//   eNone          No options
//   eTrackInstance Track this object instance (default)

template <class T>
class apObject
{
public:
  enum eOptions {eNone=0, eTrackInstance=1};

  apObject (eOptions options = eTrackInstance);
  // Object construction with optional arguments

  virtual ~apObject ();

  int  debug ()      { return apObjectInfo<T>::gOnly().debug();}
  void debug (int d) { apObjectInfo<T>::gOnly().debug(d);}
  // Get/set the debugging level for this object

  bool isDebug (int level)
  { return apObjectInfo<T>::gOnly().isDebug(level);}
  // Return true if debugging is enabled for this level

  void debugMessage (const std::string& msg);
  // Output the debugMessage.

  virtual std::string header () const;
  // The header string printed before any debugging messages

  virtual std::string process (const std::string& command);
  // Process a debugging command and return results.
  // Strings are used to keep the interface generic.
  // The base class version ignores everything
};



template <class T> apObject<T>::apObject (eOptions options)
{
  // Add ourself to our instance list if enabled
  if (options & eTrackInstance) {
    apObjectInfo<T>::gOnly().addInstance (this);
  }
}

template <class T> apObject<T>::~apObject ()
{
  apObjectInfo<T>::gOnly().removeInstance (this);
}


template <class T>
void apObject<T>::debugMessage (const std::string& msg)
{
  apObjectMgr::gOnly().debugMessage (header(), msg);
}


template <class T>
std::string apObject<T>::header () const
{
  const T* obj = static_cast<const T*> (this);

  char buffer[32];
  sprintf (buffer, " (0x%0x): ", obj);
  std::string h = apObjectInfo<T>::gOnly().name();
  h += buffer;
  return h;
}


template <class T>
std::string apObject<T>::process (const std::string& /*command*/)
{
  // The base class ignores all commands
  return "";
}


#endif // _object_h_
