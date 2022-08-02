/* /////////////////////////////////////////////////////////////////////////////
 * File:        process_module_sequence_test.cpp
 *
 * Purpose:     Implementation file for the process_module_sequence_test project.
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
#include <stlsoft/static_string.hpp>

#if defined(unix) || \
    defined(__unix__)

# include <unixstl.h>

#elif defined(WIN32) || \
      defined(_WIN32)

# include <winstl.h>
# include <winstl/dl_call.hpp>
# include <winstl/pid_sequence.hpp>
# include <winstl/process_module_sequence.hpp>

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
#include <stdio.h>

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

extern "C" 
HRESULT WINAPI Sec_EnablePrivilegeByNameA(	HANDLE      hToken
										,	LPCSTR		name
										,	BOOL        bEnable);

/* ////////////////////////////////////////////////////////////////////////// */

inline stlsoft::basic_static_string<char, _MAX_PATH> get_module_path(	HANDLE	hProcess
																	,	HMODULE	hModule)
{
	stlsoft::basic_static_string<char, _MAX_PATH>	s("", _MAX_PATH); // Construct 'full'

#if 0
	DWORD	cch	=	::GetModuleFileNameEx(hProcess, hModule, &s[0], _MAX_PATH);
#else /* ? 0 */
	DWORD	cch	=	winstl::dl_call<DWORD>("PSAPI", "stdcall:GetModuleFileNameExA", hProcess, hModule, &s[0], _MAX_PATH);
#endif /* 0 */

	if(0 == cch)
	{
		throw winstl::windows_exception("Could not elicit module path", ::GetLastError());
	}
	else
	{
		s.resize(cch);
	}

	return s;
}

static int main_(int /* argc */, char ** /*argv*/)
{
	using winstl::pid_sequence;
	using winstl::process_module_sequence;

//	using stlsoft::operator <<;


	{
		HANDLE	hToken;

		if(::OpenProcessToken(	::GetCurrentProcess()
							,	TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY
							,	&hToken))
		{
			Sec_EnablePrivilegeByNameA(hToken, SE_DEBUG_NAME, true);
		}
	}

	/* . */
	pid_sequence					pids;
	pid_sequence::const_iterator	b	=	pids.begin();

	for(; b != pids.end(); ++b)
	{
		HANDLE									hProcess	=	::OpenProcess(/* PROCESS_ALL_ACCESS |  */PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, *b);

		::GetLastError();

		cout << get_module_path(hProcess, NULL).c_str() << ": " << endl;

		process_module_sequence					modules(hProcess);
		process_module_sequence::const_iterator	b2			=	modules.begin();

		for(; b2 != modules.end(); ++b2)
		{
			cout << "  " << get_module_path(hProcess, *b2).c_str() << endl;
		}

	    ::CloseHandle(hProcess);
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
		puts("process_module_sequence_test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */


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
