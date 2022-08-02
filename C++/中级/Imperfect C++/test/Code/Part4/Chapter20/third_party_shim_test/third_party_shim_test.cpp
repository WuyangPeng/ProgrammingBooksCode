/* /////////////////////////////////////////////////////////////////////////////
 * File:        third_party_shim_test.cpp
 *
 * Purpose:     Implementation file for the third_party_shim_test project.
 *
 * Created:     24th December 2003
 * Updated:     24th December 2003
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
#include <string.h>
#include <wchar.h>

#include <stlsoft.h>

typedef struct _LSA_UNICODE_STRING
{
  unsigned short  Length;
  unsigned short  MaximumLength;
  wchar_t         *Buffer;
} LSA_UNICODE_STRING;

/* ////////////////////////////////////////////////////////////////////////// */

namespace stlsoft
{
  inline wchar_t const *c_str_ptr(LSA_UNICODE_STRING const &s)
  {
    return s.Buffer;
  }
}
namespace third_party
{
  class tp_string
  {
  public:
    wchar_t const *c_str() const
    {
      return L"tp_string";
    }
  };
  inline wchar_t const *c_str_ptr(tp_string const &s)
  {
    return s.c_str();
  }
}
namespace Client
{
  using stlsoft::c_str_ptr;
#if !defined(ACMELIB_COMPILER_SUPPORTS_KOENIG_LOOKUP)
//  using third_party::c_str_ptr;
#endif /* ! ACMELIB_COMPILER_SUPPORTS_KOENIG_LOOKUP */

  // puts will work for LSA_UNICODE_STRING and 
  // third_party::tp_string, and any other type for which a shim
  // is provided and accessible (through using 
  // declaration/directive or via Koenig lookup)

  template <typename S>
  void puts(S const &s)
  {
//    ::_putws(c_str_ptr(s));
    fwprintf(stdout, L"%s\n", c_str_ptr(s));
  }

  void test()
  {
      third_party::tp_string    ts;
      LSA_UNICODE_STRING        lsa;

      lsa.Buffer        =   L"WIN32_UNICODE_STRING";
      lsa.Length        =   wcslen(lsa.Buffer) - 1;
      lsa.MaximumLength =   wcslen(lsa.Buffer);

      puts(ts);
      puts(lsa);
  }
}

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, wchar_t ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("third_party_shim_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    Client::test();

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
