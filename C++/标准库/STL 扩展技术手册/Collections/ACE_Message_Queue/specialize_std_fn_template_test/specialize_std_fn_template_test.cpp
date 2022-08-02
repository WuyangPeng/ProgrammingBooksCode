/* /////////////////////////////////////////////////////////////////////////////
 * File:        specialize_std_fn_template_test.cpp
 *
 * Purpose:     Implementation file for the specialize_std_fn_template_test project.
 *
 * Created:     18th June 2005
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


/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <iostream>
#include <list>

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
	Thing()
		: m_p(get_this_())
	{}

public:
	void const	*ptr() const
	{
		return m_p;
	}

private:
	Thing const	*get_this_() const
	{
		return this;
	}

private:
	Thing const	*m_p;
};

/* ////////////////////////////////////////////////////////////////////////// */

namespace std
{

#if 0
	inline void for_each(Thing const *f, Thing const *l, void (*fn)(Thing const &))
	{
		std::cout << "custom for_each" << std::endl;

		for(; f != l; ++f)
		{
			fn(*f);
		}
	}

	inline void for_each(Thing *f, Thing *l, void (*fn)(Thing const &))
	{
		for_each(const_cast<Thing const*>(f), const_cast<Thing const*>(l), fn);
	}
#else /* ? 0 */

# if 0
	template<typename F>
	inline void for_each(Thing const *f, Thing const *l, F fn)
	{
		std::cout << "custom for_each" << std::endl;

		for(; f != l; ++f)
		{
			fn(*f);
		}
	}

	template<typename F>
	inline void for_each(Thing *f, Thing *l, F fn)
	{
		for_each(const_cast<Thing const*>(f), const_cast<Thing const*>(l), fn);
	}
# else /* ? 0 */
	template<typename S, typename F>
	inline void for_each(S const *f, S const *l, F fn)
	{
		std::cout << "custom for_each" << std::endl;

		for(; f != l; ++f)
		{
			fn(*f);
		}
	}

	template<typename S, typename F>
	inline void for_each(S *f, S *l, F fn)
	{
		for_each(const_cast<Thing const*>(f), const_cast<Thing const*>(l), fn);
	}
# endif /* 0 */

#endif /* 0 */

#if 0
	void copy(	std::list<Thing>::iterator	f
			,	std::list<Thing>::iterator	l
			,	void (*fn)(Thing const &))
	{
		std::cout << "custom copy (1)" << std::endl;

		for(; f != l; ++f)
		{
			fn(*f);
		}
	}
#else /* ? 0 */

	template <typename O>
	void copy(	std::list<Thing>::iterator	f
			,	std::list<Thing>::iterator	l
			,	O							o)
	{
		std::cout << "custom copy (2); " << std::endl;

		for(; f != l; ++f)
		{
			*o = *f;
		}
	}

#endif /* 0 */


} // namespace std

/* ////////////////////////////////////////////////////////////////////////// */

void dump_S(Thing const &s)
{
	std::cout << "p: " << s.ptr() << std::endl;
}

template <typename S>
inline S &operator <<(S &stm, Thing const &thing)
{
	stm << "p=" << thing.ptr();

	return stm;
}

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	/* . */
	{
		Thing	s[4];

		std::for_each(&s[0], &s[4], dump_S);
	}

	{
		std::list<Thing>	items;

		items.push_back(Thing());
		items.push_back(Thing());
		items.push_back(Thing());
		items.push_back(Thing());
		items.push_back(Thing());

		std::copy(items.begin(), items.end(), std::ostream_iterator<Thing>(std::cout, " "));
	}

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
		cerr << "Unhandled error: " << x.what() << endl;
	}
	catch(...)
	{
		cerr << "Unhandled unknown error" << endl;
	}

	return EXIT_FAILURE;
}

/* ////////////////////////////////////////////////////////////////////////// */
