/* /////////////////////////////////////////////////////////////////////////////
 * File:        impl_array_test.cpp
 *
 * Purpose:     Implementation file for the impl_array_test project.
 *
 * Created:     17th January 2004
 * Updated:     18th January 2004
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
#include <string.h>

#include <stlsoft.h>

/* ////////////////////////////////////////////////////////////////////////// */

struct IntArray1D
{
    operator int *()
    {
        return m_elements;
    }

    int m_elements[10];
};

#if 0
struct IntArray2D
{
    operator int **()
    {
        return m_elements;
    }

    int m_elements[3][3];
};
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */



struct Ar1D
{
    operator int *()
    {
        return m_elements;
    }

    Ar1D()
    {
        memset(&m_elements[0], 0, sizeof(m_elements));
    }

    int m_elements[3];
};

struct Ar2D
{
    operator Ar1D *()
    {
        return m_elements;
    }

    Ar1D    m_elements[3];
};

struct Ar3D
{
    operator Ar2D *()
    {
        return m_elements;
    }

    Ar2D    m_elements[3];
};


/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("impl_array_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    IntArray1D  ia1;

    ia1[2] = ia1[1] + 1;

#if 0
    IntArray2D  ia2;

    ia2[2][2] = ia2[2][1] + 1;
#endif /* 0 */

    Ar3D        ar3d;

    ar3d[2][2][2] = ar3d[2][2][1] + 1;

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
