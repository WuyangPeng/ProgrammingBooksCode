/* /////////////////////////////////////////////////////////////////////////////
 * File:        double_checked_lock_test.cpp
 *
 * Purpose:     Implementation file for the double_checked_lock_test project.
 *
 * Created:     1st December 2003
 * Updated:     1st December 2003
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (C) 1999-2003, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              email:      software@synesis.com.au
 *
 *              This source code is placed into the public domain 2003
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

#include <windows.h>
#include <stdio.h>

#include <stlsoft.h>

#if !defined(WIN32) && \
    !defined(_WIN32)

# include <unixstl.h>

#else /* ? operating system */

# include <winstl.h>

#endif /* operating system */



#define USE_PTHREAD

#ifdef USE_PTHREAD
# include <pthread.h>
#endif /* USE_PTHREAD */


/* ////////////////////////////////////////////////////////////////////////// */

void *thread_proc(void *arg)
{
    return (void*)1;
}

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("double_checked_lock_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    pthread_t       tid;
//  pthread_attr_t  attr;
    void            *result;
    int             status  =   pthread_create (&tid, /* &attr */ NULL, thread_proc, NULL);

    pthread_join(tid, &result);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
