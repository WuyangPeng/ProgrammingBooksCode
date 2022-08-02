/* /////////////////////////////////////////////////////////////////////////////
 * File:        expl_test.cpp
 *
 * Purpose:     Implementation file for the expl_test project.
 *
 * Created:     31st July 2003
 * Updated:     1st February 2004
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
#include <time.h>

typedef struct tm   tm;
typedef double      DATE;

/* ////////////////////////////////////////////////////////////////////////// */

template <typename T>
class explicit_cast
{
public:
    explicit_cast(T t)
        : m_t(t)
    {}

#if 0
    template <typename U>
    explicit_cast(U &u)
        : m_t(u)
    {}
#endif /* 0 */

public:
    operator T ()
    {
        return m_t;
    }

private:
    T   &m_t;
};

/* ////////////////////////////////////////////////////////////////////////// */

class Time
{
public:
#if 0
    operator tm () const
    {
        return tm();
    }
    operator DATE () const
    {
        return 0.0;
    }
#else
    operator explicit_cast<tm> () const
    {
        return tm();
    }
    operator explicit_cast<DATE> () const
    {
        return 0.0;
    }
#endif /* 0 */
};

void f1(tm t)
{
}

void f2(DATE t)
{
}


/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    /* . */
    Time    t;

#if 0
    f1(t);
    f2(t);
#else
    f1(explicit_cast<tm>(t));
    f2(explicit_cast<DATE>(t));
#endif /* 0 */

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
