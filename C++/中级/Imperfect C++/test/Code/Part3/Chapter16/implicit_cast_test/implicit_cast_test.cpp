/* /////////////////////////////////////////////////////////////////////////////
 * File:        implicit_cast_test.cpp
 *
 * Purpose:     Implementation file for the implicit_cast_test project.
 *
 * Created:     1st February 2004
 * Updated:     1st February 2004
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (C) 1999-2004, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              email:      software@synesis.com.au
 *
 *              This source code is placed into the public domain 2004
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
#include <time.h>
#include <windows.h>

#include <stlsoft.h>

/* ////////////////////////////////////////////////////////////////////////// */

#if (   defined(WIN32) || \
        defined(_WIN32)) && \
    !defined(_INC_WINDOWS)
extern "C" void __stdcall Sleep(unsigned long);
#endif /* WIN32 */

/* ////////////////////////////////////////////////////////////////////////// */

typedef struct tm   tm;
typedef double      DATE;

class Time
{
public:
    operator time_t () const
    {
        return 0;
    }
    operator tm () const
    {
        return tm();
    }
#ifdef WIN32
    operator DATE () const
    {
        return 0;
    }
    operator FILETIME () const
    {
        return FILETIME();
    }
    operator SYSTEMTIME () const
    {
        return SYSTEMTIME();
    }
#endif /* WIN32 */
    operator bool() const
    {
        return 0;
    }
};

void f1(tm t)
{}
void f2(DATE d)
{}
void f3(long double ld)
{}

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("implicit_cast_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    Time        t;

    time_t      v1  =   t;
    tm          v2  =   t;
#ifdef WIN32
    DATE        v3  =   t;
    FILETIME    v4  =   t;
    SYSTEMTIME  v5  =   t;
#endif /* WIN32 */

    if(t)
    {
        puts("true");
    }

#if 0
    f1(t);
    f2(t);
    f3(t);
#endif /* 0 */

#ifdef WIN32
    STLSOFT_SUPPRESS_UNUSED(v5);
    STLSOFT_SUPPRESS_UNUSED(v4);
    STLSOFT_SUPPRESS_UNUSED(v3);
#endif /* WIN32 */
    STLSOFT_SUPPRESS_UNUSED(v2);
    STLSOFT_SUPPRESS_UNUSED(v1);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
