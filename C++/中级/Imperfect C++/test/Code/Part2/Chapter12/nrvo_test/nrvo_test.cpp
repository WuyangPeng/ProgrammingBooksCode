/* /////////////////////////////////////////////////////////////////////////////
 * File:        nrvo_test.cpp
 *
 * Purpose:     Implementation file for the nrvo_test project.
 *
 * Created:     20th November 2003
 * Updated:     20th November 2003
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

    String &operator +=(char const *rhs)
    {
        // Don't do anything

        return *this;
    }

protected:
    char const  *m_s;
};

#if 0
String MakeString(char const *s1, char const *s2)
{
    String  result(s1);

    if(NULL != s2)
    {
        result += "";
    }
    else
    {
        if(*s2 < '9')
        {
            result += s2;
        }
        else
        {
            String  result2(s2);

            result2 += s1;

            result = result2;
        }
    }

    return result;
}

#else /* ? 0 */

String MakeString(char const *s1, char const *s2)
{
    String  result(s1);

    result += s2;

    return result;
}
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("nrvo_test: " __STLSOFT_COMPILER_LABEL_STRING);

    printf("1:\n");
    MakeString("1", "2");

    printf("2:\n");
    String  s2 = MakeString("2", "3");

    printf("3:\n");
    String  s3(MakeString("3", "4"));

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
