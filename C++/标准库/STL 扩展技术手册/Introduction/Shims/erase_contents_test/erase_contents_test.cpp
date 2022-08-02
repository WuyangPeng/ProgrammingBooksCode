/* /////////////////////////////////////////////////////////////////////////////
 * File:        erase_contents_test.cpp
 *
 * Purpose:     Implementation file for the erase_contents_test project.
 *
 * Created:     10th August 2005
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

#include <mfcstl.h>


/* Standard C++ Header Files */
#include <exception>
#include <iostream>
#include <vector>

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

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

template<	typename	T
		,	size_t		N
		>
void erase_contents(T (&ar)[N])
{
	std::fill_n(&ar[0], N, T());
}

void erase_contents(CString &str)
{
	str.Empty();
}

template<	typename T
		,	typename A
		>
void erase_contents(std::vector<T, A> &c)
{
	c.erase(c.begin(), c.end());
}

#if 0
class erase_contents
{
public:
	template<	typename T
			,	typename A
			>
	erase_contents(std::vector<T, A> &c)
	{
		c.erase(c.begin(), c.end());
	}

	erase_contents(std::vector<int> &c)
	{
		c.erase(c.begin(), c.end());
	}
};
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
	puts("erase_contents_test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

	/* . */
	{
		int					ar[21];
		CString				str("String 1");
		std::vector<int>	vi(10);	vi[1] = 1;

		erase_contents(ar);
		erase_contents(str);
		erase_contents(vi);
	}

    return 0;
}

int main(int argc, char *argv[])
{
#if 1
	for(size_t i = 0; i < 0xFFFFFFFF; ++i) {}
#endif /* 0 */

	try
	{
		return main_(argc, argv);
	}
	catch(std::exception &x)
	{
		cerr << "Unhandled error: " << x.what() << endl;
	}
	catch(...)
	{
		cerr << "Unhandled unknown error" << endl;
	}

	return EXIT_FAILURE;
}

/* ////////////////////////////////////////////////////////////////////////// */
