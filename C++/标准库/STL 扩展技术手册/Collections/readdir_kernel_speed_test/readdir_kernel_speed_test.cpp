/* /////////////////////////////////////////////////////////////////////////////
 * File:        readdir_kernel_speed_test.cpp
 *
 * Purpose:     Implementation file for the readdir_kernel_speed_test project.
 *
 * Created:     8th September 2005
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


#ifdef _WIN32
# define _STLSOFT_FORCE_ANY_COMPILER
#endif /* _WIN32 */

/* STLSoft Header Files */
#include <stlsoft.h>

#include <platformstl/platformstl.hpp>
#include <platformstl/performance_counter.hpp>
//#include <stlsoft/performance_counter_scope.hpp>

#if defined(PLATFORMSTL_OS_IS_UNIX)

# include <unixstl.h>
# include <unixstl/readdir_sequence.hpp>

# ifdef _WIN32
#  include <unixem/implicit_link.h>
# endif /* _WIN32 */

#elif defined(PLATFORMSTL_OS_IS_WIN32)

# include <winstl.h>
# include <winstl/findfile_sequence.hpp>

#else /* ? operating system */

# error Operating system not discriminated

#endif /* operating system */


/* Standard C++ Header Files */
#include <exception>
#include <iostream>
#include <string>
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

/* /////////////////////////////////////////////////////////////////////////////
 * Function Objects
 */

struct length_append
{
public:
	length_append(size_t &n)
		: m_n(n)
	{}

public:
	template <typename S>
	void operator ()(S const &s) const
	{
		m_n += stlsoft::c_str_len(s);
	}

private:
	size_t	&m_n;
};

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	platformstl::performance_counter				counter;
	platformstl::performance_counter::interval_type	double_scan_time;
	platformstl::performance_counter::interval_type	stored_element_time;
//	platformstl::performance_counter::interval_type	double_scan_half_time;
	platformstl::performance_counter::interval_type	stored_element_half_time;

	static const char	HOME[]		=	"H:/Publishing/Books/Extended STL/test/Pt2_Collections/readdir_kernel_speed_test";

	static const size_t	NUM_LOOPS	=	50;

	size_t				n1			=	0;
	size_t				n2			=	0;

	{ for(size_t WARMUPS = 4; WARMUPS > 0; --WARMUPS)
	{
		counter.start();
		{
			unixstl::readdir_sequence	rds(HOME, unixstl::readdir_sequence::files);

			for(size_t k = 0; k < NUM_LOOPS; ++k)
			{
				std::for_each(rds.begin(), rds.end(), length_append(n1));
			}
		}
		counter.stop();
		double_scan_time = counter.get_microseconds();

		counter.start();
		{
			unixstl::readdir_sequence	rds(HOME, unixstl::readdir_sequence::files);
			std::vector<std::string>	copies;

			std::copy(rds.begin(), rds.end(), std::back_inserter(copies));

			counter.stop();
			stored_element_half_time = counter.get_microseconds();

			for(size_t k = 0; k < NUM_LOOPS; ++k)
			{
				std::for_each(copies.begin(), copies.end(), length_append(n2));
			}
//			{ for(size_t k = 0; k < 0x0FFFFFFF; ++k) {} }
		}
		counter.stop();
		stored_element_time = counter.get_microseconds();
	}}

	fprintf(stdout, "double scan time (ms):         %lu (n1=%d)\n", (unsigned long)double_scan_time, n1);
	fprintf(stdout, "stored element time (ms):      %lu (n1=%d)\n", (unsigned long)stored_element_time, n2);
	fprintf(stdout, "stored element half time (ms): %lu\n", (unsigned long)(stored_element_time - stored_element_half_time));

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
		cout << "readdir_kernel_speed_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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
