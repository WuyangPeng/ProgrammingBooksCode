/* /////////////////////////////////////////////////////////////////////////////
 * File:        explicit_cast_test.cpp
 *
 * Purpose:     Implementation file for the explicit_cast_test project.
 *
 * Created:     22nd December 2003
 * Updated:     22nd December 2003
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

#define _STLSOFT_NO_NAMESPACE

#include <stlsoft.h>
#include <stlsoft_explicit_cast.h>

/* ////////////////////////////////////////////////////////////////////////// */

struct POD
{
    char    v1[1000];
    long    l1;
};

class X
{
public:
    X()
    {
        memset(m_pod.v1, 10, sizeof(m_pod.v1));
        m_pod.l1 = 20;
    }

public:
    operator explicit_cast<int> () const
    {
        return 10;
    }
    operator explicit_cast<POD> () const
    {
        return m_pod;
    }

private:
    POD m_pod;
};

class Y
{
public:
    Y()
    {
        memset(m_pod.v1, 30, sizeof(m_pod.v1));
        m_pod.l1 = 40;
    }

public:
    operator int () const
    {
        return 30;
    }
    operator POD () const
    {
        return m_pod;
    }

private:
    POD m_pod;
};

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("explicit_cast_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    X   x;
    Y   y;

    int i1  =   explicit_cast<int>(x);
    int i2  =   explicit_cast<int>(y);
    POD p1  =   explicit_cast<POD>(x);
    POD p2  =   explicit_cast<POD>(y);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
