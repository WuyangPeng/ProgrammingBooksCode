/* /////////////////////////////////////////////////////////////////////////////
 * File:        glob_sequence_constructor_ambiguity_test.cpp
 *
 * Purpose:     Implementation file for the glob_sequence_constructor_ambiguity_test project.
 *
 * Created:     31st August 2005
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


/* /////////////////////////////////////////////////////////////////////////////
 * Class definitions
 */

class std_string;
class simple_string;

class cstyle_string
{
public:
	cstyle_string(char const *)
	{}
	explicit cstyle_string(std_string const *)
	{}
	explicit cstyle_string(simple_string const *)
	{}
};

class std_string
{
public:
	operator cstyle_string() const
	{
		return cstyle_string(this);
	}
};

class simple_string
{
public:
	operator cstyle_string() const
	{
		return cstyle_string(this);
	}
};

class glob_sequence
{
public:
#if 0
	enum 
#else /* ? 0 */
# define NAMED_FLAGS
	enum search_flags
#endif /* 0 */
	{
			noSort		=	1
		,	matchBrace	=	2
	};
public:

#define USE_ALT_FORM

#ifdef USE_ALT_FORM

    template<class S>
    explicit glob_sequence(S const &pattern)
	{
		do_stuff_(std_string(), pattern, 0);
	}

    template<class S>
    glob_sequence(S const &pattern, int flags)
	{
		do_stuff_(std_string(), pattern, flags);
	}

    glob_sequence(char const *directory, char const *pattern, int flags = noSort)
	{
		do_stuff_(directory, pattern, flags);
	}

    template<class S>
    glob_sequence(S const &directory, char const *pattern, int flags = noSort)
	{
		do_stuff_(directory, pattern, flags);
	}

    template<class S>
    glob_sequence(S const &directory, S const &pattern, int flags = noSort)
	{
		do_stuff_(directory, pattern, flags);
	}

#else /* ? USE_ALT_FORM */

    template<class S>
    explicit glob_sequence(S const &pattern, int flags = noSort)
	{
		do_stuff_(std_string(), pattern, flags);
	}
#ifdef NAMED_FLAGS
    template<class S>
    explicit glob_sequence(S const &pattern, search_flags flag)
	{
		do_stuff_(std_string(), pattern, flag);
	}
#endif /* NAMED_FLAGS */

    template<	class S1
			,	class S2
			>
    glob_sequence(S1 const &directory, S2 const &pattern, int flags = noSort)
	{
		do_stuff_(directory, pattern, flags);
	}
#ifdef NAMED_FLAGS
    template<	class S1
			,	class S2
			>
    glob_sequence(S1 const &directory, S2 const &pattern, search_flags flag)
	{
		do_stuff_(directory, pattern, flag);
	}
#endif /* NAMED_FLAGS */

#endif /* USE_ALT_FORM */

private:
	void do_stuff_(cstyle_string, cstyle_string, int)
	{}
};

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
	/* . */
	{
		std_string		stds	=	std_string();
		simple_string	sims	=	simple_string();
		char const		*css	=	0;

		glob_sequence	gls1("*");
#ifdef NAMED_FLAGS
		glob_sequence	gls2("*", glob_sequence::noSort/*  | 0 */);
#endif /* NAMED_FLAGS */
		glob_sequence	gls3("*", glob_sequence::noSort | glob_sequence::matchBrace);

		glob_sequence	gls4(stds);
		glob_sequence	gls5(stds, glob_sequence::noSort);
		glob_sequence	gls6(stds, glob_sequence::noSort | 1);

		glob_sequence	gls7(stds, "*");
		glob_sequence	gls8(stds, "*", glob_sequence::noSort);
		glob_sequence	gls9(stds, "*", glob_sequence::noSort | 1);

		glob_sequence	gls10(stds, stds);
		glob_sequence	gls11(stds, stds, glob_sequence::noSort);
		glob_sequence	gls12(stds, stds, glob_sequence::noSort | 1);

#ifdef GLOB_SEQUENCE_CTOR_PRIMARY_FORM
		glob_sequence	gls13(stds, sims);
		glob_sequence	gls14(stds, sims, glob_sequence::noSort);
		glob_sequence	gls15(stds, sims, glob_sequence::noSort | 1);
#endif /* GLOB_SEQUENCE_CTOR_PRIMARY_FORM */

#if 0
		((void)gls12);
		((void)gls11);
		((void)gls10);
		((void)gls9);
		((void)gls8);
		((void)gls7);
		((void)gls6);
		((void)gls5);
		((void)gls4);
#endif /* 0 */
		((void)gls3);
#ifdef NAMED_FLAGS
		((void)gls2);
#endif /* NAMED_FLAGS */
		((void)gls1);

		((void)stds);
		((void)sims);
		((void)css);
	}

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
