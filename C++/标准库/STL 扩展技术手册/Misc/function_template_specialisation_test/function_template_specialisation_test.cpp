/* /////////////////////////////////////////////////////////////////////////////
 * File:        function_template_specialisation_test.cpp
 *
 * Purpose:     Implementation file for the function_template_specialisation_test project.
 *
 * Created:     29th April 2005
 * Updated:     30th December 2005
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


/* Standard C Header Files */
#include <stdio.h>

/* Standard C++ Header Files */
#include <exception>
#include <iostream>

#ifdef __WATCOMC__
namespace std
{
	using ::exception;
}
#endif /* __WATCOMC__ */


/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

#if (   defined(WIN32) || \
        defined(_WIN32)) && \
    !defined(_INC_WINDOWS)
extern "C" void __stdcall Sleep(unsigned long);
#endif /* WIN32 */

/* ////////////////////////////////////////////////////////////////////////// */

namespace Test0
{
	template <typename T>
	inline T multiply(T *t1, T *t2)
	{
		return *t1 * *t2;
	}

	template <typename T>
	inline T multiply(T t1, T t2)
	{
		return t1 * t2;
	}

	template <>
	inline short multiply<short>(short t1, short t2)
	{
		return t1 * t2 * 2;
	}

	template <>
	inline long multiply<long>(long *t1, long *t2)
	{
#if 1
		return *t1 * *t2 * 4;
#else /* ? 0 */
		static long l	=	*t1 * *t2 * 4;

		return &l;
#endif /* 0 */
	}


} // namespace Test0

void test0()
{
	using Test0::multiply;

	std::cout	<< "char:  "
				<< (int)multiply(char(2), char(3))
				<< std::endl;

	std::cout	<< "short: "
				<< multiply(short(2), short(3))
				<< std::endl;

	std::cout	<< "int:   "
				<< multiply(int(2), int(3))
				<< std::endl;

	std::cout	<< "long:  "
				<< multiply(long(2), long(3))
				<< std::endl;

	{
		const long l1	=	2;
		const long l2	=	3;

		std::cout	<< "&long: "
					<< multiply(&l1, &l2)
					<< std::endl;
	}
}

/* ////////////////////////////////////////////////////////////////////////// */

namespace Test1
{
	template <typename T>
	inline T multiply(T const &t1, T const &t2)
	{
		return t1 * t2;
	}

	inline long multiply(long t1, long t2)
	{
		return t1 * t2 * 100;
	}

	template <>
	inline short multiply<short>(short const &t1, short const &t2)
	{
		return t1 * t2 * 200;
	}

} // namespace Test1

void test1()
{
	using Test1::multiply;

	std::cout	<< "char:  "
				<< (int)multiply(char(2), char(3))
				<< std::endl;

	std::cout	<< "short: "
				<< multiply(short(2), short(3))
				<< std::endl;

	std::cout	<< "int:   "
				<< multiply(int(2), int(3))
				<< std::endl;

	std::cout	<< "long:  "
				<< multiply(long(2), long(3))
				<< std::endl;
}

/* ////////////////////////////////////////////////////////////////////////// */

#if 0
namespace Test2
{
#if 0
	template <typename T, typename T2>
	inline T multiply(T /* const & */t1, T /* const & */t2, T2)
	{
		return t1 * t2;
	}

#if 0
	inline long multiply(long t1, long t2, int)
	{
		return t1 * t2 * 100;
	}
#else /* ? 0 */

	template <>
	inline const long multiply<const long>(const long t1, const long t2, int)
	{
		return t1 * t2 * 100;
	}

	template <>
	inline long multiply<long const *, int>(long const *t1, long const *t2, int)
	{
		return *t1 * *t2 * 100;
	}
#endif /* 0 */

	template <>
	inline short multiply<short, int>(short /* const & */t1, short /* const & */t2, int)
	{
		return t1 * t2 * 200;
	}
#else /* ? 0 */


	template <typename T>
	inline T multiply(T /* const & */t1, T /* const & */t2, int)
	{
		return t1 * t2;
	}

#if 0
	inline long multiply(long t1, long t2, int)
	{
		return t1 * t2 * 100;
	}
#else /* ? 0 */

