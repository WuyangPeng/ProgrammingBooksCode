/* /////////////////////////////////////////////////////////////////////////////
 * File:        invalidateable_reference_test.cpp
 *
 * Purpose:     Implementation file for the invalidateable_reference_test project.
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
#include <stlsoft/stlsoft.h>
#include <stlsoft/conversion/integer_to_string.hpp>

/* Standard C++ Header Files */
#include <exception>
#include <iostream>
#include <list>
#include <string>
#include <vector>

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

class integer
{
public:
	integer(int value)
		: m_value(value)
	{
		m_instance = nextInstance();
	}

public:
	int	value() const
	{
		return m_value;
	}
	int	instance() const
	{
		return m_instance;
	}

public:
	static int &nextInstance(int i = -1)
	{
		static int s_instance	=	0;

		if(i >= 0)
		{
			s_instance = i;
		}
		else
		{
			++s_instance;
		}

		return s_instance;
	}

private:
	int	m_value;
	int	m_instance;
};

template <typename S>
inline S &operator <<(S &stm, integer i)
{
	stm << i.value() << "(" << i.instance() << ")";

	return stm;
}

/* ////////////////////////////////////////////////////////////////////////// */

class intstr
{
public:
	intstr(int value)
	{
		char	sz[21];

		m_value = stlsoft::integer_to_string(&sz[0], 21, value);

		m_instance = nextInstance();
	}
	~intstr()
	{
		m_value = "Maybe Moby";
	}

public:
	std::string const &value() const
	{
		return m_value;
	}
	int	instance() const
	{
		return m_instance;
	}

public:
	static int &nextInstance(int i = -1)
	{
		static int s_instance	=	0;

		if(i >= 0)
		{
			s_instance = i;
		}
		else
		{
			++s_instance;
		}

		return s_instance;
	}

private:
	std::string	m_value;
	int			m_instance;
};

template <typename S>
inline S &operator <<(S &stm, intstr i)
{
	stm << i.value() << "(" << i.instance() << ")";

	return stm;
}


/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
#if 1
	typedef	int		value_t;
#else /* ? 0 */
# if 0
	typedef	integer	value_t;
# else /* ? 0 */
	typedef	intstr	value_t;
# endif /* 0 */
#endif /* 0 */

	/* . */
	{
		std::vector<int> vi(10);

		vi.reserve(10); // Remember that reserve() might reserve more than requested, . . .

		int &ri = vi[0];

		vi.resize(vi.capacity() + 1); // . . ., so ask for cap+1 to be sure

		int i = ri; // Error!

	}

	{
		integer::nextInstance(0);

		std::vector<value_t>  vi;

		vi.push_back(10);
		vi.push_back(20);

		std::vector<value_t>::iterator	b	=	vi.begin();
		std::vector<value_t>::iterator	b2	=	vi.begin();

		value_t &ri0 = *b;
		value_t &ri1 = *++b2;

		vi.erase(b);

		value_t i0 = ri0;
		value_t i1 = ri1; // Beware: here there be dragons

		cout << "i0=" << i0 << "; i1=" << i1 << endl;
	}

	{
		integer::nextInstance(0);

		std::list<value_t>  li;

		li.push_back(10);
		li.push_back(20);

		std::list<value_t>::iterator	b	=	li.begin();
		std::list<value_t>::iterator	b2	=	b;

		value_t &ri0 = *b;
		value_t &ri1 = *++b2;

		li.erase(b);

		value_t i0 = ri0; // Beware: here there be dragons
		value_t i1 = ri1;

		cout << "ri0=" << i0 << "; ri1=" << i1 << endl;
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
		puts("invalidateable_reference_test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */
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
