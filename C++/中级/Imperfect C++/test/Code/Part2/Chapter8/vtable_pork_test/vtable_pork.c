/* /////////////////////////////////////////////////////////////////////////////
 * File:        vtable_pork.c
 *
 * Purpose:     Implementation file for the vtable_pork_test project.
 *
 * Created:     29th November 2003
 * Updated:     29th November 2003
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
#include <stdlib.h>

#include "vtable_pork.h"

/* ////////////////////////////////////////////////////////////////////////// */


char const *LOCKABLE_CALLCONV Pork(IThing *thing)
{
    return "Porked!!";
}


void PorkThing(IThing *thing)
{
    typedef struct IThingVTable  vtable_t;
    vtable_t *vt    =   (vtable_t*)malloc(sizeof(vtable_t));
    *vt             =   *thing->vtable;
    vt->Get         =   Pork;
    thing->vtable   =   vt;
}



/* ////////////////////////////////////////////////////////////////////////// */
