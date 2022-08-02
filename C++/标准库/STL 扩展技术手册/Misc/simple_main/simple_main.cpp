/* /////////////////////////////////////////////////////////////////////////////
 * File:        simple_main.cpp
 *
 * Purpose:     Implementation file for the simple_main project.
 *
 * Created:     1st May 2005
 * Updated:     30th December 2005
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
#include <stlsoft_integer_to_string.h>

/* Standard C Header Files */
#include <windows.h>

/* Standard C++ Header Files */

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    DWORD       pid =   ::GetCurrentProcessId();
    char        sz[21];
    size_t      n;
    char const  *s  =   ::stlsoft::integer_to_string(sz, 21, (__int32)pid, n);
    DWORD       dummy;

    ::WriteFile(::GetStdHandle(STD_OUTPUT_HANDLE)
            ,   s
            ,   n
            ,   &dummy
            ,   NULL);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
