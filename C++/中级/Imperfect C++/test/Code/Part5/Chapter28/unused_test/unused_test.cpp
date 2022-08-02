/* /////////////////////////////////////////////////////////////////////////////
 * File:        unused_test.cpp
 *
 * Purpose:     Implementation file for the unused_test project.
 *
 * Created:     28th December 2003
 * Updated:     29th December 2003
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

//#define _STLSOFT_NO_NAMESPACE

#include <stlsoft.h>
#include <stlsoft_simple_string.h>
#include <stlsoft_unused_return_value_monitor.h>

typedef stlsoft_ns_qual(basic_simple_string)<char>  string_t;

/* ////////////////////////////////////////////////////////////////////////// */

class X
{
    struct unused_monitor
    {
        void operator ()(void const volatile *instance, X const &value) const
        {
            printf("Unused return value %s from object instance %p\n", value.get_value().c_str(), instance);
        }
    };

public:
    X &operator ++()
    {
        printf("X::operator ++()\n");

        m_value.push_back((char)']');

        return *this;
    }

#ifdef _DEBUG
    stlsoft_ns_qual(unused_return_value_monitor)<X, unused_monitor> operator ++(int)
#else /* ? _DEBUG */
    X operator ++(int)
#endif /* _DEBUG */
    {
        printf("X::operator ++(int)\n");

        X ret(*this);
        operator ++();
        return ret;
    }

    void print() const
    {
        printf("X value: %s\n", m_value.c_str());
    }

    string_t const &get_value() const
    {
        return m_value;
    }

private:
    string_t    m_value;
};


/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("unused_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    X   x;

    X   r1  =   ++x;
    X   r2  =   x++;
                x++;    // Unused!

    r1.print();
    r2.print();

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
