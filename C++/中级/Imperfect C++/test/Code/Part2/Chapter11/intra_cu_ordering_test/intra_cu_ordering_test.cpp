/* /////////////////////////////////////////////////////////////////////////////
 * File:        intra_cu_ordering_test.cpp
 *
 * Purpose:     Implementation file for the intra_cu_ordering_test project.
 *
 * Created:     11th November 2003
 * Updated:     1st December 2003
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
#include <stlsoft_simple_string.h>

/* ////////////////////////////////////////////////////////////////////////// */

class Object
{
public:
    Object(char const *s)
        : m_str(s)
    {
        printf("Object(%p, \"%s\")\n", this, c_str());
    }
    Object(Object const &rhs)
        : m_str(rhs.m_str)
    {
        printf("Object(%p, \"%s\")\n", this, c_str());
    }
    ~Object()
    {
        printf("~Object(%p, \"%s\")\n", this, c_str());
    }

    char const *c_str() const
    {
        return m_str.c_str();
    }

private:
    stlsoft::basic_simple_string<char>  m_str;
};

/* ////////////////////////////////////////////////////////////////////////// */

extern Object o2;

#if 0
// Independent
Object  o1("o1");
Object  o2("o2");
#elif 0
// Legally dependent
Object  o1("o1");
Object  o2(o1);
#else
// Illegally dependent
Object  o1(o2);
Object  o2("o2");
#endif

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
  /* . */
    Object  o3("o3");
    Object  o4("o4");

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
