/* /////////////////////////////////////////////////////////////////////////////
 * File:        fixed_reference_test.cpp
 *
 * Purpose:     Implementation file for the fixed_reference_test project.
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
#include <stlsoft/fixed_array.hpp>


/* Standard C++ Header Files */
#include <exception>

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

class Stevie
{
public:
  Stevie(size_t dim0, size_t dim1)
    : m_array(dim0, dim1)
    , m_00(m_array[0][0])
  {
	  int	&i	=	m_array[0][0];

	  i = 1;
	  i = 2;
  }
  ~Stevie()
  {
//    *m_00 = 0; // Well-defined
  }
private:
  stlsoft::fixed_array_2d<int>  m_array;
  int                           &m_00;
};


/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
	puts("fixed_reference_test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

	/* . */
	Stevie	s(2, 2);

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
