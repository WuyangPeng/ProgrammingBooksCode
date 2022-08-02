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
// Unit Test for resource manager

#include "unitTest.h"
#include "resourceMgr.h"
#include "xmlTools.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


UTFUNC(apstringresource)
{
  setDescription ("apStringResource test");

  apStringResource r1 (L"This is string 1", L"Notes");
  apStringResource r2 (L"This is string 2", L"Notes 2");
  apResourceMgr::gOnly().exportStrings ("test.xml");

  VERIFY (r1.string() == L"This is string 1");
  VERIFY (r2.string() == L"This is string 2");

  // Clear our list and make sure it's empty
  apResourceMgr::gOnly().reset ();
  VERIFY (r1.string() == L"");
  VERIFY (r2.string() == L"");

  // Import the list and make sure it is back
  apResourceMgr::gOnly().importStrings ("test.xml");
  VERIFY (r1.string() == L"This is string 1");
  VERIFY (r2.string() == L"This is string 2");

  // Test conversion operator, operator()
  std::wstring s1 = r1;
  std::wstring s2 = r2;
  VERIFY (s1 == L"This is string 1");
  VERIFY (s2 == L"This is string 2");

}

UTFUNC(xml1)
{
  setDescription ("xml test");
  std::wstring xml1 = L"<phrase><id>1</id><string>Hello World</string></phrase>";

  // Test parseNextTag()
  apXMLTools xmlTool1 (xml1, apWideTools::gOnly().endian());
  std::wstring tag = xmlTool1.parseNextTag ();
  VERIFY (tag == L"<phrase>");
  tag = xmlTool1.parseNextTag ();
  VERIFY (tag == L"<id>");
  tag = xmlTool1.parseNextTag ();
  VERIFY (tag == L"</id>");
  tag = xmlTool1.parseNextTag ();
  VERIFY (tag == L"<string>");
  tag = xmlTool1.parseNextTag ();
  VERIFY (tag == L"</string>");
  tag = xmlTool1.parseNextTag ();
  VERIFY (tag == L"</phrase>");
  tag = xmlTool1.parseNextTag ();
  VERIFY (tag == L"");

  // Test parse()
  apXMLTools xmlTool2 (xml1, apWideTools::gOnly().endian());
  apXMLElement element = xmlTool2.parse ();
  VERIFY (element.name == L"<phrase>");
  VERIFY (element.value == L"<id>1</id><string>Hello World</string>");
  
  element = xmlTool2.parse ();
  VERIFY (element.name == L"");
  VERIFY (element.value == L"");

  // Test parseTag () (used directly by the constructor)
  std::wstring xml2 = L"<?xml version=\"1.0\" encoding=\"UTF-16\" ?><!-- Comment --><resources><phrase><id>1</id><string>Hello World</string></phrase><!-- Another Comment --></resources>";
  apXMLTools xmlTool3 (xml2, apWideTools::gOnly().endian());
  VERIFY (xmlTool3.xml() == L"<resources><phrase><id>1</id><string>Hello World</string></phrase></resources>");
}

UTFUNC(write)
{
  setDescription ("write test");

  apXMLTools xml;
  xml.writeResource (101, L"String", L"Notes");
  xml.writeResource (202, L"String 2", L"Notes 2");
  xml.writeResource (303, L"String 3", L"");
  xml.writeTrailing ();

  std::wstring expected;
  expected.push_back (apWideTools::gOnly().bom());
  expected += L"<?xml version=\"1.0\" encoding=\"UTF-16\" ?>\n<resources>\n<phrase><id>101</id><string>String</string><notes>Notes</notes></phrase>\n<phrase><id>202</id><string>String 2</string><notes>Notes 2</notes></phrase>\n<phrase><id>303</id><string>String 3</string></phrase>\n</resources>\n";

  VERIFY (expected == xml.xml());
}



// Our main function is trivial
int main()
{
  bool state = apUnitTest::gOnly().run ();
  apUnitTest::gOnly().dumpResults (std::cout);
  return state;
}

