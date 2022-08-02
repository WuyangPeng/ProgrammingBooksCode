/* /////////////////////////////////////////////////////////////////////////////
 * File:        multi_dim_create_test.cpp
 *
 * Purpose:     Implementation file for the multi_dim_create_test project.
 *
 * Created:     17th January 2004
 * Updated:     17th January 2004
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (C) 1999-2004, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              email:      software@synesis.com.au
 *
 *              This source code is placed into the public domain 2004
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

typedef char    byte_t;

/* ////////////////////////////////////////////////////////////////////////// */

#if 0
void f(int x)
{
  new byte_t[x];
}

#else /* ? 0 */

#if 0
void f(int x, int y, int z)
{
  new byte_t[x][y][z]; // Error
}
#else /* ? 0 */

const size_t Y = 10;
const size_t Z = Y * 2;

void f(int x)
{
  new byte_t[x][Y][Z];
}
#endif /* 0 */

#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    /* . */

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
