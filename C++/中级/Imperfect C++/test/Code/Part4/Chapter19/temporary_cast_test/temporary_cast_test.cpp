/* /////////////////////////////////////////////////////////////////////////////
 * File:        temporary_cast_test.cpp
 *
 * Purpose:     Implementation file for the temporary_cast_test project.
 *
 * Created:     14th November 2003
 * Updated:     14th November 2003
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

#include <windows.h>
#include <iostream>

#include <string>

#include <stlsoft.h>
#include <stlsoft_string_access.h>

using stlsoft::c_str_ptr;

#include <comstl.h>
#include <comstl_string_access.h>

using comstl::c_str_ptr;

#include <winstl.h>
#include <winstl_string_access.h>

using winstl::c_str_ptr;

/* ////////////////////////////////////////////////////////////////////////// */

template<   typename T
        ,   typename P = T const *
        >
struct temporary_cast
{
public:
    temporary_cast(P p)
        : m_p(p)
    {}

public:
    operator P () const
    {
        return m_p;
    }

public:
    P   m_p;
};


/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 1
    ::Sleep(100000);
#endif /* 0 */

    std::cout << "temporary_cast_test: " << __STLSOFT_COMPILER_LABEL_STRING << std::endl;

    /* . */
    HWND        hwndDesktop =   ::GetDesktopWindow();



    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
