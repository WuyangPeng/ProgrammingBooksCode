/* /////////////////////////////////////////////////////////////////////////////
 * File:        properties_ext_test.cpp
 *
 * Purpose:     Implementation file for the properties_ext_test project.
 *
 * Created:     1st October 2003
 * Updated:     1st October 2003
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

class Thingy
{
public:
    Thingy(int i)
        : m_value(i)
    {}

public:
    int get_Value()
    {
        return m_value;
    }

#ifdef __BORLANDC__
      __property int Value = {read=get_Value};
#elif defined(_MSC_VER)
    __declspec(property(get=get_Value)) int Value;
#endif // compiler

private:
    int m_value;
};


/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    /* . */
    Thingy  t(7);
    int     i = t.Value;

    i = i;
    ((void)i);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
