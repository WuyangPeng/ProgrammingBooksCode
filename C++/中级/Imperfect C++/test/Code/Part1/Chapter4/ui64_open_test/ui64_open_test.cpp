/* /////////////////////////////////////////////////////////////////////////////
 * File:        ui64_open_test.cpp
 *
 * Purpose:     Implementation file for the ui64_open_test project.
 *
 * Created:     28th October 2003
 * Updated:     29th October 2003
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

#include "..\uinteger64\uinteger64.h"

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    puts("ui64_open_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    uinteger64  i1;
    uinteger64  i2;

    UI64_Assign(&i1, 0x11111111, 0x22222222);
    UI64_Assign(&i2, 0x10101010, 0x02020202);

//  bool        bLess       = i1 < i2;  // Error!
    bool        bLess       =   UI64_IsLessThan(&i1, &i2);
//  bool        bEqual      = i1 == i2; // Error!
    bool        bEqual      =   UI64_IsEqual(&i1, &i2);
    bool        bGreater    =   UI64_IsGreaterThan(&i1, &i2);

//  i1 + i2; // Error!
    uinteger64  i3;
    uinteger64  i4 = i3;
    uinteger64  i5;

    UI64_Add(&i3, &i1, &i2);

    i5 = i3;

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */

extern "C"
{
    void UI64_Assign(uinteger64 *lhs, uint32_t higher, uint32_t lower)
    {
        lhs->lowerVal   =   lower;
        lhs->upperVal   =   higher;
    }
    void UI64_Add(uinteger64 *result, uinteger64 const *lhs, uinteger64 const *rhs)
    {
        uint32_t    lowTotal = lhs->lowerVal + rhs->lowerVal;

        result->lowerVal = lowTotal;
        result->upperVal = lhs->upperVal + rhs->upperVal;

        assert((lowTotal < rhs->lowerVal && lowTotal < lhs->lowerVal) || (lowTotal >= rhs->lowerVal && lowTotal >= lhs->lowerVal));

        if(lowTotal < lhs->lowerVal)
        {
            assert(lowTotal < rhs->lowerVal);

            // It's overflowed, so add one.

            ++result->upperVal;
        }
    }

    int UI64_Compare(uinteger64 const *lhs, uinteger64 const *rhs)
    {
        int iRet;

        if(lhs->lowerVal < rhs->lowerVal)
        {
            iRet = -1;
        }
        else if(rhs->lowerVal < lhs->lowerVal)
        {
            iRet = +1;
        }
        else
        {
            if(lhs->lowerVal < rhs->lowerVal)
            {
                iRet = -1;
            }
            else if(rhs->lowerVal < lhs->lowerVal)
            {
                iRet = +1;
            }
            else
            {
                iRet = 0;
            }
        }

        return iRet;
    }

} // extern "C"

/* ////////////////////////////////////////////////////////////////////////// */
