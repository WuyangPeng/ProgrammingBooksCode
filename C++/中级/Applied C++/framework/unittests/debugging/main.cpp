// main.cpp
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
// Unit Test for debugging class

//Disable the warning regarding long template names
#ifdef WIN32
#pragma warning(disable:4786)
#pragma warning(disable:4503)
#endif


#include "unitTest.h"
#include "object.h"
#include "debugStream.h"
#include "debugging.h"

#include <iostream>
#include <fstream>

// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



#define NODEBUG 1

UTFUNC(debug)
{
  setDescription ("Simple apDebugging tests");

  debugstream.sink (apDebugSinkConsole::sOnly);
  apDebugSinkConsole::sOnly.showHeader (true);

  cdebug << "This is output to the debug string" << std::endl;
  cdebug << "This is line 2";

  apDebugSinkFile::sOnly.setFile ("test.txt");
  debugstream.sink (apDebugSinkFile::sOnly);
  apDebugSinkFile::sOnly.showHeader (true);
  cdebug << "This is output to the debug string" << std::endl;
  cdebug << "This is line 4";

  debugstream.sink (apDebugSinkConsole::sOnly);

  int count = 0;
  apDebug::gOnly().reset ();
  DEBUGGING(0, count++;)
  DEBUGGING(1, count++;)
  VERIFY (count == 0);

  count = 0;
  apDebug::gOnly().debug (0, true);
  DEBUGGING(0, count++;)
  DEBUGGING(1, count++;)
  VERIFY (count == 1);

  count = 0;
  apDebug::gOnly().debug (1, true);
  DEBUGGING(0, count++;)
  DEBUGGING(1, count++;)
  VERIFY (count == 2);

  count = 0;
  apDebug::gOnly().debug (2, true);
  DEBUGGING(1, {
    count++;
    count++;
  })
  DEBUGGING(2, {
    count++;
    count++;
  })
  VERIFY (count == 4);


}

// This test only runs on win32 platforms
#ifdef WIN32
#include <windows.h>

// Output our data to the windows debug console
class apDebugSinkWindows : public apDebugSinkConsole
{
public:
  static apDebugSinkWindows sOnly;
  virtual void display (const std::string& str);
};

apDebugSinkWindows apDebugSinkWindows::sOnly = apDebugSinkWindows ();

void apDebugSinkWindows::display (const std::string& str)
{
  OutputDebugString (str.c_str());
}

UTFUNC(windows)
{
  setDescription ("OutputDebugString testing");

  debugstream.sink (apDebugSinkWindows::sOnly);
  apDebugSinkWindows::sOnly.showHeader (true);

  cdebug << "This is output to the debug string" << std::endl;
  cdebug << "This is line 2";

  VERIFY (true);
}
#endif

UTFUNC(directlySink)
{
  for (int i=0; i<10; i++)
    apDebugSinkConsole::sOnly.write ('0' + i);
  apDebugSinkConsole::sOnly.write ('\n');
}

// Not strictly a unittest, but show that I can redirect
UTFUNC(streamredirect)
{
  std::cout << "This should be written to the console" << std::endl;

  std::ofstream file ("redirect.txt");
  std::streambuf* oldbuf = std::cout.rdbuf (); // Save
  std::cout.rdbuf (file.rdbuf());

  std::cout << "This should be written to the file" << std::endl;

  std::cout.rdbuf (oldbuf); // Restore
  std::cout << "This should be written to the console" << std::endl;

}

UTFUNC(bookexample)
{
cdebug << "This line goes to our null sink" << std::endl;

// Start like power-up
apDebugSinkConsole::sOnly.showHeader (false);
apDebugSinkFile::sOnly.showHeader (false);

debugstream.sink (apDebugSinkConsole::sOnly);
cdebug << "This line goes to std::cout" << std::endl;

apDebugSinkConsole::sOnly.showHeader (true);
cdebug << "Also to std::cout, but with a timestamp" << std::endl;

apDebugSinkFile::sOnly.setFile ("test.txt");
debugstream.sink (apDebugSinkFile::sOnly);
cdebug << "This line goes to test.txt" << std::endl;

apDebugSinkFile::sOnly.showHeader (true);
cdebug << "Also to test.txt, but with a timestamp" << std::endl;
}

UTFUNC(bookexample2)
{
DEBUGGING(1, cdebug << "This is level 1" << std::endl; );
DEBUGGING(2, {
  for (int i=0; i<10; i++)
    cdebug << "This is line " << i << std::endl;
});

DEBUGGING(2,
  for (int i=0; i<10; i++)
    cdebug << "Again, this is line " << i << std::endl;
);

}

UTFUNC(bookexample3)
{
 debugstream.sink (apDebugSinkConsole::sOnly);
 apDebug::gOnly().reset ();

 cdebug << "set bit 0" << std::endl;
  apDebug::gOnly().set (0);
DEBUGGING(0, cdebug << "This is bit 0" << std::endl; );
DEBUGGING(1, {
  for (int i=0; i<10; i++)
    cdebug << "bit 1This is line " << i << std::endl;
});

  cdebug << "set bit 1" << std::endl;
  apDebug::gOnly().clear (0);
  apDebug::gOnly().set (1);
DEBUGGING(0, cdebug << "This is bit 0" << std::endl; );
DEBUGGING(1, {
  for (int i=0; i<10; i++)
    cdebug << "bit 1This is line " << i << std::endl;
});
}


class apTest : public apObject<apTest>
{
public:
  apTest ()  {}
  ~apTest () {}
  void test () {
    debugMessage ("Hello");
  }
  virtual std::string process (const std::string& command)
  {
    std::cout << "process: " << command.c_str() << std::endl;
    return command;
  }

};


UTFUNC(ctor)
{
  setDescription ("Constructor and simple accessor tests");

  debugstream.sink (apDebugSinkConsole::sOnly);

  apTest test;
  test.test ();

  apTest testb, testc;

  std::cout << "Map: " << apObjectMgr::gOnly().dump().c_str() << std::endl;

  // Try the list command
  std::string list = apObjectInfo<apTest>::gOnly().process ("list");
  std::cout << "list command: " << list << std::endl;

  // Try the execute command
  std::string result = apObjectInfo<apTest>::gOnly().process ("execute my command");
  std::cout << "execute command: " << result << std::endl;

  // Try the to command. We'll call the first instance
  apToken parsed = apStringTools::sParse (list);
  std::string cmd = "to " + parsed.parsed + " my command";
  result = apObjectInfo<apTest>::gOnly().process (cmd);
  std::cout << "'" << cmd.c_str() << "' comand: " << result << std::endl;

  VERIFY (true);
}


#define CREATEINSTANCECLASS(classname)                        \
class apObjectInfo_##classname : public apObjectInfoBase      \
  {                                                           \
  public:                                                     \
    static apObjectInfo_##classname gOnly ();                 \
    virtual std::string process (const std::string& command); \
    virtual std::string dump ();                              \
  private:                                                    \
    static apObjectInfo_##classname* sOnly_;                  \
    std::string name_;                                        \
    apObjectInfo_##classname ();                              \
  };


// Our main function is trivial
int main()
{
  bool state = apUnitTest::gOnly().run ();
  apUnitTest::gOnly().dumpResults (std::cout);
  return state;
}

