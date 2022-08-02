/* /////////////////////////////////////////////////////////////////////////////
 * File:        fixed_size_test.cpp
 *
 * Purpose:     Implementation file for the fixed_size_test project.
 *
 * Created:     10th August 2003
 * Updated:     10th August 2003
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
#if 0
#include <stdint.h>
#else
typedef signed char         int8_t;
typedef unsigned char       uint8_t;
typedef signed short        int16_t;
typedef unsigned short      uint16_t;
typedef signed long         int32_t;
typedef unsigned long       uint32_t;
typedef signed __int64      int64_t;
typedef unsigned __int64    uint64_t;
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

#if 1

char const *integer_to_string(int32_t );
char const *integer_to_string(uint32_t );
char const *integer_to_string(int64_t );
char const *integer_to_string(uint64_t );
char const *integer_to_string(bool ); // return "true" or "false"

inline char const *integer_to_string(int8_t i)
{
  return integer_to_string(static_cast<int32_t>(i));
}
char const *integer_to_string(uint8_t i)
{
  return integer_to_string(static_cast<uint32_t>(i));
}
char const *integer_to_string(int16_t i)
{
  return integer_to_string(static_cast<int32_t>(i));
}
char const *integer_to_string(uint16_t i)
{
  return integer_to_string(static_cast<uint32_t>(i));
}

void integer_to_string(char );
struct wchar_t_cannot_convert_as_integer {};
#ifndef _MSC_VER
wchar_t_cannot_convert_as_integer integer_to_string(wchar_t );
#endif _MSC_VER


#else

#endif /* 0 */

class integer_convert
{
// Conversions
public:
  static char const *to_string(int8_t );
  static char const *to_string(uint8_t );
  static char const *to_string(int16_t );
  static char const *to_string(uint16_t );
  static char const *to_string(int32_t );
  static char const *to_string(uint32_t );
  static char const *to_string(int64_t );
  static char const *to_string(uint64_t );
  static char const *integer_to_string(bool );

#if !defined(INTCONV_INT_USED_FOR_SIZED_TYPES)
  static char const *to_string(int );
  static char const *to_string(unsigned int );
#endif /* !INTCONV_INT_USED_FOR_SIZED_TYPES */

// Proscribed conversions
private:
  static char const *to_string(char );
  static char const *integer_to_string(wchar_t );
};

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    /* . */
    int8_t  i8  =   0;
    int32_t i32 =   0;
    char    ch  =   'A';
    wchar_t wch =   L'L';

    puts(integer_to_string(i8));
//  puts(integer_to_string(ch));


    puts(integer_convert::to_string(i32));  // Ok
    puts(integer_convert::to_string(ch)); // Ok


    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */

char const *integer_to_string(int32_t i)    { return "int32_t"; }
char const *integer_to_string(uint32_t )    { return "uint32_t"; }
char const *integer_to_string(int64_t )     { return "int64_t"; }
char const *integer_to_string(uint64_t )    { return "uint64_t"; }
char const *integer_to_string(bool )        { return "bool"; }

/* ////////////////////////////////////////////////////////////////////////// */
