/* /////////////////////////////////////////////////////////////////////////////
 * File:        for_all_test.cpp
 *
 * Purpose:     Implementation file for the for_all_test project.
 *
 * Created:     11th November 2003
 * Updated:     11th November 2003
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

#include <stlsoft.h>
#include <stlsoft_simple_algorithms.h>

using stlsoft::copy_all;
using stlsoft::fill_all;
using stlsoft::for_all;

extern "C" void __stdcall Sleep(unsigned long);

/* ////////////////////////////////////////////////////////////////////////// */

void print_int(int const &i)
{
    printf("%d\n", i);
}

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
//  ::Sleep(100000);

    puts("for_all_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    int         ari[10];
    int const   ari2[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    fill_all(ari, 10);

    puts("ari");
    for_all(ari, print_int);
    puts("ari2");
    for_all(ari2, print_int);

    copy_all(ari2, ari);

    puts("ari (after copy)");
    for_all(ari, print_int);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
