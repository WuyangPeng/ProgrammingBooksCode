/* /////////////////////////////////////////////////////////////////////////////
 * File:        templ_ctors_test.cpp
 *
 * Purpose:     Implementation file for the templ_ctors_test project.
 *
 * Created:     26th December 2003
 * Updated:     15th March 2004
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

#define _STLSOFT_NO_NAMESPACE

#include <stlsoft.h>
#include <stlsoft_argument_proxies.h>

#if !defined(__WATCOMC__) && \
    !defined(__COMO__)
# include <stlsoft_simple_string.h>

typedef stlsoft_ns_qual(basic_simple_string)<char>  string_t;
#else

class string_t
{
public:
    string_t(const char *)
    {}
};

#endif /* */

//#define STEP_ONE      /* By value */
//#define STEP_TWO      /* By const ref */
#define STEP_THREE  /* By ref + const ref */

#define USE_PROXIES

/* ////////////////////////////////////////////////////////////////////////// */

class Double
{
public:
    typedef double  value_type;
public:
    Double()
        : m_value(0.0)
    {}
    explicit Double(double value)
        : m_value(value)
    {}
public:
    double GetValue() const
    {
        return m_value;
    }
private:
    double  m_value;
};

class String
{
public:
    typedef string_t const  &value_type;
public:
    explicit String(string_t const &value)
        : m_value(value)
    {}
    explicit String(char const *value)
        : m_value(value)
    {}
public:
    string_t const &GetValue() const
    {
        return m_value;
    }
    void GetValue(string_t const &value)
    {
        m_value = value;
    }
private:
    string_t    m_value;
};

class StringUser
{
public:
    typedef string_t const  &value_type;
public:
    explicit StringUser(string_t &value)
        : m_value(value)
    {}
public:
    string_t const &GetValue() const
    {
        return m_value;
    }
    void SetValue(string_t const &value)
    {
        m_value = value;
    }
private:
    string_t    &m_value;
};

template <typename T>
class Wrapper
  : public T
{
public:
  typedef T   base_class_type;
public:
  typedef typename base_class_type::value_type  operator_type;
  operator operator_type() const
  {
    return base_class_type::GetValue();
  }

  Wrapper()
  {}
#ifdef STEP_ONE
  template <typename T1>
  explicit Wrapper(T1 t1)
    :  base_class_type(t1)
  {}
#elif defined(STEP_TWO)
  template <typename T1>
  explicit Wrapper(T1 const &t1)
    :  base_class_type(t1)
  {}
#elif defined(STEP_THREE)
  template <typename T1>
  explicit Wrapper(T1 &t1)
    :  base_class_type(t1)
  {}
  template <typename T1>
  explicit Wrapper(T1 const &t1)
    :  base_class_type(t1)
  {}
#endif /* STEP_??? */

};

/* ////////////////////////////////////////////////////////////////////////// */

static double d_func()
{
    return 123.456;
}

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    ::Sleep(100000);
#endif /* 0 */

    puts("templ_ctors_test: " __STLSOFT_COMPILER_LABEL_STRING);

    {
        typedef Wrapper<Double> Double_t;

        Double_t    d1;
//      Double_t    d2(12.34); // Error!
        double      v1 = d1;

        STLSOFT_SUPPRESS_UNUSED(v1);

//      Double_t    d3(d_func());
    }

    {
        typedef Wrapper<String> String_t;

        string_t const  sc("A string instance");

        String_t        s1("c-string");
#ifdef USE_PROXIES
        String_t        s2 = stlsoft_ns_qual(const_ref_proxy)(sc);
#else /* ? USE_PROXIES */
        String_t        s2(sc);
#endif /* USE_PROXIES */
        string_t const  &v1 = s1;

        STLSOFT_SUPPRESS_UNUSED(v1);
    }

#ifndef STEP_TWO
    {
        typedef Wrapper<StringUser> StringUser_t;

        string_t        ms("A mutable string");

#ifdef USE_PROXIES
        StringUser_t    s1 = stlsoft_ns_qual(ref_proxy)(ms);
#else /* ? USE_PROXIES */
        StringUser_t    s1(ms);
#endif /* USE_PROXIES */

        string_t const  &v1 =   s1.GetValue();

        STLSOFT_SUPPRESS_UNUSED(v1);
    }
#endif /* !STEP_TWO */

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
