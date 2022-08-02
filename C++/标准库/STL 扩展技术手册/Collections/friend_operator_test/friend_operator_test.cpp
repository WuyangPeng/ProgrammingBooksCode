/* /////////////////////////////////////////////////////////////////////////////
 * File:        friend_operator_test.cpp
 *
 * Purpose:     Implementation file for the friend_operator_test project.
 *
 * Created:     10th September 2005
 * Updated:     6th January 2006
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

/* Standard C++ Header Files */
#include <exception>
#include <iostream>

#if !defined(__WATCOMC__) && \
    (   !defined(_MSC_VER) || \
        _MSC_VER >= 1100)

using std::cerr;
using std::cin;
using std::cout;
using std::endl;

#else /* ? __WATCOMC__ */
namespace std
{
    using ::exception;
}
#endif /* __WATCOMC__ */


/* Standard C Header Files */
#include <stdlib.h>

/* /////////////////////////////////////////////////////////////////////////////
 * Class declarations
 */


//#define TEST_TC



class ntc
{
public:
	explicit ntc(int i)
		: m_i(i)
	{}

public:
	friend bool operator ==(ntc const &lhs, ntc const &rhs)
	{
		return lhs.m_i == rhs.m_i;
	}
	friend bool operator ==(ntc const &lhs, int rhs)
	{
		return lhs.m_i == rhs;
	}
	friend bool operator ==(int lhs, ntc const &rhs)
	{
		return lhs == rhs.m_i;
	}
	friend bool operator !=(ntc const &lhs, ntc const &rhs)
	{
		return !operator ==(lhs, rhs);
	}

private:
	int	m_i;
};

#ifdef TEST_TC
template <class T>
class tc
{
public:
	explicit tc(T const &i)
		: m_i(i)
	{}

	typedef tc<T>	tc_type;

public:
	friend template <class T2>
	bool operator ==(tc<T2> const &lhs, tc<T2> const &rhs);
	friend template <class T2>
	bool operator !=(tc<T2> const &lhs, tc<T2> const &rhs);

private:
	T	m_i;
};

	template <class T>
	inline bool operator ==(tc<T> const &lhs, tc<T> const &rhs)
	{
		return lhs.m_i == rhs.m_i;
	}
	template <class T>
	inline bool operator !=(tc<T> const &lhs, tc<T> const &rhs)
	{
		return !operator ==(lhs, rhs);
	}

#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	if(ntc(1) == ntc(2))
	{}

	if(ntc(1) != ntc(2))
	{}

	if(ntc(1) == 2)
	{}

	if(1 == ntc(2))
	{}

#ifdef TEST_TC
	if(tc<int>(1) == tc<int>(2))
	{}

	if(tc<int>(1) != tc<int>(2))
	{}
#endif /* 0 */

    return 0;
}

int main(int argc, char *argv[])
{
#if 0
	{ for(size_t i = 0; i < 0xffffffff; ++i){} }
#endif /* 0 */

	try
	{

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
