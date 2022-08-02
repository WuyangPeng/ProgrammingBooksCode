/* /////////////////////////////////////////////////////////////////////////////
 * File:        short_circuit_test.cpp
 *
 * Purpose:     Implementation file for the short_circuit_test project.
 *
 * Created:     6th November 2003
 * Updated:     6th November 2003
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

class B
{
public:
    B(bool b)
        : m_b(b)
    {}

    operator bool() const
    {
        return m_b;
    }

private:
    bool    m_b;
};

class X
{
public:
    X(bool b)
        : m_b(b)
    {}

    operator B() const
    {
        printf("this (%p) => B()\n", this);

        return B(m_b);
    }

private:
    bool    m_b;
};


inline bool operator &&(B b1, B b2)
{
    bool    b1_ =   b1;
    bool    b2_ =   b2;

    return b1_ && b2_;
}

inline bool operator &&(bool b1, B b2)
{
    bool    b1_ =   b1;
    bool    b2_ =   b2;

    return b1_ && b2_;
}

namespace Z
{
    class X
    {
    public:
        operator bool() const
        {
            return true;
        }
    };

    class Y
    {
    public:
      operator X() const
      {
        printf("Why am I called?\n");

        return X();
      }
    };

    bool operator &&(bool lhs, X const &rhs)
    {
        return lhs && (bool)rhs;
    }

    bool operator &&(bool lhs, Y const &rhs)
    {
        return lhs && (X)rhs;
    }
}

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    /* . */
    X   x1(true);
    X   x2(true);

    if(x1 && x2)
    {
        printf("Both evaluated true\n");
    }

    if(false && x2)
    {
        printf("Both evaluated true\n");
    }

    Z::Y y;

    if(false && y) {}

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
