/* /////////////////////////////////////////////////////////////////////////////
 * File:        delete_contents_C_test.c
 *
 * Purpose:     Implementation file for the delete_contents_C_test project.
 *
 * Created:     19th March 2005
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


/* Standard C Header Files */
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

#include <sys/stat.h>

/* /////////////////////////////////////////////////////////////////////////////
 * Forward declarations
 */

#if (   defined(WIN32) || \
        defined(_WIN32)) && \
    !defined(_INC_WINDOWS)
void __stdcall Sleep(unsigned long);
#endif /* WIN32 */

/* ////////////////////////////////////////////////////////////////////////// */

int main(int argc, char *argv[])
{
	char const	*dir	=	NULL;

#if 0
	Sleep(100000);
#endif /* 0 */

#if defined(_DEBUG) || \
    defined(__SYNSOFT_DBS_DEBUG)
	puts("delete_contents_C_test");
#endif /* debug */

	((void)argc);
	((void)argv);

	/* . */
#if 0
	if(argc < 2)
	{
		fprintf(stderr, "Must specify directory to clear\n");

		return EXIT_FAILURE;
	}
	else
#endif /* 0 */
	{
		DIR	*dir	=	opendir(".");

		if(NULL != dir)
		{
			struct dirent	*de;

			for(; NULL != (de = readdir(dir)); )
			{
				struct stat	st;

				if( 0 == stat(de->d_name, &st) &&
					S_IFREG == (st.st_mode & S_IFMT))
				{
#if 0
					remove(de->d_name);
#else /* ? 0 */
					puts(de->d_name);
#endif /* 0 */
				}
			}

			closedir(dir);
		}
	}

    return 0;
}


/* ////////////////////////////////////////////////////////////////////////// */
