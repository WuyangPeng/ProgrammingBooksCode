/* /////////////////////////////////////////////////////////////////////////////
 * File:        backwards_available_test.cpp
 *
 * Purpose:     Implementation file for the backwards_available_test project.
 *
 * Created:     29th April 2005
 * Updated:     10th January 2006
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2005-2006, Synesis Software Pty Ltd.
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


/* Standard C Header Files */
#include <stdio.h>

/* Standard C++ Header Files */
#include <exception>

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

namespace main1
{
	template <typename T>
	struct some_traits;

	template <typename T>
	void fn_use_traits(T const &thing)
	{
	  some_traits<T>::f(thing);
	}

	class Thing
	{
	};

	template <>
	struct some_traits<Thing>
	{
	  static void f(Thing const &thing)
	  {
		printf("&thing: %p\n", &thing);
	  }
	};

	int main_(int /* argc */, char ** /*argv*/)
	{
	  Thing thing;

#if 0
	  typedef some_traits<Thing>  Thing_traits_t;

	  Thing_traits_t::f(thing);
#else /* ? 0 */
	  fn_use_traits(thing);
#endif /* 0 */

	  return 0;
	}
}

namespace main2
{
	template <typename T>
	struct addr_printer
	{
		static void f(T const &t)
		{
			printf("&thing: %p\n", get_addr(t));
		}
	};

	void const *get_addr(int const &i)
	{
 		return &i;
	}

	class Thing
	{
	};

	void const *get_addr(Thing const &thing)
	{
		return &thing;
	}

	int main_(int /* argc */, char ** /*argv*/)
	{
	  typedef addr_printer<Thing>  Thing_printer_t;

	  Thing thing;

	  Thing_printer_t::f(thing);

	  return 0;
	}
}

/* ////////////////////////////////////////////////////////////////////////// */

int main(int argc, char *argv[])
{
#if 0
	::Sleep(100000);
#endif /* 0 */

	try
	{
		return main1::main_(argc, argv) || main2::main_(argc, argv);
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
