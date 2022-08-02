/* /////////////////////////////////////////////////////////////////////////////
 * File:        Fibonacci_sequence_test.cpp
 *
 * Purpose:     Implementation file for the Fibonacci_sequence_test project.
 *
 * Created:     16th August 2005
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
#include <stlsoft/stlsoft.h>
#include <stlsoft/integer_to_string.hpp>
#include <stlsoft/iterator.hpp>
#include <stlsoft/limit_traits.h>
#include <stlsoft/meta.hpp>
#include <stlsoft/algorithms/bounded.hpp>
#include <stlsoft/sign_traits.hpp>
#include <stlsoft/true_typedef.hpp>

/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <iostream>
#include <stdexcept>

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
#include <float.h>
#include <math.h>
#include <stdio.h>

/* /////////////////////////////////////////////////////////////////////////////
 * Options
 *
 * 1. 
 */

//#define XSTL_FIBONACCI_USE_64BIT

//#define USE_SEQUENCE_1
//#define USE_SEQUENCE_2
//#define USE_SEQUENCE_3
//#define USE_SEQUENCE_4
//#define USE_SEQUENCE_5
//#define USE_SEQUENCE_6
#define USE_SEQUENCE_7

#if 0
 // Nothing
#elif defined(USE_SEQUENCE_7)
# define  DESC_STRING			"integral, contract enforcement, constructor limit or threshold"
# include "./sequence_7.hpp"
#elif defined(USE_SEQUENCE_6)
# define  DESC_STRING			"integral, contract enforcement, constructor threshold"
# include "./sequence_6.hpp"
#elif defined(USE_SEQUENCE_5)
# define  DESC_STRING			"integral, contract enforcement, constructor limit"
# include "./sequence_5.hpp"
#elif defined(USE_SEQUENCE_4)
# define  DESC_STRING			"integral, throw overflow_error"
# include "./sequence_4.hpp"
#elif defined(USE_SEQUENCE_3)
# define  DESC_STRING			"floating-point, contract enforcement"
# include "./sequence_3.hpp"
#elif defined(USE_SEQUENCE_2)
# define  DESC_STRING			"integral, contract enforcement"
# include "./sequence_2.hpp"
#elif defined(USE_SEQUENCE_1)
# define  DESC_STRING			"integral, no checking"
# include "./sequence_1.hpp"
#else
# error Must define one of the USE_SEQUENCE_1, USE_SEQUENCE_2, . . . USE_SEQUENCE_7
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

namespace std
{

	template <class S>
	S &operator <<(S &stm, stlsoft::uint32_t n)
	{
		return stm << static_cast<unsigned int>(n);
	}

	template <class S>
	S &operator <<(S &stm, stlsoft::uint64_t n)
	{
		char	sz[21];

		return stm << stlsoft::integer_to_string(sz, 21, n);
	}

} // namespace std


/* ////////////////////////////////////////////////////////////////////////// */

template <typename FS>
void dump_fs(FS const &fs)
{
	cout	<< endl 
			<< "Dumping instance " << &fs
#if defined(USE_SEQUENCE_5) || \
	defined(USE_SEQUENCE_6) || \
	defined(USE_SEQUENCE_7)
			<< "; empty=" << ((fs.empty()) ? "true" : "false")
#endif /* USE_SEQUENCE_? */
			<< endl;

	ss_typename_param_k FS::const_iterator	b	=	fs.begin();
	size_t									i	=	1;

#if 1
	for(; b != fs.end(); ++b, ++i)
#else /* ? 0 */
	for(; fs.end() != b; ++b, ++i)
#endif /* 0 */
	{
		STLSOFT_ASSERT((1 == i) == (b == fs.begin()));

		cout << i << ": " << *b << endl;

		if(i > 1000)
		{
			cout << "More than 1000 elements enumerated. Terminating now ..." << endl;
			break;
		}
	}
}

