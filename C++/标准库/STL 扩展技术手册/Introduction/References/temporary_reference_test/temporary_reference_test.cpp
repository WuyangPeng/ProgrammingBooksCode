/* /////////////////////////////////////////////////////////////////////////////
 * File:        temporary_reference_test.cpp
 *
 * Purpose:     Implementation file for the temporary_reference_test project.
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


/* Open-RJ Header Files */
#include <openrj/stl/openrj.hpp>
#include <openrj/stl/field.hpp>
#include <openrj/stl/record.hpp>
#include <openrj/stl/database.hpp>

/* Standard C++ Header Files */
#include <iostream>
#include <exception>

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

#if 0
template <typename I>
std::iterator_traits<I>::reference get_iter_ref(I i)
{
	return *i;
}
#else
openrj::stl::record::const_reference get_iter_ref(openrj::stl::record::const_iterator i)
{
	return *i;
}
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */


openrj::stl::record::const_reference get_a_reference(openrj::stl::memory_database &db)
{
	openrj::stl::record						record	=	db[0];
	openrj::stl::record::const_iterator		it		=	record.begin();

	return get_iter_ref(it);
}

static int main_(int /* argc */, char ** /*argv*/)
{
	/* . */
	{
		openrj::stl::memory_database			db("name:rebel\n%%\n");
		openrj::stl::record::const_reference	r	=	get_a_reference(db);

		cout << r << endl;
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
		puts("temporary_reference_test: " __STLSOFT_COMPILER_LABEL_STRING);
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
