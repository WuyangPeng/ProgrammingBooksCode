/* /////////////////////////////////////////////////////////////////////////////
 * File:        independent_threads_test.cpp
 *
 * Purpose:     Implementation file for the independent_threads_test project.
 *
 * Created:     10th December 2003
 * Updated:     11th December 2003
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

#include <stdio.h>
#include <pthread.h>


/* ////////////////////////////////////////////////////////////////////////// */

int calc_factorial(int );
int calc_fibonacci_sum(int );

/* ////////////////////////////////////////////////////////////////////////// */

int s_i1;
int s_i2;

void *thread_proc1(void *p)
{
    s_i1 = calc_factorial((int)p);

    return 0;
}

void *thread_proc2(void *p)
{
    s_i2 = calc_fibonacci_sum((int)p);

    return 0;
}


/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    /* . */
    pthread_t       tid1;
    void            *result1;
    int             status1 =   pthread_create (&tid1, /* &attr */ NULL, thread_proc1, NULL);
    pthread_join(tid1, NULL);

    pthread_t       tid2;
    void            *result2;
    int             status2 =   pthread_create (&tid2, /* &attr */ NULL, thread_proc2, NULL);
    pthread_join(tid2, NULL);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */

int calc_factorial(int /* i */)
{
    return 0;
}
int calc_fibonacci_sum(int /* i */)
{
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
