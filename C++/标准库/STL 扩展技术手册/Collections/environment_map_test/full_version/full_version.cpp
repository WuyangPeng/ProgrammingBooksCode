/* /////////////////////////////////////////////////////////////////////////////
 * File:        full_version.cpp
 *
 * Purpose:     Implementation file for the full_version project.
 *
 * Created:     10th November 2005
 * Updated:     1st May 2007
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2005-2007, Synesis Software Pty Ltd.
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
#include <stlsoft/string_split_functions.hpp>
#include <stlsoft/string_view.hpp>

#include "full_version.hpp"

/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <iostream>

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
	/* . */
	stlsoft::environment_map	env;

	cout << "Enumerating (forward):" << endl;
	{ for(stlsoft::environment_map::const_iterator b = env.begin(); b != env.end(); ++b)
	{
		stlsoft::environment_map::value_type const	&r	=	*b;

//		cout << "  " << (*b).first << " = " << (*b).second << endl;
//		cout << "  " << r.first << " = " << r.second << endl;

//		env.insert((*b).first.c_str(), "Arch");
//		env.erase(b);

#if 0
		stlsoft::environment_map::const_reverse_iterator	rit	=	env.rbegin();

		++rit;

		if(rit.base() != b)
		{
			env.erase(rit.base());
		}
#endif /* 0 */

#if 0
		{ for(stlsoft::environment_map::const_iterator b2 = b; ++b2 != env.end();)
		{
			if(NULL != ::strstr((*b).first.c_str(), (*b2).first.c_str()))
			{
				cout << "    " << (*b2).first << " = " << (*b2).second << endl;
			}

//			stlsoft_assert((*(b + 1)).first == (*b2).first);
//			stlsoft_assert((*(b + 1)).second == (*b2).second);
		}}
#else /* ? 0 */
		stlsoft::environment_map::const_iterator b1	=	b;
		{ for(stlsoft::environment_map::const_iterator b2 = env.begin(); b2 != env.end(); ++b2)
		{
			if( b1 != b2 &&
				(*b1).first.end() != std::search(	(*b1).first.begin()
												,	(*b1).first.end()
												,	(*b2).first.begin()
												,	(*b2).first.end()))
			{
				env.erase((*b2).first.c_str());

				cout << (*b2).first << " is in " << (*b1).first << endl;
			}

		}}
#endif /* 0 */
	}}
	cout << endl;

	return 0;

	cout << "Enumerating (backward):" << endl;
	{ for(stlsoft::environment_map::const_reverse_iterator b = env.rbegin(); b != env.rend(); ++b)
	{
		stlsoft::environment_map::value_type const	&r	=	*b;

		cout << "  " << (*b).first << " = " << (*b).second << endl;
		cout << "  " << r.first << " = " << r.second << endl;
	}}
	cout << endl;

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
		cout << "full_version: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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
