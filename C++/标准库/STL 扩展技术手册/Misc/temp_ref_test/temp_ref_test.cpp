/* /////////////////////////////////////////////////////////////////////////////
 * File:        temp_ref_test.cpp
 *
 * Purpose:     Implementation file for the temp_ref_test project.
 *
 * Created:     9th July 2004
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

#include <iostream>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

#include <string>

typedef std::string			string_t;

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

#if (   defined(WIN32) || \
        defined(_WIN32)) && \
    !defined(_INC_WINDOWS)
extern "C" void __stdcall Sleep(unsigned long);
#endif /* WIN32 */

/* ////////////////////////////////////////////////////////////////////////// */

struct Thing
{
public:
	Thing(char const *name)
		: m_name(name)
	{}

public:
	string_t	m_name;
};

Thing byVal(char const *name)
{
	return Thing(name);
}

Thing &byRef(char const *name)
{
	return byVal(name);
}

class ThingArray
{
public:
	Thing operator [](size_t 
};

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
	::Sleep(100000);
#endif /* 0 */

	/* . */
	cout << "Name: " << byRef("The Dr").m_name << endl;

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
