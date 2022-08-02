/* /////////////////////////////////////////////////////////////////////////
 * File:        msi_perf_test.cpp
 *
 * Purpose:     Implementation file for the msi_perf_test project.
 *
 * Created:     31st January 2007
 * Updated:     31st January 2007
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2007-2007, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////// */




/* STLSoft Header Files */
#include <stlsoft/iterators/member_selector_iterator.hpp>
#include <stlsoft/memory/auto_buffer.hpp>

/* PlatformSTL Header Files */
#include <platformstl/performance/performance_counter.hpp>


/* Standard C++ Header Files */
#include <exception>
#include <iostream>
#include <algorithm>
#include <numeric>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

/* Standard C Header Files */
#include <stdlib.h>

#if defined(_MSC_VER) && \
    defined(_DEBUG)
# include <crtdbg.h>
#endif /* _MSC_VER) && _DEBUG */


#include "slice.h"

/* /////////////////////////////////////////////////////////////////////////
 * Macros and definitions
 */


/* /////////////////////////////////////////////////////////////////////////
 * Globals
 */


/* /////////////////////////////////////////////////////////////////////////
 * Typedefs
 */


/* /////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

/* ////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	platformstl::performance_counter	counter;
	stlsoft::auto_buffer<slice_t>		slices(100000);

	::srand(slices.size());

	{ for(size_t i = 0; i < slices.size(); ++i)
	{
		slices[i].len = ::rand();
	}}

#if 0
	std::generate(	stlsoft::member_selector(slices.begin(), &slice_t::len)
				,	stlsoft::member_selector(slices.end(), &slice_t::len)
				,	::rand);
#endif /* 0 */

	size_t			total0	=	0;
	size_t			total1	=	0;
	unsigned long	time0;
	unsigned long	time1;

	const unsigned	ITERATIONS	=	200;

	{ for(int WARMUPS = 2; WARMUPS > 0; --WARMUPS)
	{
		counter.start();
		{ for(unsigned i = 0; i < ITERATIONS; ++i)
		{
			total0 += std::accumulate(	slices.begin()
									,	slices.end()
									,	size_t(0)
									,	sum_slice);
		}}
		counter.stop();
		time0 = static_cast<unsigned long>(counter.get_milliseconds());

		counter.start();
		{ for(unsigned i = 0; i < ITERATIONS; ++i)
		{
			total1 += std::accumulate(	stlsoft::member_selector(slices.begin(), &slice_t::len)
									,	stlsoft::member_selector(slices.end(), &slice_t::len)
									,	size_t(0));
		}}
		counter.stop();
		time1 = static_cast<unsigned long>(counter.get_milliseconds());

		if(total0 != total1)
		{
			cerr << total0 << " != " << total1 << "!" << endl;
		}
	}}

	cout << "with custom function: " << time0 << endl;
	cout << "with member_selector: " << time1 << endl;

	
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    int             res;

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemState    memState;
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
        cout << "msi_perf_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
#endif /* debug */

        res = main_(argc, argv);
    }
    catch(std::exception &x)
    {
        cerr << "Unhandled error: " << x.what() << endl;

        res = EXIT_FAILURE;
    }
    catch(...)
    {
        cerr << "Unhandled unknown error" << endl;

        res = EXIT_FAILURE;
    }

#if defined(_MSC_VER) && \
    defined(_DEBUG)
    _CrtMemDumpAllObjectsSince(&memState);
#endif /* _MSC_VER) && _DEBUG */

    return res;
}

/* ////////////////////////////////////////////////////////////////////// */
