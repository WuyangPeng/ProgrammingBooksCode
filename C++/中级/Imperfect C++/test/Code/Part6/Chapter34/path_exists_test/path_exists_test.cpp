/* /////////////////////////////////////////////////////////////////////////////
 * File:        path_exists_test.cpp
 *
 * Purpose:     Implementation file for the path_exists_test project.
 *
 * Created:     22nd January 2004
 * Updated:     23rd January 2004
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

#include <windows.h>
#include <stdio.h>

#include <stlsoft.h>
#include <stlsoft_simple_string.h>

#if defined(unix) || \
    defined(__unix__)

# include <unixstl.h>
# include <unixstl_filesystem_traits.h>
# include <unixstl_glob_sequence.h>
# include <unixstl_readdir_sequence.h>
# include <unixstl_functionals.h>

typedef unixstl::filesystem_traits<char>        traits_t;

typedef unixstl::basic_glob_sequence<char>      sequence_t;

#elif defined(WIN32) || \
    defined(_WIN32)

# include <winstl.h>
# include <winstl_filesystem_traits.h>
# include <winstl_findfile_sequence.h>
# include <winstl_functionals.h>

typedef winstl::filesystem_traits<char>         traits_t;

typedef winstl::basic_findfile_sequence<char>   sequence_t;

# include <winstl_listbox_sequence.h>

#else /* ? operating system */

# error Operating system not discriminated

#endif /* operating system */

#include <algorithm>
#include <functional>

using stlsoft::c_str_ptr;

/* ////////////////////////////////////////////////////////////////////////// */

template<   ss_typename_param_k C
        ,   ss_typename_param_k A = C const *
        >
struct is_large
    : public std::unary_function<A, bool>
{
public:
    typedef C           char_type;
    typedef is_large<C> class_type;

public:
//    bool operator ()(char_type const *s) const
//    {
//        return is_large_(s);
//    }

//#ifdef __STLSOFT_CF_MEMBER_TEMPLATE_FUNCTION_SUPPORT
    template <ss_typename_param_k S>
    bool operator ()(S const &s) const
    {
        return is_large_(c_str_ptr(s));
    }
//#endif /* __STLSOFT_CF_MEMBER_TEMPLATE_FUNCTION_SUPPORT */

private:
    static bool is_large_(char_type const *s)
    {
        HANDLE  h       =   ::CreateFile(s, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
        ::GetLastError();
        DWORD   size    =   ::GetFileSize(h, NULL);

        if(INVALID_HANDLE_VALUE != h)
        {
            ::CloseHandle(h);
        }

        return size != 0xFFFFFFFF && size > 1024;
    }
};

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("path_exists_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    sequence_t  files(".", traits_t::pattern_all(), sequence_t::includeDots);

    size_t      cSmall  =   std::count_if(files.begin(), files.end(), is_large<char>());
    size_t      cLarge  =   std::count_if(files.begin(), files.end(), std::not1(is_large<char>()));

    HWND        hwndListBox =   ::CreateWindow("LISTBOX", "", 0, 0, 0, 0, 0, 0, 0, 0, 0);

    ::SendMessage(hwndListBox, LB_ADDSTRING, 0, (LPARAM)"String #1");
    ::SendMessage(hwndListBox, LB_ADDSTRING, 0, (LPARAM)"String #2");
    ::SendMessage(hwndListBox, LB_ADDSTRING, 0, (LPARAM)"String #3");

    winstl::listbox_sequence<stlsoft::basic_simple_string<char> >   lbs(hwndListBox);

    cSmall  =   std::count_if(lbs.begin(), lbs.end(), is_large<char>());
    cLarge  =   std::count_if(lbs.begin(), lbs.end(), std::not1(is_large<char, winstl::listbox_sequence<stlsoft::basic_simple_string<char> >::value_type /* const */ >()));

    ;

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
