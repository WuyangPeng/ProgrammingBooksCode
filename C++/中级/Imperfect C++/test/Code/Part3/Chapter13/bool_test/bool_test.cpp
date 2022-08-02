/* /////////////////////////////////////////////////////////////////////////////
 * File:        bool_test.cpp
 *
 * Purpose:     Implementation file for the bool_test project.
 *
 * Created:     26th July 2003
 * Updated:     3rd August 2003
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

/* ////////////////////////////////////////////////////////////////////////// */

int int_func(int i);

unsigned char unigned_char_func()
{
    return 3;
}

int main(int /* argc */, char ** /*argv*/)
{
    /* sizeof(bool) */
    (void)printf("sizeof(bool): %u\n", sizeof(bool));

    /* conversion to bool */
    bool    b   =   int_func(555);

    (void)printf("b = %d\n", b);

    b   =   unigned_char_func();

    (void)printf("b = %d\n", b);

    /* notionally boolean pointer evaluation */
    void    *p  =   &b;

    if(p)
    {
        p = NULL;
    }

    /* !false !true */
    reinterpret_cast<char&>(b) = char(128);

    if(b != false)
    {
        printf("b != false\n");
    }
    if(b != true)
    {
        printf("b != true\n");
    }
    if(b)
    {
        printf("b is implicitly true\n");
    }

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */

int int_func(int i)
{
    return i;
}

/* ////////////////////////////////////////////////////////////////////////// */
