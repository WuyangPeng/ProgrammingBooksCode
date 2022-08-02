/* /////////////////////////////////////////////////////////////////////////////
 * File:        global_dereference_test.cpp
 *
 * Purpose:     Implementation file for the global_dereference_test project.
 *
 * Created:     29th May 2005
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


/* Standard C Header Files */

/* Standard C++ Header Files */
#include <exception>
#include <iostream>

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

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

#if (   defined(WIN32) || \
        defined(_WIN32)) && \
    !defined(_INC_WINDOWS)
extern "C" void __stdcall Sleep(unsigned long);
#endif /* WIN32 */

/* ////////////////////////////////////////////////////////////////////////// */

class nt_iterator
{
public:
	nt_iterator()
	{}

public:
	nt_iterator &operator ++()
	{
		return *this;
	}
	nt_iterator operator ++(int)
	{
		return *this;
	}

	int operator *()
	{
		return 0;
	}
	const int operator *() const
	{
		return 0;
	}

	bool equal(nt_iterator const &rhs) const
	{
		return &rhs == this;
	}
};

inline int operator *(nt_iterator &rhs)
{
	return rhs.operator *();
}

inline int operator *(nt_iterator const &rhs)
{
	return rhs.operator *();
}

/* ////////////////////////////////////////////////////////////////////////// */

template <typename T>
class nt_iterator_t
{
public:
	nt_iterator_t()
	{}

public:
	nt_iterator_t &operator ++()
	{
		return *this;
	}
	nt_iterator_t operator ++(int)
	{
		return *this;
	}

	T &operator *()
	{
		return m_t;
	}
	const T &operator *() const
	{
		return m_t;
	}

	bool equal(nt_iterator_t const &rhs) const
	{
		return &rhs == this;
	}

private:
	T	m_t;
};

#if 0
template <typename T>
inline T &operator *(nt_iterator_t<T> &rhs)
{
	return rhs.operator *();
}

template <typename T>
inline T const &operator *(nt_iterator_t<T> const &rhs)
{
	return rhs.operator *();
}
#else /* ? 0 */
inline int &operator *(nt_iterator_t<int> &rhs)
{
	return rhs.operator *();
}

template <typename T>
inline int const &operator *(nt_iterator_t<int> const &rhs)
{
	return rhs.operator *();
}
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
#if 0
	::Sleep(100000);
#endif /* 0 */

#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
	cout << "global_dereference_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
#endif /* debug */

	/* . */
	{
		nt_iterator	nti;

//		*nti;
	}

	{
		nt_iterator_t<int>	nti;

		*nti;
	}

    return 0;
}

int main(int argc, char *argv[])
{
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
