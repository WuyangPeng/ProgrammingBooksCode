/* /////////////////////////////////////////////////////////////////////////////
 * File:        environment_thread_test.cpp
 *
 * Purpose:     Implementation file for the environment_thread_test project.
 *
 * Created:     9th December 2005
 * Updated:     30th December 2005
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright 1999-2005, Synesis Software Pty Ltd.
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

#ifdef unix
//# define _SYSTYPE_BSD
# include <unixem/setenv.h>
# include <unixem/implicit_link.h>
#endif

/* PlatformSTL Header Files */
#include <platformstl/environment_map.hpp>

/* PThreads Header Files */
#include <pthread.h>
#include <sched.h>

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
#include <stdlib.h>

#if defined(_MSC_VER) && \
	defined(_DEBUG)
# include <crtdbg.h>
#endif /* _MSC_VER) && _DEBUG */

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

#if 0
typedef std::string		string_t;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

static void *thread_proc(void *);


#if 0

#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	{
		platformstl::environment_map	env;

#ifdef PLATFORMSTL_ENVVAR_HAS_ENVIRON
		puts("Enumerating range:");
		{ for(platformstl::environment_map::const_iterator b = env.begin(); b != env.end(); ++b)
		{
			::fprintf(stdout, "  %s=%s\n", (*b).first.c_str(), (*b).second.c_str());
		}}
		puts("");

		puts("Enumerating range and calling erase() on each iterator");
		{ for(platformstl::environment_map::const_iterator b = env.begin(); b != env.end(); )
		{
			platformstl::environment_map::const_iterator del	=	b;

			++b;

			env.erase(del);
		}}
		puts("");

		puts("Enumerating range:");
		{ for(platformstl::environment_map::const_iterator b = env.begin(); b != env.end(); ++b)
		{
			::fprintf(stdout, "  %s=%s\n", (*b).first.c_str(), (*b).second.c_str());
		}}
		puts("");
#endif /* PLATFORMSTL_ENVVAR_HAS_ENVIRON */

		puts("");
		try
		{
			fprintf(stdout, "  SOMETHING_NOT_LIKELY_TO_B_DEFINED=%s\n", stlsoft::c_str_ptr(stlsoft::c_str_ptr(env["SOMETHING_NOT_LIKELY_TO_B_DEFINED"])));
		}
		catch(std::out_of_range &)
		{
			fprintf(stdout, "  SOMETHING_NOT_LIKELY_TO_B_DEFINED is not defined\n");
		}
		puts("");

#ifdef PLATFORMSTL_ENVVAR_SET_SUPPORTED
		env.insert("SOMETHING_NOT_LIKELY_TO_B_DEFINED", "Rabbit stew");
#endif /* PLATFORMSTL_ENVVAR_SET_SUPPORTED */

		puts("");
		try
		{
			fprintf(stdout, "  SOMETHING_NOT_LIKELY_TO_B_DEFINED=%s\n", stlsoft::c_str_ptr(stlsoft::c_str_ptr(env["SOMETHING_NOT_LIKELY_TO_B_DEFINED"])));
		}
		catch(std::out_of_range &)
		{
			fprintf(stdout, "  SOMETHING_NOT_LIKELY_TO_B_DEFINED is not defined\n");
		}
		puts("");

#ifdef PLATFORMSTL_ENVVAR_HAS_ENVIRON
		platformstl::environment_map::const_iterator b_outer	=	env.begin();
		platformstl::environment_map::const_iterator e_outer	=	env.end();
#endif /* PLATFORMSTL_ENVVAR_HAS_ENVIRON */

		env.refresh();

#ifdef PLATFORMSTL_ENVVAR_SET_SUPPORTED
		env.insert("SOMETHING_NOT_LIKELY_TO_B_DEFINED", "Rabbit stew (2)");
#endif /* PLATFORMSTL_ENVVAR_SET_SUPPORTED */

#ifdef PLATFORMSTL_ENVVAR_HAS_ENVIRON
		puts("Enumerating range:");
		{ for(platformstl::environment_map::const_iterator b = b_outer; b != e_outer; ++b)
		{
			::fprintf(stdout, "  %s=%s\n", (*b).first.c_str(), (*b).second.c_str());
		}}
		puts("");

		puts("Enumerating range:");
		{ for(platformstl::environment_map::const_iterator b = env.begin(); b != env.end(); ++b)
		{
			::fprintf(stdout, "  %s=%s\n", (*b).first.c_str(), (*b).second.c_str());
		}}
		puts("");
#endif /* PLATFORMSTL_ENVVAR_HAS_ENVIRON */
	}

	/* . */
	pthread_t	threads[2];

	{ for(size_t i = 0; i < sizeof(threads) / sizeof(0[threads]); ++i)
	{
		void	*arg	=	NULL;

		if(0 != pthread_create(&threads[i], NULL, thread_proc, arg))
		{
			fprintf(stderr, "Failed to create thread %d\n", i);

			return EXIT_FAILURE;
		}
	}}

	{ for(size_t i = 0; i < sizeof(threads) / sizeof(0[threads]); ++i)
	{
		void	*arg	=	NULL;

		if(0 != pthread_join(threads[i], NULL))
		{
			fprintf(stderr, "Failed to join thread %d\n", i);

			return EXIT_FAILURE;
		}
	}}

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
		puts("environment_thread_test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */


		iRet = main_(argc, argv);
	}
	catch(std::exception &x)
	{
		fprintf(stderr, "Unhandled error: %s\n", x.what());

		iRet = EXIT_FAILURE;
	}
	catch(...)
	{
		fprintf(stderr, "Unhandled unknown error\n");

		iRet = EXIT_FAILURE;
	}

#if defined(_MSC_VER) && \
	defined(_DEBUG)
    _CrtMemDumpAllObjectsSince(&memState);
#endif /* _MSC_VER) && _DEBUG */

	return iRet;
}

/* ////////////////////////////////////////////////////////////////////////// */

static void *thread_proc(void *)
{
	// TODO: Do some threading stuff

	return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
