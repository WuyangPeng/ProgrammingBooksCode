/* /////////////////////////////////////////////////////////////////////////////
 * File:        listbox_deletions_test.cpp
 *
 * Purpose:     Implementation file for the listbox_deletions_test project.
 *
 * Created:     22nd August 2005
 * Updated:     20th November 2005
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
#include <stlsoft/integer_to_string.hpp>

#include <winstl.h>
#include <winstl/listbox_sequence.hpp>

#include <windowsx.h>


/* Standard C++ Header Files */
#include <exception>
#include <iostream>
#include <string>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

#ifdef __WATCOMC__
namespace std
{
	using ::exception;
}
#endif /* __WATCOMC__ */


/* Standard C Header Files */
#include <stdio.h>
#include <stdlib.h>

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	/* . */
	HWND	hwndListBox	=	::CreateWindow("LISTBOX", "", 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL);

	size_t	i;

	for(i = 0; i < 100; ++i)
	{
		char	sz[21];

		ListBox_AddString(hwndListBox, stlsoft::integer_to_string(sz, 21, i));
	}

	typedef winstl::listbox_sequence<std::string>	lbs_t;

	lbs_t					lbs(hwndListBox);
	lbs_t::const_iterator	b	=	lbs.begin();
#if 0

	for(i = 0; b != lbs.end(); ++b, ++i)
#else /* ? 0 */
	lbs_t::const_iterator	e	=	lbs.end();

	for(i = 0; b != e; ++b, ++i)
#endif /* 0 */
	{
		size_t	index	=	rand() % lbs.size();

		cout << "[" << i << "]: " << *b << endl;

		if(index < lbs.size())
		{
			cout << "<<" << index << ">>" << endl;

			ListBox_DeleteString(hwndListBox, index);
		}
	}

    return 0;
}

int main(int argc, char *argv[])
{
#if 0
	{ for(size_t i = 0; i < 0xffffffff; ++i){} }
#endif /* 0 */

	try
	{
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
		puts("listbox_deletions_test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */


		return main_(argc, argv);
	}
	catch(std::exception &x)
	{
		fprintf(stderr, "Unhandled error: %s\n", x.what());
	}
	catch(...)
	{
		fprintf(stderr, "Unhandled unknown error\n");
	}

	return EXIT_FAILURE;
}

/* ////////////////////////////////////////////////////////////////////////// */