	template <>
	inline const long multiply<const long>(const long t1, const long t2, int)
	{
		return t1 * t2 * 100;
	}

	template <>
	inline long multiply<long const *>(long const *t1, long const *t2, int)
	{
		return *t1 * *t2 * 100;
	}
#endif /* 0 */

	template <>
	inline short multiply<short, int>(short /* const & */t1, short /* const & */t2, int)
	{
		return t1 * t2 * 200;
	}
#endif /* 0 */

} // namespace Test2

void test2()
{
	using Test2::multiply;

	std::cout	<< "char:  "
				<< (int)multiply(char(2), char(3), 0)
				<< std::endl;

	std::cout	<< "short: "
				<< multiply(short(2), short(3), 0)
				<< std::endl;

	std::cout	<< "int:   "
				<< multiply(int(2), int(3), 0)
				<< std::endl;

	std::cout	<< "long:  "
				<< multiply(long(2), long(3), 0)
				<< std::endl;

	{
		long l1	=	2;
		long l2	=	3;

		std::cout	<< "&long: "
					<< multiply(&l1, &l2, 0)
					<< std::endl;
	}
}
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

namespace Test3
{
	template <typename T, typename T2>
	inline T multiply(T const &t1, T const &t2, T2)
	{
		return t1 * t2;
	}

	inline long multiply(long t1, long t2, int)
	{
		return t1 * t2 * 100;
	}

	template <>
	inline short multiply<short>(short const &t1, short const &t2, int)
	{
		return t1 * t2 * 200;
	}

} // namespace Test3

void test3()
{
	using Test3::multiply;

	std::cout	<< "char:  "
				<< (int)multiply(char(2), char(3), 0)
				<< std::endl;

	std::cout	<< "short: "
				<< multiply(short(2), short(3), 0)
				<< std::endl;

	std::cout	<< "int:   "
				<< multiply(int(2), int(3), 0)
				<< std::endl;

	std::cout	<< "long:  "
				<< multiply(long(2), long(3), 0)
				<< std::endl;

}

/* ////////////////////////////////////////////////////////////////////////// */

#if 0
namespace Test4
{
	template <typename T, typename T2>
	inline T multiply(T const &t1, T const &t2, T2)
	{
		return t1 * t2;
	}

	template <typename T, typename T2>
	inline T multiply(T const *t1, T const *t2, T2)
	{
		return *t1 * *t2 * 300;
	}

#if 0
	inline long multiply(long const *t1, long const *t2, int)
	{
		return *t1 * *t2 * 100;
	}
#endif /* 0 */

	template <>
	inline short multiply<short>(short const &t1, short const &t2, int)
	{
		return t1 * t2 * 200;
	}

#if 0
	template <>
	inline long multiply<long const *>(long const *&t1, long const *&t2, int)
	{
		return *t1 * *t2 * 200;
	}
#endif /* 0 */

} // namespace Test4

void test4()
{
	using Test4::multiply;

	std::cout	<< "char:  "
				<< (int)multiply(char(2), char(3), 0)
				<< std::endl;

	std::cout	<< "short: "
				<< multiply(short(2), short(3), 0)
				<< std::endl;

	std::cout	<< "int:   "
				<< multiply(int(2), int(3), 0)
				<< std::endl;

	std::cout	<< "long:  "
				<< multiply(long(2), long(3), 0)
				<< std::endl;

	{
		long l1	=	2;
		long l2	=	3;

		std::cout	<< "&long: "
					<< multiply(&l1, &l2, 0)
					<< std::endl;
	}
}
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
	puts("function_template_specialisation_test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

	/* . */
	puts("Test 0");
	test0();
	puts("");

	puts("Test 1");
	test1();
	puts("");

#if 0
	puts("Test 2");
	test2();
	puts("");
#endif /* 0 */

	puts("Test 3");
	test3();
	puts("");

#if 0
	puts("Test 4");
	test4();
	puts("");
#endif /* 0 */

    return 0;
}

int main(int argc, char *argv[])
{
#if 0
	::Sleep(100000);
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
