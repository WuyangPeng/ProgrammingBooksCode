#ifndef _unittest_h_
#define _unittest_h_

// unittest.h
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
// Simple unit test framework.



// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345


#include <string>
#include <vector>
#include <iostream>

#include <time.h>


// ************************ 
// *                      *
// *  apUnitTestFunction  *
// *                      *
// ************************
//
// apUnitTestFunction is the base class for all unit test
// functions. The macros defined at the bottom of this file will
// construct objects derived from apUnitTestFunction.
//
// When you write a unit test function, it executes as a member
// or an object derived from apUnitTestFunction.  Useful 
// functions:
//
//   VERIFY(condition)       A macro wrapped around verify(). If
//                           condition resolves to false, the
//                           unit test will fail.
//   verifyFloat (d1,d2);    Verifies that d1= d2, within a
//                           small value delta.  If this 
//                           condition is false, the unit test 
//                           will fail.
//   VERIFYFLOAT(d1,d2);     Same as verifyFlot() to match the
//                           look of VERIFY().
//   addMessage (string);    Adds the string to our internal
//                           message string.
//
// You should call VERIFY() or VERIFYFLOAT() at least once in 
// each unit test function.  If you don't the result state of
// the function will be eUnknown.

class apUnitTestFunction
{
public:
  apUnitTestFunction (const std::string& name);

  enum eResult {eNotRun, eRunning, eUnknown, eSuccess, eFailure};
  // Each unit test has a result, even if the user never sets it

  const std::string& name         () const { return name_;}
  eResult            result       () const { return result_;}
  double             elapsed      () const { return elapsed_;}
  const std::string& message      () const { return message_;}
  const std::string& description  () const
  { return description_;}
  std::string        resultString () const;

  void setDescription (const std::string& s) { description_ = s;}
  // Set the description of this test function

  void run (bool verbose = false);
  // Run this unit test. Called by the unit test framework


protected:
  virtual void test() = 0;
  // All unit tests define this function to perform a single test

  bool verify (bool state, const std::string& message="");
  // Fails test if state is false. Used by VERIFY() macro

  bool verifyFloat (double d1, double d2);
  // Verifies d1=d2, within a value delta. Used by VERIFYFLOAT()

  void addMessage (const std::string& message);
  // Adds the message string to our messages

  bool         verbose_;     // true for verbose output

  eResult      result_;      // Result of this unit test
  std::string  name_;        // Unit test name (must be unique)
  std::string  description_; // Description of function
  std::string  message_;     // Message, usual a failure message
  double       elapsed_;     // Execution time, in seconds
};



// ****************
// *              *
// *  apUnitTest  *
// *              *
// ****************
//

class apUnitTest
{
public:
  static apUnitTest& gOnly ();
  // The only instance of this object we create

  bool run (bool verbose = false);
  // Run all the unit tests. Returns true if all tests are ok

  void dumpResults (std::ostream& out);
  // Dump results to specified stream

  int size () const { return static_cast<int>(tests_.size());}
  const apUnitTestFunction* retrieve (int index) const;
  // Retrieves the specific test, or NULL if invalid index


  void addTest (const std::string& name, apUnitTestFunction* test);
  // Used by our macro to add another unit test

private:
  apUnitTest ();  // We will only have one instance, gOnly()

  static apUnitTest* sOnly_;  // Points to our only instance

  std::vector<apUnitTestFunction*> tests_; // Array of tests
  time_t start_, stop_;                    // Start, stop time
};




// This might look difficult, but it creates a unique class,
// derived from apUnitTestFunction. A static instance is also
// created which will add itself to the array of unit tests in
// the apUnitTest object (there is only a single, global
// instance of apUnitTest created). When the unit tests are run,
// the test() method of each derived object is called. An 
// example unit test function (which always passed) is show 
// below: 
//
//    UTFUNC(test)
//    {
//      VERIFY (true);
//    }
//
// The ## is the merging operator.  a##b = ab
// The # is a stringization operator  #a = "a"

#define UTFUNC(utx)                            \
class UT##utx : public apUnitTestFunction      \
{                                              \
UT##utx ();                                    \
static UT##utx sInstance;                      \
void test ();                                  \
};                                             \
UT##utx UT##utx::sInstance;                    \
UT##utx::UT##utx () : apUnitTestFunction(#utx) \
{                                              \
  apUnitTest::gOnly().addTest(#utx,this);      \
}                                              \
void UT##utx::test ()


#define VERIFY(condition) verify (condition, #condition)
#define VERIFYFLOAT(d1,d2) verifyFloat (d1, d2)


#endif // _unittest_h_
