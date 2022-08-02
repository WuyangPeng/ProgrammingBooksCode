/* /////////////////////////////////////////////////////////////////////////////
 * File:        string_switch_test.cpp
 *
 * Purpose:     Implementation file for the string_switch_test project.
 *
 * Created:     4th August 2003
 * Updated:     4th August 2003
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
#include <string.h>

/* ////////////////////////////////////////////////////////////////////////// */

enum Type
{
        abc
    ,   def
    ,   unknown
};

Type g(char const *s)
{
    if( s == "abc" ||
        s == "ABC")
    {
        return abc;
    }
    else if(s == "def" ||
            s == "DEF")
    {
        return def;
    }
    else
    {
        if( 0 == strcmp(s, "abc") ||
            0 == strcmp(s, "ABC"))
        {
            return abc;
        }
        else if(0 == strcmp(s, "def") ||
                0 == strcmp(s, "DEF"))
        {
            return abc;
        }
    }
    
    return unknown;
}

int main(int /* argc */, char ** /*argv*/)
{
    /* . */

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
