/* /////////////////////////////////////////////////////////////////////////////
 * File:        fast_concatenator_test.cpp
 *
 * Purpose:     Implementation file for the fast_concatenator_test project.
 *
 * Created:     7th November 2003
 * Updated:     7th November 2003
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
#include <stlsoft_simple_string.h>
#include <stlsoft_fast_string_concatenator.h>


typedef stlsoft::basic_simple_string<char>          String;
typedef stlsoft::fast_string_concatenator<String>   fast_concat_t;

/* ////////////////////////////////////////////////////////////////////////// */

inline fast_concat_t operator +(String const &lhs, String const &rhs)
{
    return fast_concat_t(lhs, rhs);
}

inline fast_concat_t operator +(String const &lhs, String::value_type const *rhs)
{
    return fast_concat_t(lhs, rhs);
}

inline fast_concat_t operator +(String::value_type const *lhs, String const &rhs)
{
    return fast_concat_t(lhs, rhs);
}


/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    puts("fast_concatenator_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    String  s1  =   "Goodbye";
    String  s2  =   "cruel";
    String  s3  =   "world!";
    String  s   =   s1 + " " + s2 + " " + s3;

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
