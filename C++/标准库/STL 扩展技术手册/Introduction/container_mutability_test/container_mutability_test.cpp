/* /////////////////////////////////////////////////////////////////////////////
 * File:        container_mutability_test.cpp
 *
 * Purpose:     Implementation file for the container_mutability_test project.
 *
 * Created:     3rd March 2006
 * Updated:     3rd March 2006
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2006, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              This source code is placed into the public domain 2006
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


/* STLSoft Header Files */
#include <stlsoft/stlsoft.h>

/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#if 0
#include <iterator>
#endif /* 0 */

#if !defined(__WATCOMC__) && \
    (   !defined(_MSC_VER) || \
        _MSC_VER >= 1100)

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

#else /* ? __WATCOMC__ */
namespace std
{
    using ::exception;
}
#endif /* __WATCOMC__ */


/* Standard C Header Files */
#include <stdlib.h>

#if defined(_MSC_VER) && \
    defined(_DEBUG)
# include <crtdbg.h>
#endif /* _MSC_VER) && _DEBUG */

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

typedef std::string     string_t;

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

static void print_element(std::string const &s)
{
	printf("0x%08x: %s\n", &s, s.c_str());
}

static void arrangement_mutating_only()
{
//	std::list<const int>	li;


}

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	arrangement_mutating_only();

    /* . */
	const size_t				NUM	=	4;

	std::vector<std::string>	v;
	std::list<std::string>		l;

	{for(size_t i = 0; i < NUM; ++i)
	{
		char	s[7 + 21];

		::sprintf(&s[0], "string-%u", NUM - i);

		v.push_back(s);
		l.push_back(s);
	}}

	cout << "vector (before sort)" << endl;
	std::for_each(v.begin(), v.end(), print_element);
	cout << "list (before sort)" << endl;
	std::for_each(l.begin(), l.end(), print_element);
	cout << endl;

	std::sort(v.begin(), v.end());
	l.sort();

	cout << "vector (after sort)" << endl;
	std::for_each(v.begin(), v.end(), print_element);
	cout << "list (after sort)" << endl;
	std::for_each(l.begin(), l.end(), print_element);
	cout << endl;

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    int             iRet;

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemState    memState;
#endif /* _MSC_VER && _MSC_VER */

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemCheckpoint(&memState);
#endif /* _MSC_VER && _MSC_VER */

#if 0
    { for(size_t i = 0; i < 0xffffffff; ++i){} }
#endif /* 0 */

    try
    {

        iRet = main_(argc, argv);
    }
    catch(std::exception &x)
    {
        cerr << "Unhandled error: " << x.what() << endl;

        iRet = EXIT_FAILURE;
    }
    catch(...)
    {
        cerr << "Unhandled unknown error" << endl;

        iRet = EXIT_FAILURE;
    }

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemDumpAllObjectsSince(&memState);
#endif /* _MSC_VER) && _DEBUG */

    return iRet;
}

/* ////////////////////////////////////////////////////////////////////////// */
