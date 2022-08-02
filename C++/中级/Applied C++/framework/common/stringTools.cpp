// stringtools.h
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
// String tools

#include "stringTools.h"


// Ruler
//       1         2         3         4         5         6    6
//345678901234567890123456789012345678901234567890123456789012345



// *******************
// *                 *
// *  apStringTools  *
// *                 *
// *******************

// Standard terminators for parsing a text stream
// Note. The first character in the string is a space
std::string apStringTools::sStandardTerm = " \t\r\n";


apToken apStringTools::sParse (const std::string& str, const std::string& term)
{
  apToken result;

  // Skip over leading terminators
  size_t start = str.find_first_not_of (term);
  if (start == str.npos) {
    // The entire string only contains terminator characters
    return result;
  }

  // Find the first command
  size_t end = str.find_first_of (term, start);
  if (end == str.npos) {
    result.parsed = str;
    return result;
  }

  // Extract the first command
  result.parsed = str.substr (start, end-start);

  // Return the rest of the string (after the terminators)
  size_t next = str.find_first_not_of (term, end);
  if (next != str.npos)
    result.remainder = str.substr (next);

  return result;
}
