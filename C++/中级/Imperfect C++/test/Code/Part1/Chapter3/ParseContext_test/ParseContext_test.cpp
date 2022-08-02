/* /////////////////////////////////////////////////////////////////////////////
 * File:        ParseContext_test.cpp
 *
 * Purpose:     Implementation file for the ParseContext_test project.
 *
 * Created:     27th October 2003
 * Updated:     27th October 2003
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (C) 1999-2003, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              email:      software@synesis.com.au
 *
 *              This source code is placed into the public domain 2003
 *              by Synesis Software Pty Ltd. There are no restrictions
 *              whatsoever to your use of the software. 
 *
 *              This source code is provided by Synesis Software Pty Ltd "as is"
 *              and any warranties, whether expressed or implied, including, but
 *              not limited to, the implied warranties of merchantability and
 *              fitness for a particular purpose are disclaimed. In no event
 *              shall the Synesis Software Pty Ltd be liable for any direct,
 *              indirect, incidental, special, exemplary, or consequential
 *              damages (including, but not limited to, procurement of
 *              substitute goods or services; loss of use, data, or profits; or
 *              business interruption) however caused and on any theory of
 *              liability, whether in contract, strict liability, or tort
 *              (including negligence or otherwise) arising in any way out of
 *              the use of this software, even if advised of the possibility of
 *              such damage. 
 *
 *              Neither the name of Synesis Software Pty Ltd nor the names of
 *              any subdivisions, employees or agents of Synesis Software Pty
 *              Ltd, nor the names of any other contributors to this software
 *              may be used to endorse or promote products derived from this
 *              software without specific prior written permission. 
 *
 * ////////////////////////////////////////////////////////////////////////// */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ////////////////////////////////////////////////////////////////////////// */


enum SPEvent { SPE_PARSE_SYMBOL };

struct ParseContext
{
// Callback functions
  void *(*pfnAlloc)(size_t cb);
  void (*pfnFree)(void *p);
  void *(*pfnRealloc)(void *p, size_t cb);
  int (*pfnLookupSymbol)(char const *name, char *dest, size_t *pcchDest);

// Data members
//  . . .

  char const *currTokBegin;
  char const *currTokEnd;

//  . . .
};

int SrcParse_LibEntry(SPEvent event, ParseContext *context);

/* ////////////////////////////////////////////////////////////////////////// */

// MyPlugIn.cpp

void MyPlugIn_ParseSymbol(ParseContext *context);

int SrcParse_LibEntry(SPEvent event, ParseContext *context)
{
  switch(event)
  {
    case SPE_PARSE_SYMBOL:
      MyPlugIn_ParseSymbol(context);
  }

  //. . .
  return 0;
}

void MyPlugIn_ParseSymbol(ParseContext *context)
{
  size_t  tokLength = 1 + (context->currTokEnd - context->currTokBegin);
  char    *tokName  = strncpy( (char*)(*context->pfnAlloc)(sizeof(char) * tokLength)
                              , context->currTokBegin, tokLength);
  size_t  cchDest   = 0;

  int  cch = (*context->pfnLookupSymbol)(tokName, NULL, &cchDest);

//  . . .  
}

/* ////////////////////////////////////////////////////////////////////////// */

class ParseContextWrapper
{
public:
  ParseContextWrapper(ParseContext *context)
    : m_context(context)
  {}

  void *Alloc(size_t cb)
  {
    return (*m_context->pfnAlloc)(cb);
  }

  string CurrentToken()
  {
    return string(m_context->currTokBegin, m_context->currTokEnd);
  }

  string LookupSymbol(string const &token)
  {
     ...

  int OnParseSymbol();

private:
  ParseContext *m_context;
};


int SrcParse_LibEntry(SPEvent event, ParseContext *context)
{
  ParseContextWrapper   cw(context);

  switch(event)
  {
    case SPE_PARSE_SYMBOL:
      return OnParseSymbol();

    . . .

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    /* . */

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
