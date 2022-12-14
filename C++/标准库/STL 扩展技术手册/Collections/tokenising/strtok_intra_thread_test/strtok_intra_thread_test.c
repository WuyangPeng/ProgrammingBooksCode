/* /////////////////////////////////////////////////////////////////////////////
 * File:        strtok_intra_thread_test.c
 *
 * Purpose:     Implementation file for the strtok_intra_thread_test project.
 *
 * Created:     22nd February 2006
 * Updated:     22nd February 2006
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2006, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              This source code is placed into the public domain 2006
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


/* Standard C Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_MSC_VER) && \
    defined(_DEBUG)
# include <crtdbg.h>
#endif /* _MSC_VER) && _DEBUG */

/* /////////////////////////////////////////////////////////////////////////////
 * Typedefs
 */

#if 0
typedef std::string     string_t;
#endif /* 0 */

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

/* ////////////////////////////////////////////////////////////////////////// */

int main(int argc, char *argv[])
{
#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
    puts("strtok_intra_thread_test: " __STLSOFT_COMPILER_LABEL_STRING);
#endif /* debug */

#if 0
    { for(size_t i = 0; i < 0xffffffff; ++i){} }
#endif /* 0 */

    ((void)argc);
    ((void)argv);
    /* . */

	{
        char    str[]       =   "abc,def;ghi,hjk;;";
        char    *tokenOuter;
        char    *tokenInner;

//      printf(
        for(tokenOuter = strtok(str, ";"); NULL != tokenOuter; tokenOuter = strtok(NULL, ";"))
        {
            printf("Outer token:   %s\n", tokenOuter);

            for(tokenInner = strtok(tokenOuter, ","); NULL != tokenInner; tokenInner = strtok(NULL, ","))
            {
                printf("  Inner token: %s\n", tokenOuter);
            }
        }
	}

    return EXIT_SUCCESS;
}


/* ////////////////////////////////////////////////////////////////////////// */
