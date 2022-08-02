/* /////////////////////////////////////////////////////////////////////////////
 * File:        poab_test.cpp
 *
 * Purpose:     Implementation file for the poab_test project.
 *
 * Created:     3rd December 2003
 * Updated:     5th December 2003
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

#ifndef COMP_NAME
# error You must define COMP_NAME, e.g. "CodeWarrior 8"
#endif /* COMP_NAME */

#define stringize_(x)   #x
#define stringize(x)    stringize_(x)

#define COMPILER    stringize(COMP_NAME)

#include "object.h"

/* ////////////////////////////////////////////////////////////////////////// */

extern "C" IObject *make_Object(int i, char const *s);

////////////////////////////////////////////////////////////////////////////////

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("");
#ifdef SHARED_CLIENT
    puts("poab_test (dynamically linked)");
#else /* ? SHARED_CLIENT */
    puts("poab_test (statically linked)");
#endif /* SHARED_CLIENT */

    /* . */
    char const *strings[] = 
    {
            "Reginald Perrin"
        ,   "Archie Goodwin"
        ,   "Scott Tracy"
    };

    for(int i = 0; i < 3; ++i)
    {
        printf("Calling make_Object()\n");
        IObject *obj = make_Object(i, strings[i]);

        printf("Calling from C++ (%u, %s): ", sizeof(IObject), COMPILER);
        printf("%s\n", obj->GetName());
    }

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
