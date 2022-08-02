/* /////////////////////////////////////////////////////////////////////////////
 * File:        filesys_enum_test.cpp
 *
 * Purpose:     Implementation file for the filesys_enum_test project.
 *
 * Created:     7th September 2005
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

/* PlatformSTL Header Files */
#include <platformstl/platformstl.hpp>

#if defined(PLATFORMSTL_OS_IS_UNIX)

# include <unixstl.h>
# include <unixstl/glob_sequence.hpp>

#elif defined(PLATFORMSTL_OS_IS_WIN32)

# include <winstl.h>
# include <winstl/findfile_sequence.hpp>

#else /* ? operating system */

# error Operating system not discriminated

#endif /* operating system */


/* Standard C++ Header Files */
#include <exception>
#include <iostream>

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

/* /////////////////////////////////////////////////////////////////////////////
 * Function declarations
 */

template <typename C>
void dump(C const &c)
{
	ss_typename_type_k C::const_iterator	b	=	c.begin();

	for(; b != c.end(); ++b)
	{
		cout << stlsoft_ns_qual(c_str_ptr)(*b) << endl;
	}
}

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	/* . */

#ifdef PLATFORMSTL_OS_IS_UNIX
	using unixstl::glob_sequence;

	glob_sequence	gls("H:/Dev/Products/systools/hardlink/vc5", "../../stdfilt/*.h", glob_sequence::files);

	dump(gls);
#else /* ? 0 */
	using winstl::findfile_sequence;

	findfile_sequence	gls("H:\\Dev\\Products\\systools\\hardlink\\vc5", "..\\..\\stdfilt\\*.h;..\\..\\hardlink\\*.c*", ';', findfile_sequence::files);

	dump(gls);
#endif /* 0 */

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
		cout << "filesys_enum_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
#endif /* debug */


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
