/* /////////////////////////////////////////////////////////////////////////////
 * File:        atomic_read_test.cpp
 *
 * Purpose:     Implementation file for the atomic_read_test project.
 *
 * Created:     11th December 2003
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
#include <MLBase.h>
#include <windows.h>

/* ////////////////////////////////////////////////////////////////////////// */

#ifdef _DEBUG
const int   ITERATIONS  =   100000;
const int   NUM_THREADS =   2;
#else /* ? _DEBUG */
const int   ITERATIONS  =   1000000000;
const int   NUM_THREADS =   31;
#endif /* _DEBUG */

const int   VAL1    =   0x10101010;
const int   VAL2    =   0x07070707;


int x;

DWORD WINAPI ThreadProc(LPVOID /* pv */)
{
    for(int i = 0; i < ITERATIONS; ++i)
    {
        int y   =   x;

        switch(y)
        {
            case    VAL1:
                x = VAL2;
                break;
            case    VAL2:
                x = VAL1;
                break;
            default:
                printf("x is invalid: 0x%08x\n", y);
                break;
        }
    }

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    /* . */
    int     i;
    HANDLE  threads[NUM_THREADS];

    for(i = 0; i < NUM_ELEMENTS(threads); ++i)
    {
        DWORD   id;

        threads[i]  = ::CreateThread(NULL, 0, ThreadProc, NULL, CREATE_SUSPENDED, &id);
    }

    x   =   VAL1;

    ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
    for(i = 0; i < NUM_ELEMENTS(threads); ++i)
    {
        ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
        ::ResumeThread(threads[i]);
    }

    ::SetThreadPriority(::GetCurrentThread(), THREAD_PRIORITY_NORMAL);
    ::WaitForMultipleObjects(NUM_ELEMENTS(threads), threads, true, INFINITE);
    for(i = 0; i < NUM_ELEMENTS(threads); ++i)
    {
        ::CloseHandle(threads[i]);
    }

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
