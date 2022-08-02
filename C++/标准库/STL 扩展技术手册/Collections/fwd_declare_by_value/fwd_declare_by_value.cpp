/* /////////////////////////////////////////////////////////////////////////////
 * File:        fwd_declare_by_value.cpp
 *
 * Purpose:     Implementation file for the fwd_declare_by_value project.
 *
 * Created:     16th September 2005
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


/* Standard C++ Header Files */
#include <exception>

#if !defined(__WATCOMC__) && \
    (   !defined(_MSC_VER) || \
        _MSC_VER >= 1100)

#else /* ? __WATCOMC__ */
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

namespace ns1
{
	class Outer1
	{
	public:
		class Inner1;

	public:
		Inner1 begin() const;
	};

	class Outer1::Inner1
	{};

	Outer1::Inner1 Outer1::begin() const
	{
		return Inner1();
	}
}

namespace ns2
{
	class Inner2;

	class Outer2
	{
	public:

	public:
		Inner2 begin() const;
	};

	class Inner2
	{};

	Inner2 Outer2::begin() const
	{
		return Inner2();
	}
}


/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	/* . */

    return 0;
}

int main(int argc, char *argv[])
{
#if 0
	{ for(size_t i = 0; i < 0xffffffff; ++i){} }
#endif /* 0 */

	try
	{

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
