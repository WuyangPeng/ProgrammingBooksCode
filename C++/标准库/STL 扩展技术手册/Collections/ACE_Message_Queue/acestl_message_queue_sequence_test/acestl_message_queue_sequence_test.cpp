/* /////////////////////////////////////////////////////////////////////////////
 * File:        acestl_message_queue_sequence_test.cpp
 *
 * Purpose:     Implementation file for the acestl_message_queue_sequence_test project.
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

/* STLSoft Header Files */
#include <stlsoft.h>

#include <acestl/acestl.hpp>
#include <acestl/message_block_functions.hpp>
#include <acestl/message_queue_sequence.hpp>

#include <ace/Message_Queue.h>

/* Standard C++ Header Files */
#include <algorithm>
#include <exception>
#include <vector>

#ifdef __WATCOMC__
namespace std
{
	using ::exception;
}
#endif /* __WATCOMC__ */

/* Standard C Header Files */
#include <stdio.h>


#if 0
namespace stlsoft
{
	namespace acestl_project
	{

		template <ACE_SYNCH_DECL, typename O>
#if 0
		O std_copy_impl_(	message_queue_sequence<ACE_SYNCH_USE>::iterator const	&f
						,	message_queue_sequence<ACE_SYNCH_USE>::iterator const	&l
#else /* ? 0 */
		O std_copy_impl_(	message_queue_sequence<ACE_SYNCH_USE>::iterator			f
						,	message_queue_sequence<ACE_SYNCH_USE>::iterator			l
#endif /* 0 */
						,	O														o)
		{
			message_queue_sequence<ACE_SYNCH_USE>::iterator	i(f);

			fprintf(stderr, "Using acestl::copy()\n");

			for(; i != l; ++o, ++i)
			{
				*o = *i;
			}

			return o;
		}

	} // namespace acestl_project

} // namespace stlsoft


namespace std
{

#if 0
	template <ACE_SYNCH_DECL, typename O>
	O copy(	::acestl::message_queue_sequence<ACE_SYNCH_USE>::iterator const	&f
		,	::acestl::message_queue_sequence<ACE_SYNCH_USE>::iterator const	&l
		,	O																o)
	{
		return ::acestl::std_copy_impl_(f, l, o);
	}
#else /* ? 0 */
# if 0
	template <ACE_SYNCH_DECL, typename O>
	O copy(	::acestl::message_queue_sequence<ACE_SYNCH_USE>::iterator	f
		,	::acestl::message_queue_sequence<ACE_SYNCH_USE>::iterator	l
		,	O															o)
	{
		return ::acestl::std_copy_impl_(f, l, o);
	}
# else /* ? 0 */
#  if 0
	template <ACE_SYNCH_DECL, typename O>
	O copy(	::acestl::message_queue_sequence<ACE_SYNCH_USE>::iterator	f
		,	::acestl::message_queue_sequence<ACE_SYNCH_USE>::iterator	l
		,	O															*o)
	{
		return ::acestl::std_copy_impl_(f, l, o);
	}
#  else /* ? 0 */
#   if 0
	template <ACE_SYNCH_DECL>
	char *copy(	::acestl::message_queue_sequence<ACE_SYNCH_USE>::iterator	f
			,	::acestl::message_queue_sequence<ACE_SYNCH_USE>::iterator	l
			,	char														*o)
	{
		return ::acestl::std_copy_impl_(f, l, o);
	}
#   else /* ? 0 */
#    if 1
	char *copy(::acestl::message_queue_sequence<ACE_Null_Mutex, ACE_Null_Condition>::iterator	f
			,	::acestl::message_queue_sequence<ACE_Null_Mutex, ACE_Null_Condition>::iterator	l
#    else /* ? 0 */
	template <ACE_SYNCH_DECL>
	char *copy(::acestl::message_queue_sequence<ACE_SYNCH_USE>::iterator	f
			,	::acestl::message_queue_sequence<ACE_SYNCH_USE>::iterator	l
#    endif /* 0 */
			,	char																							*o)
	{
		return ::acestl::std_copy_impl_(f, l, o);
	}
#   endif /* 0 */
#  endif /* 0 */
# endif /* 0 */
#endif /* 0 */

} // namespace std
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

#if (   defined(WIN32) || \
        defined(_WIN32)) && \
    !defined(_INC_WINDOWS)
extern "C" void __stdcall Sleep(unsigned long);
#endif /* WIN32 */


/* /////////////////////////////////////////////////////////////////////////////
 * Functions
 */

inline ACE_Message_Block *new_ACE_Message_Block(char const *s, size_t n)
{
	ACE_Message_Block	*mb = new ACE_Message_Block(s, n);

	mb->wr_ptr(n);

	return mb;
}

inline ACE_Message_Block *new_ACE_Message_Block(char const *s, size_t n, size_t o)
{
	ACE_Message_Block	*mb = new ACE_Message_Block(s, n);

	mb->rd_ptr(n);
	mb->wr_ptr(n + o);

	return mb;
}

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
	puts("acestl_message_queue_sequence_test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

	/* . */
	{
		static const char					SRC[]	=	"Hello, Natty!";

		ACE_Message_Queue<ACE_NULL_SYNCH>	mq;
		ACE_Time_Value						nowait(ACE_OS::gettimeofday());

		mq.enqueue_tail(new_ACE_Message_Block(SRC + 0, 6), &nowait);
		mq.enqueue_tail(new_ACE_Message_Block(SRC + 6, 0), &nowait);
		mq.enqueue_tail(new_ACE_Message_Block(SRC + 6, 1), &nowait);
		mq.enqueue_tail(new_ACE_Message_Block(SRC + 7, 6), &nowait);

		acestl::message_queue_sequence<ACE_NULL_SYNCH>	mqs(mq);

		stlsoft_assert(mqs.size() == strlen(SRC));

		std::vector<char>	v(std::distance(mqs.begin(), mqs.end()));

		std::copy(mqs.begin(), mqs.end(), std::ostream_iterator<char>(std::cout));
		std::cout << std::endl;

		std::copy(mqs.begin(), mqs.end(), &v[0]);
		std::cout << std::endl;
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
		fprintf(stderr, "Unhandled error: %s\n", x.what());
	}
	catch(...)
	{
		fprintf(stderr, "Unhandled unknown error\n");
	}

	return EXIT_FAILURE;
}

/* ////////////////////////////////////////////////////////////////////////// */
