/* /////////////////////////////////////////////////////////////////////////////
 * File:        ev4.cpp
 *
 * Purpose:     Implementation file for the ev4 project.
 *
 * Created:     10th November 2005
 * Updated:     22nd November 2005
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2005, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              This source code is placed into the public domain 2005
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
#include <stlsoft.h>
#include <stlsoft/member_selector_iterator.hpp>
#include <stlsoft/string_split_functions.hpp>
#include <stlsoft/string_view.hpp>

#include "ev4.hpp"

/* Standard C++ Header Files */
#include <exception>
#include <iostream>
#include <string>
#include <vector>

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

static int main_(int /* argc */, char ** /*argv*/)
{
	std::vector<std::string>	delete_names;

	/* . */
	{
		stlsoft::environment_map	env;

		cout << "Enumerating (forward):" << endl;
		{ for(stlsoft::environment_map::const_iterator b = env.begin(); b != env.end(); ++b)
		{
			stlsoft::environment_map::value_type const	&r	=	*b;

			cout << "  " << (*b).first << " = " << (*b).second << endl;
			cout << "  " << r.first << " = " << r.second << endl;
		}}
		cout << endl;

		cout << "Enumerating (backward):" << endl;
		{ for(stlsoft::environment_map::const_reverse_iterator b = env.rbegin(); b != env.rend(); ++b)
		{
			stlsoft::environment_map::value_type const	&r	=	*b;

			cout << "  " << (*b).first << " = " << (*b).second << endl;
			cout << "  " << r.first << " = " << r.second << endl;
		}}
		cout << endl;

	}

	{
		stlsoft::environment_map	env;

		cout << "Enumerating (forward):" << endl;
		{ for(stlsoft::environment_map::const_iterator b = env.begin(); b != env.end(); ++b)
		{
			stlsoft::environment_map::value_type const	&r	=	*b;

			cout << "  " << (*b).first << " = " << (*b).second << endl;
			cout << "  " << r.first << " = " << r.second << endl;
		}}
		cout << endl;
	}

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
	int				iRet;

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemState	memState;
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
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
		cout << "ev4: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
#endif /* debug */


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
