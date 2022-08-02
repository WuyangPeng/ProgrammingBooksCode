/* /////////////////////////////////////////////////////////////////////////////
 * File:        explicit_conversion.cpp
 *
 * Purpose:     Implementation file for the explicit_conversion project.
 *
 * Created:     29th July 2003
 * Updated:     29th July 2003
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


/* ////////////////////////////////////////////////////////////////////////// */

template <typename T>
class xop
{
public:
    xop(T t)
        : m_t(t)
    {}

#if 0
    template <typename U>
    xop(U &u)
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

struct S
{
    int i;
};

union Thing
{
public:
    Thing()
    {
        s.i = (int)this;
    }

public:
    operator xop<int> () const
    {
        return xop<int>(i);
    }

    operator xop<double> () const
    {
        return xop<double>(d);
    }

    operator xop<S> () const
    {
        return xop<S>(s);
    }

    operator xop<S*> () const
    {
        return xop<S*>(ps);
    }

#if 0
    operator xop<S const&> () const
    {
        return xop<S const&>(s);
    }

    operator xop<S&> ()
    {
        return xop<S&>(s);
    }
#endif /* 0 */

protected:
    int     i;
    double  d;
    S       s;
    S       *ps;
};

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    /* . */

    Thing   t1;
    Thing   t2;

    double  d1      =   (xop<double>)t1;
    S       s1      =   (xop<S>)t1;
    S       *ps1    =   (xop<S*>)t1;
//  S const &s2     =   (xop<S const &>)t1;
//  S const &s3     =   (xop<S &>)t1;

    ((void)s1);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
