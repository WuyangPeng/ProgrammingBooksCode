/* /////////////////////////////////////////////////////////////////////////////
 * File:        rvo_test.cpp
 *
 * Purpose:     Implementation file for the rvo_test project.
 *
 * Created:     20th November 2003
 * Updated:     2nd December 2003
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

/* ////////////////////////////////////////////////////////////////////////// */

class String
{
public:
    explicit String(char const *s)
        : m_s(s)
    {
        printf("String(char const* = %s): %p\n", s, this);
    }
//private:
//  explicit
    String(String const &rhs)
        : m_s(rhs.m_s)
    {
        printf("String(String const& = %s): %p\n", rhs.m_s, this);
    }

public:
    String &operator =(String const &rhs)
    {
        m_s = rhs.m_s;

        printf("operator = &(String const& = %s): %p\n", rhs.m_s, this);

        return *this;
    }

    String &operator +=(String const &rhs)
    {
        // Don't do anything

        return *this;
    }

protected:
    char const  *m_s;
};

#if 0
String MakeString(char const *s)
{
    if(NULL == s)
    {
        return String("");
    }
    else
    {
        if(*s < '9')
        {
            return String("small");
        }
        else
        {
            return String(s);
        }
    }

//  return r_val;
}
#endif /* 0 */

String CreateString(char const *s)
{
  return String((NULL == s) ? "" : s);
}

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    puts("rvo_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
#define MakeString  CreateString

    printf("1:\n");
    MakeString("1");

    printf("2:\n");
    String  s2 = MakeString("2");

    printf("3:\n");
    String  s3(MakeString("3"));

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
