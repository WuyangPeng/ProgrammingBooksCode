/* /////////////////////////////////////////////////////////////////////////////
 * File:        glob_errfunc_test.c
 *
 * Purpose:     Implementation file for the glob_errfunc_test project.
 *
 * Created:     29th August 2005
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

#ifdef _WIN32
# define _STLSOFT_FORCE_ANY_COMPILER
#endif /* _WIN32 */

#include <unixstl.h>

#include <unixem/implicit_link.h>
#include <glob.h>

/* Standard C Header Files */
#include <errno.h>
#include <stdio.h>
#include <string.h>

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

int on_glob_error(char const *errPath, int erno)
{
    fprintf(stderr, "Error searching: \"%s\"; error: %d (%s)\n", errPath, erno, strerror(erno));

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */

int main(int argc, char *argv[])
{
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
    puts("glob_errfunc_test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

#if 0
    { size_t i; for(i = 0; i < 0xffffffff; ++i){} }
#endif /* 0 */

    ((void)argc);
    ((void)argv);
    /* . */

    {
        const   OFFS    =   200;
        glob_t  gl      =   { 0, 10, OFFS, 0, NULL };
#if 0
        int     flags   =   0;
        int     r       =   glob(   "H:\\System Volume Information\\*.*"
#else /* ? 0 */
        int     flags   =   0
						|	GLOB_TILDE
#if 0
						|	GLOB_DOOFFS
						|	GLOB_NOSORT
						|	GLOB_NOCHECK
						|	GLOB_TILDE_CHECK
						|	GLOB_NOMAGIC
#endif /* 0 */
#if 1
						|	GLOB_PERIOD
						|	GLOB_NODOTSDIRS
#endif /* 0 */
						|	GLOB_ONLYDIR
						|	GLOB_LIMIT
						|	0;
#if 0
        int     r       =   glob(   "H:\\dev\\bin\\*.dll"
#else /* ? 0 */
#if 0
#if 0
        int     r       =   glob(   "~\\*.*"
#else /* ? 0 */
        int     r       =   glob(   "?"
#endif /* 0 */
#else /* ? 0 */
        int     r       =   glob(   "H:\\*.*"
#endif /* 0 */
#endif /* 0 */
#endif /* 0 */
                                ,   flags
                                ,   on_glob_error
                                ,   &gl);

        if( 0 != r &&
			(	GLOB_NOSPACE != r ||
				GLOB_LIMIT != (flags & GLOB_LIMIT)))
        {
            fprintf(stderr, "glob() failed: %d\n", r);
        }
        else
        {
            int i;

            for(i = 0; i < gl.gl_pathc; ++i)
            {
                puts(gl.gl_pathv[i + ((flags & GLOB_DOOFFS) ? OFFS : 0)]);
            }

            globfree(&gl);
        }
    }

    return 0;
}


/* ////////////////////////////////////////////////////////////////////////// */
