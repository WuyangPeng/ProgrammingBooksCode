/* /////////////////////////////////////////////////////////////////////////////
 * File:        std_string_test.cpp
 *
 * Purpose:     Implementation file for the std_string_test project.
 *
 * Created:     30th December 2003
 * Updated:     30th December 2003
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

#include <stlsoft.h>
#include <stlsoft_fast_string_concatenator.h>

//#define USE_STD_STRING
//#define USE_SIMPLE_STRING
#define USE_CSTRING
//#define USE_CCOMBSTR
//#define USE_BSTR_T

#if defined(USE_STD_STRING)

# include <string>
typedef std::string                         string_t;
# define    T(x)                            x
# define    printf                          printf
# define    STRING_TYPE                     "std::string"

#elif defined(USE_SIMPLE_STRING)

# include <stlsoft_simple_string.h>
typedef stlsoft::basic_simple_string<char>  string_t;
# define    T(x)                            x
# define    printf                          printf
# define    STRING_TYPE                     "stlsoft::simple_string"

#elif defined(USE_CSTRING)

# include <afx.h>
# define _MFCSTL_CSTRING_VENEER_INHERIT_AS_PUBLIC
# include <mfcstl_cstring_veneer.h>
typedef mfcstl::cstring_veneer              string_t;
# define    T(x)                            x
# define    printf                          printf
# define    STRING_TYPE                     "CString"

#elif defined(USE_CCOMBSTR)

# include <atlbase.h>
# define _ATLSTL_CCOMBSTR_VENEER_INHERIT_AS_PUBLIC
# include <atlstl_ccombstr_veneer.h>
typedef atlstl::ccombstr_veneer             string_t;
# define    T(x)                            L ## x
# define    printf                          wprintf
# define    STRING_TYPE                     "CComBSTR"

inline string_t operator +(string_t const &lhs, LPCOLESTR rhs)
{
    return string_t(lhs) += rhs;
}

#elif defined(USE_BSTR_T)

# include <comdef.h>
# define _XSTL_BSTR_T_VENEER_INHERIT_AS_PUBLIC
# include <xstl_bstr_t_veneer.h>
typedef xstl::bstr_t_veneer                 string_t;
# define    T(x)                            L ## x
# define    printf                          wprintf
# define    STRING_TYPE                     "_bstr_t"

#else
# error Must select a string type
#endif /* string */

#if defined(unix) || \
    defined(__unix__)

#include <unixstl.h>

#include <unixstl_performance_counter.h>

unixstl_ns_using(performance_counter)

#elif defined(WIN32) || \
    defined(_WIN32)

#include <winstl.h>

#include <winstl_performance_counter.h>

winstl_ns_using(performance_counter)

#else /* ? operating system */

# error Operating system not discriminated

#endif /* operating system */

/* ////////////////////////////////////////////////////////////////////////// */

inline stlsoft::fast_string_concatenator<string_t> operator +(stlsoft::fsc_seed lhs, string_t const &rhs)
{
    return stlsoft::fast_string_concatenator<string_t>(lhs, rhs);
}


const int ITERATIONS    =   100000;

/* ////////////////////////////////////////////////////////////////////////// */

volatile int    s_x;

int main(int argc, char *argv[])
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    int                 iRet    =   0;
    int                 i;
    performance_counter counter;

    puts("std_string_test: " __STLSOFT_COMPILER_LABEL_STRING " (" STRING_TYPE ")");

    for(i = 1; i < argc; ++i)
    {
        const char  *arg    =   argv[i];

        if(arg[0] == '-')
        {
            if(arg[1] == '-')
            {
                /* -- arguments */
            }
            else
            {
                /* - arguments */
            }
        }
        else
        {
            /* other arguments */
        }
    }

    /* . */
    unsigned long   tm_normal;
    unsigned long   tm_fast;

    string_t            strings[10];

    for(i = 0; i < stlsoft_num_elements(strings); ++i)
    {
        strings[i] = string_t((size_t)(rand() % 100) + i, string_t::value_type('~'));

        printf(T("%2d - %s\n"), i, strings[i].c_str());
    }

    for(int WARMUPS = 2; WARMUPS > 0; --WARMUPS)
    {
        counter.start();
        for(i = 0; i < ITERATIONS; ++i)
        {
#if 0
            string_t    s   =   strings[0] + ' ' + strings[1] + " (" + strings[2] + ")";
#else /* ? 0 */
            string_t    s;
#endif /* 0 */

#if 1
            s = s + T(" [") + s + T("]");
#else /* ? 0 */
            s = T(" [") + s + T("]");
#endif /* 0 */

            s_x += s.length();
        }
        counter.stop();
        tm_normal = counter.get_milliseconds();

        if(1 == WARMUPS)
        {
            printf(T("std:  %lu\n"), tm_normal);
        }

        counter.start();
        for(i = 0; i < ITERATIONS; ++i)
        {
#if 0
            string_t    s   =   stlsoft::fsc_seed() + strings[0] + ' ' + strings[1] + " (" + strings[2] + ")";
#else /* ? 0 */
            string_t    s;
#endif /* 0 */

#if 1
            s = stlsoft::fsc_seed() + s + T(" [") + s + T("]");
#else /* ? 0 */
            s = stlsoft::fsc_seed() + T(" [") + s + T("]");
#endif /* 0 */

            s_x += s.length();
        }
        counter.stop();
        tm_fast = counter.get_milliseconds();

        if(1 == WARMUPS)
        {
            printf(T("fsc:  %lu\n"), tm_fast);
        }
    }


    return iRet + s_x;
}

/* ////////////////////////////////////////////////////////////////////////// */
