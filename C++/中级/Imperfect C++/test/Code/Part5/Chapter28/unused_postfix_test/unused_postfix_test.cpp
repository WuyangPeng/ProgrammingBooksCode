/* /////////////////////////////////////////////////////////////////////////////
 * File:        unused_postfix_test.cpp
 *
 * Purpose:     Implementation file for the unused_postfix_test project.
 *
 * Created:     9th November 2003
 * Updated:     9th November 2003
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
#include <stlsoft_unused_return_value_monitor.h>

stlsoft_ns_using(unused_return_value_monitor)

#include <string>

stlsoft_ns_using_std(string)

/* ////////////////////////////////////////////////////////////////////////// */


struct int_monitor
{
public:
    void operator ()(void const *instance, int value) const
    {
        printf("Unused return value %d from object instance %p\n", value, instance);
    }
};

struct string_monitor
{
public:
    void operator ()(void const *instance, string const &value) const
    {
        printf("Unused return value %s from object instance %p\n", value.c_str(), instance);
    }
};

class X
{
public:
    X()
        : m_str("Hello Natty!")
    {}

    unused_return_value_monitor<int, int_monitor>   fn1()
    {
        return 10;
    }

    unused_return_value_monitor<string, string_monitor> fn2()
    {
        return "Hello Natty!";
    }

    unused_return_value_monitor<string, string_monitor, string const &> fn3()
    {
        return m_str;
    }

private:
    string const    m_str;
};

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    puts("unused_postfix_test: " __STLSOFT_COMPILER_LABEL_STRING);

    X       x;
    int     i;
    string  s;

    i = x.fn1(); // Used
        x.fn1(); // Unused

    s = x.fn2(); // Used
        x.fn2(); // Unused

    s = x.fn3(); // Used
        x.fn3(); // Unused

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
