/* /////////////////////////////////////////////////////////////////////////////
 * File:        pid_sequence_test.cpp
 *
 * Purpose:     Implementation file for the pid_sequence_test project.
 *
 * Created:     23rd August 2005
 * Updated:     13th December 2005
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

#if defined(unix) || \
    defined(__unix__)

# include <unixstl.h>

#elif defined(WIN32) || \
      defined(_WIN32)

# include <winstl.h>
# include <winstl/pid_sequence.hpp>

#else /* ? operating system */

# error Operating system not discriminated

#endif /* operating system */


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


/* Standard C Header Files */
#include <stdlib.h>

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	/* . */
	{
		STARTUPINFO			si;
		PROCESS_INFORMATION	pi;

		memset(&si, 0, sizeof(si));
		si.cb = sizeof(si);

		BOOL	b	=	CreateProcess(	NULL//"whereis"
									,	"c:\\bin\\whereis.exe H:\\dev *.dll"
									,	NULL
									,	NULL
									,	false
									,	CREATE_SUSPENDED | CREATE_NEW_CONSOLE
									,	NULL
									,	NULL
									,	&si
									,	&pi);

		if(!b)
		{
			cerr << "Could not create: " << ::GetLastError() << endl;

			return EXIT_FAILURE;
		}
		else
		{
			cout << "Started: " << pi.dwProcessId << endl;
		}

		{
			winstl::pid_sequence	pids(winstl::pid_sequence::sort);

			cout << "Enumerating:" << endl;
			std::copy(pids.begin(), pids.end(), std::ostream_iterator<DWORD>(std::cout, " "));
			cout << endl << endl;
		}

		ResumeThread(pi.hThread);
		::WaitForSingleObject(pi.hProcess, INFINITE);

		{
			winstl::pid_sequence	pids(winstl::pid_sequence::sort);

			cout << "Enumerating:" << endl;
			std::copy(pids.begin(), pids.end(), std::ostream_iterator<DWORD>(std::cout, " "));
			cout << endl << endl;
		}

		::CloseHandle(pi.hThread);
		::CloseHandle(pi.hProcess);

		::Sleep(2000);

		{
			winstl::pid_sequence	pids(winstl::pid_sequence::sort);

			cout << "Enumerating:" << endl;
			std::copy(pids.begin(), pids.end(), std::ostream_iterator<DWORD>(std::cout, " "));
			cout << endl << endl;
		}
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
		cout << "pid_sequence_test: " << __STLSOFT_COMPILER_LABEL_STRING << endl;
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
