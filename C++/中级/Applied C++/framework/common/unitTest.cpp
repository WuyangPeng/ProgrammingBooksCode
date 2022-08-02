// unittest.cpp
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


#include "unitTest.h"
#include "timing.h"

#include <math.h>
#include <stdio.h>


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345




// ************************ 
// *                      *
// *  apUnitTestFunction  *
// *                      *
// ************************

apUnitTestFunction::apUnitTestFunction (const std::string& name)
: result_ (eNotRun), name_ (name), verbose_ (false), elapsed_ (0)
{}


void apUnitTestFunction::run (bool verbose)
{
  std::string error;
  verbose_ = verbose;

  // Run the test
  if (verbose) 
    std::cout << "Running " << name_.c_str() << std::endl;
  result_ = eRunning;
 
  apElapsedTime time;
  try {
    test ();
  }
  catch (const std::exception& ex) {
    // We caught an STL exception
    error = std::string("Exception '") + ex.what() + "' caught";
    if (verbose)
      std::cout << error << " in " << name_.c_str() << std::endl;
    addMessage (error);
    result_ = eFailure;
  }
  catch (...) {
    // We caught an unknown exception
    error = "Unknown exception caught";
    if (verbose)
      std::cout << error << " in " << name_.c_str() << std::endl;
    addMessage (error);
    result_ = eFailure;
  }
  elapsed_ = time.sec ();

  // Make sure the test() function set a result or set eUnknown
  if (result_ != eSuccess && result_ != eFailure)
    result_ = eUnknown;

  if (verbose_) {
    std::cout << "  Result of " << name_.c_str() << " is " 
              << resultString().c_str() << " (" << elapsed_ 
              << " sec)" << std::endl;
    if (message_.size() > 0)
      std::cout << "  Messages: " << message_.c_str() 
                << std::endl;
  }
}


bool apUnitTestFunction::verify (bool state, const std::string& message)
{
  if (!state) {
    result_ = eFailure;
    addMessage (message);
    if (verbose_) 
      std::cout << " FAILURE " << name_.c_str() << " : " 
                << message.c_str() << std::endl;
  }
  else if (result_ != eFailure)
    // Make sure we mark the unit test success, if possible.
    result_ = eSuccess;
  return state;
}

bool apUnitTestFunction::verifyFloat (double d1, double d2)
{
  double delta = fabs (d1-d2);
  if (delta > 1.e-5) {
    char buffer[128];
    sprintf (buffer, "%.11f != %.11f", d1, d2);
    return verify (false, buffer);
  }

  return verify (true);
}


void apUnitTestFunction::addMessage (const std::string& message)
{
  if (message_.size() > 0) message_ += "\n";
  message_ += message;
}


// Not a const reference because it isn't safe
std::string apUnitTestFunction::resultString () const
{
  switch (result_) {
  case eNotRun:
    return "Not Run";
  case eRunning:
    return "Running";
  case eUnknown:
    return "Unknown";
  case eSuccess:
    return "Success";
  case eFailure:
    return "***** Failure *****";
  default:
    break;
  }

  return "Unknown Result";
}


// ****************
// *              *
// *  apUnitTest  *
// *              *
// ****************
//

apUnitTest* apUnitTest::sOnly_ = 0;

apUnitTest& apUnitTest::gOnly ()
{
  if (!sOnly_)  sOnly_ = new apUnitTest ();
  return *sOnly_;
}


apUnitTest::apUnitTest () : start_ (0), stop_ (0)
{}


void apUnitTest::addTest (const std::string& /*name*/, 
                          apUnitTestFunction* test)
{
  // Keep track of this unit test object to run
  tests_.push_back (test);
}

bool apUnitTest::run (bool verbose)
{
  bool state = true;
  start_ = time(0);

  for (unsigned int i=0; i<tests_.size(); i++) {
    // Fetch the next test to run and run it
    apUnitTestFunction* test = tests_[i];
    test->run (verbose);
    if (test->result() != apUnitTestFunction::eSuccess) 
      state = false;
  }

  stop_ = time(0);
  return state;
}


const apUnitTestFunction* apUnitTest::retrieve (int index) const
{
  if (index < 0 || index >= size()) return 0;
  return tests_[index];
}


void apUnitTest::dumpResults (std::ostream& out)
{
  int nSuccess = 0;
  int nFailed  = 0;
  int nOther   = 0;

  out << "Unit Test started at  " << ctime(&start_) << std::endl;
  out << "Unit Test finished at " << ctime(&stop_) << std::endl;

  for (unsigned int i=0; i<tests_.size(); i++) {
    apUnitTestFunction* test = tests_[i];

    switch (test->result()) {
    case apUnitTestFunction::eSuccess:
      nSuccess++;
      break;
    case apUnitTestFunction::eFailure:
      nFailed++;
      break;
    default:
      nOther++;
      break;
    };

    out << "Test " << i+1 << ": " << test->resultString().c_str() 
        << " : " << test->name().c_str() << " : ";
    if (test->description().size() > 0)
      out << test->description().c_str();
    out << " : " << test->elapsed() << " sec" << std::endl;
    if (test->message().size() > 0)
      out << "  Messages: " << std::endl 
          << test->message().c_str() << std::endl;
  }

  out << std::endl << std::endl;
  out << "Passed: " << nSuccess << ", Failed: " << nFailed 
      << ", Other: " << nOther << std::endl;
}