static int main_(int /* argc */, char ** /*argv*/)
{
#if defined(USE_SEQUENCE_1) || \
	defined(USE_SEQUENCE_2) || \
	defined(USE_SEQUENCE_3) || \
	defined(USE_SEQUENCE_4)

	Fibonacci_sequence		fs;

	dump_fs(fs);

#elif defined(USE_SEQUENCE_5)

# ifdef XSTL_FIBONACCI_USE_64BIT
	Fibonacci_sequence		fs(93);
# else /* ? XSTL_FIBONACCI_USE_64BIT */
	Fibonacci_sequence		fs(47);
# endif /* XSTL_FIBONACCI_USE_64BIT */

	dump_fs(fs);

#elif defined(USE_SEQUENCE_6)

# ifdef XSTL_FIBONACCI_USE_64BIT
	Fibonacci_sequence		fs(__STLSOFT_GEN_UINT64_SUFFIX(12200160415121876738));
# else /* ? XSTL_FIBONACCI_USE_64BIT */
	Fibonacci_sequence		fs(2971215073);
# endif /* XSTL_FIBONACCI_USE_64BIT */

	dump_fs(fs);


#elif defined(USE_SEQUENCE_7)

	{
# ifdef XSTL_FIBONACCI_USE_64BIT
	Fibonacci_sequence		fs(Fibonacci_sequence::limit(93));
# else /* ? XSTL_FIBONACCI_USE_64BIT */
	Fibonacci_sequence		fs(Fibonacci_sequence::limit(47));
# endif /* XSTL_FIBONACCI_USE_64BIT */

	dump_fs(fs);
	}

	{
# ifdef XSTL_FIBONACCI_USE_64BIT
	Fibonacci_sequence		fs(Fibonacci_sequence::threshold(__STLSOFT_GEN_UINT64_SUFFIX(12200160415121876738)));
# else /* ? XSTL_FIBONACCI_USE_64BIT */
	Fibonacci_sequence		fs(Fibonacci_sequence::threshold(2971215073));
# endif /* XSTL_FIBONACCI_USE_64BIT */

	dump_fs(fs);
	}

#elif defined(USE_SEQUENCE_7)
	{
		Fibonacci_sequence		fs(Fibonacci_sequence::limit(47));

		fs.empty();

		dump_fs(fs);
	}

	{
		Fibonacci_sequence	fs(Fibonacci_sequence::limit(0));

		dump_fs(fs);
	}

	{
		Fibonacci_sequence	fs(Fibonacci_sequence::limit(1));

		dump_fs(fs);
	}

	{
		Fibonacci_sequence	fs(Fibonacci_sequence::limit(10));

		dump_fs(fs);
	}

	{
		Fibonacci_sequence	fs(Fibonacci_sequence::limit(47));

		dump_fs(fs);
	}

	{
		Fibonacci_sequence	fs(Fibonacci_sequence::threshold(0));

		dump_fs(fs);
	}

	{
		Fibonacci_sequence	fs(Fibonacci_sequence::threshold(1));

		dump_fs(fs);
	}

	{
		Fibonacci_sequence	fs(Fibonacci_sequence::threshold(2));

		dump_fs(fs);
	}

	{
		Fibonacci_sequence	fs(Fibonacci_sequence::threshold(47));

		dump_fs(fs);
	}

	{
		Fibonacci_sequence	fs(Fibonacci_sequence::threshold(100));

		dump_fs(fs);
	}

	{
		Fibonacci_sequence	fs(Fibonacci_sequence::threshold(1000000));

		dump_fs(fs);
	}

	{
		Fibonacci_sequence	fs(Fibonacci_sequence::threshold(1000000000));
		dump_fs(fs);
	}

	{
		Fibonacci_sequence	fs(Fibonacci_sequence::threshold(2971215073));
		dump_fs(fs);
	}

#if 0
	{
		typedef Fibonacci_sequence::traits_type	traits_t;
		Fibonacci_sequence	fs(Fibonacci_sequence::threshold(traits_t::maxThreshold));

		dump_fs(fs);
	}
#endif /* 0 */

	{
		Fibonacci_sequence	fs;

		dump_fs(fs);
	}

#if 0
	{
		Fibonacci_sequence	fs(Fibonacci_sequence::threshold(__STLSOFT_GEN_UINT64_SUFFIX(12200160415121876738)));

		dump_fs(fs);
	}
#endif /* 0 */

	return 0;
#endif

#if 0

	/* . */
#if defined(USE_SEQUENCE_4)
	Fibonacci_sequence	fs(1836311904);
#elif defined(USE_SEQUENCE_3)
	Fibonacci_sequence	fs(25);
#else
	Fibonacci_sequence	fs;
#endif

#if 0
	{
		Fibonacci_sequence::const_iterator	b	=	fs.begin();

		{ for(size_t i = 0; i < 47; ++i, ++b)
		{
		}}

		Fibonacci_sequence::value_type		v	=	*b;

		{ for(size_t i = 0; i < 0xFFFFFFFF/* 000 */; ++i, ++b)
		{
			if(*b < v)
			{
				v = *b;
			}

			if(0 == *b)
			{
				printf("i=%lu; i0=%lu; i1=%lu\n", i, b.i0(), b.i1());
			}
		}}

		printf("min: %lu\n", v);

		return 0;
	}
#endif /* 0 */

#if defined(USE_SEQUENCE_1) || \
	defined(USE_SEQUENCE_3) || \
	defined(USE_SEQUENCE_4)
	std::copy(fs.begin(), fs.end(), std::ostream_iterator<Fibonacci_sequence::value_type>(cout, "\n"));
#else /* ? sequence_n */
# if 1
	{ size_t i = 1;
	try
	{
		Fibonacci_sequence::value_type	prev	=	0.0;

		for(Fibonacci_sequence::const_iterator b = fs.begin(); ; ++b, ++i)
		{
			if(stlsoft::is_integral_type<Fibonacci_sequence::value_type>::value)
			{
				printf("%I64u, ", static_cast<stlsoft::uint64_t>(*b));
			}
			else
			{
				Fibonacci_sequence::value_type	current	=	*b;
				Fibonacci_sequence::value_type	ratio	=	(0 != prev) ? (current / prev) : 0.0;
				Fibonacci_sequence::value_type	ab		=	fabs(current);

				printf("%u: %G=>%G = %G\n", i, static_cast<double>(prev), static_cast<double>(current), static_cast<double>(ratio));
				prev = current;

				if(current != ab)
				{
					break;
				}

				if( _isnan(current) ||
					!_finite(current))
				{
					break;
				}

#  if 0
				if(i > 186)
				{
					break;
				}
#  endif /* 0 */
			}
		}
	}
	catch(...)
	{
		printf("\nn=%u\n", i);
	}
	}
# else /* ? 0 */
#  if 0
	stlsoft::copy_n(fs.begin(), 60, std::ostream_iterator<Fibonacci_sequence::value_type>(cout, ", "));
#  else /* ? 0 */
//	std::copy(fs.begin(), fs.end(), std::ostream_iterator<Fibonacci_sequence::value_type>(cout, "\n"));
	std::copy(fs.begin(), fs.end(), std::ostream_iterator<Fibonacci_sequence::value_type>(cout, " "));
#  endif /* 0 */
# endif /* 0 */
#endif /* sequence */
#endif /* 0 */

    return 0;
}

int main(int argc, char *argv[])
{
#if 0
	{ for(size_t i = 0; i < 0xFFFFFFFF; ++i) {} }
#endif /* 0 */

	try
	{
		puts("Fibonacci_sequence_test: " __STLSOFT_COMPILER_LABEL_STRING "; " DESC_STRING);

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
