/* /////////////////////////////////////////////////////////////////////////////
 * File:        RandomAccessNonContiguity_test.cpp
 *
 * Purpose:     Implementation file for the RandomAccessNonContiguity_test project.
 *
 * Created:     1st September 2004
 * Updated:     20th November 2005
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2004-2005, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              This source code is placed into the public domain 2004
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

/* Standard C++ Header Files */
#if defined(__DMC__)
# include <iostream.h>
#else /* ? __DMC__ */
# include <iostream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
#endif /* __DMC__ */

#include <deque>
#include <map>

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

#if (   defined(WIN32) || \
        defined(_WIN32)) && \
    !defined(_INC_WINDOWS)
extern "C" void __stdcall Sleep(unsigned long);
#endif /* WIN32 */

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
	::Sleep(100000);
#endif /* 0 */

#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
	cout << "RandomAccessNonContiguity_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
#endif /* debug */

	/* . */
    typedef std::deque<int>     cont_t;
    typedef std::map<int, int>  map_t;

    cont_t  cont;
    map_t   counts;

    { for(int i = 0; i < 100000; ++i)
    {
        cont.push_back(i);
    }}

    { for(int i = 0; i < cont.size() - 1; ++i)
    {
        int *p1     =   &cont[i];
        int *p2     =   &cont[i + 1];

        int diff    =   p2 - p1;

        ++counts[diff];
    }}

    { for(map_t::const_iterator b = counts.begin(); b != counts.end(); ++b)
    {
        cout << (*b).first << ": " << (*b).second << endl;
    }}

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
