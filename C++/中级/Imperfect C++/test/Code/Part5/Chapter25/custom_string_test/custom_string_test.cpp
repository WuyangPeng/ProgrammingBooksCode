/* /////////////////////////////////////////////////////////////////////////////
 * File:        custom_string_test.cpp
 *
 * Purpose:     Implementation file for the custom_string_test project.
 *
 * Created:     29th December 2003
 * Updated:     30th December 2003
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
#include <stlsoft_fast_string_concatenator.h>

/* ////////////////////////////////////////////////////////////////////////// */

#define USE_FAST_CONCAT

/* ////////////////////////////////////////////////////////////////////////// */

#ifdef USE_WCHAR
# include <wchar.h>
typedef wchar_t         char_t;
# define CHAR_TYPE      "wchar_t"
# define C_T(x)         L ## x
# define string_len     wcslen
# define string_ncpy    wcsncpy
# define string_cpy     wcscpy
# define string_cat     wcscat
#else
# include <string.h>
typedef char            char_t;
# define CHAR_TYPE      "char"
# define C_T(x)         x
# define string_len     strlen
# define string_ncpy    strncpy
# define string_cpy     strcpy
# define string_cat     strcat
#endif /* USE_WCHAR */

/* ////////////////////////////////////////////////////////////////////////// */

namespace fc_test
{
    class trivial_string
    {
    public:
        typedef char_t          char_type;
        typedef char_type       value_type;
        typedef trivial_string  class_type;

    public:
        /* explicit */ trivial_string(char_type const *s);
                 trivial_string(char_type const *s, size_t cch);
                 trivial_string(size_t cch, char_type ch);
                 trivial_string(class_type const &s);
                ~trivial_string();

    public:
        class_type &operator +=(class_type const &s);
        class_type &operator +=(char_type const *s);
        class_type &operator +=(char_type const ch);

    public:
        char_type *begin();
        char_type *end();
        char_type const *begin() const;
        char_type const *end() const;

    public:
        char_type const *c_str() const;
        char_type const *data() const;
        char_type &operator [](size_t );
        char_type const &operator [](size_t ) const;
        size_t length() const;

    private:
        static char_type *_make_string(char_type const *s, size_t &len);
        static char_type *_make_string(char_type const *s, size_t cch, size_t &len);

    private:
        char_type   *m_s;
        size_t      m_len;
    };

# ifndef USE_FAST_CONCAT
    trivial_string operator +(trivial_string const &lhs, trivial_string const &rhs)
    {
        trivial_string  res(lhs);

        res += rhs;

        return res;
    }

    trivial_string operator +(trivial_string const &lhs, trivial_string::char_type const *rhs)
    {
        trivial_string  res(lhs);

        res += rhs;

        return res;
    }

    trivial_string operator +(trivial_string const &lhs, trivial_string::char_type const rhs)
    {
        trivial_string  res(lhs);

        res += rhs;

        return res;
    }

    trivial_string operator +(trivial_string::char_type const *lhs, trivial_string const &rhs)
    {
        trivial_string  res(lhs);

        res += rhs;

        return res;
    }

    trivial_string operator +(trivial_string::char_type const lhs, trivial_string const &rhs)
    {
        trivial_string  res(1, lhs);

        res += rhs;

        return res;
    }
# endif /* !USE_FAST_CONCAT */

} // namespace fc_test

/* ////////////////////////////////////////////////////////////////////////// */

namespace fc_test
{
    /* static */ trivial_string::char_type *trivial_string::_make_string(trivial_string::char_type const *s, size_t &len)
    {
        len = string_len(s);

        char_type   *news = string_ncpy(new char_type[1 + len], s, len);

        news[len] = '\0';

        return news;
    }

    /* static */ trivial_string::char_type *trivial_string::_make_string(trivial_string::char_type const *s, size_t cch, size_t &len)
    {
        len = string_len(s);

        if(cch < len)
        {
            len = cch;
        }

        char_type   *news = string_ncpy(new char_type[1 + cch], s, len);

        news[len] = '\0';

        return news;
    }

    /* explicit */ trivial_string::trivial_string(trivial_string::char_type const *s)
        : m_s(_make_string(s, m_len))
    {}

    trivial_string::trivial_string(trivial_string::char_type const *s, size_t cch)
        : m_s(_make_string(s, cch, m_len))
    {}

    trivial_string::trivial_string(size_t cch, trivial_string::char_type ch)
        : m_s(_make_string(C_T(""), cch, m_len))
    {
        m_len = cch;
        memset(m_s, ch, m_len); // This is wrong! It needs to be 
        m_s[m_len] = '\0';
    }

    trivial_string::trivial_string(trivial_string const &s)
        : m_s(_make_string(s.m_s, s.m_len, m_len))
    {}

    trivial_string::~trivial_string()
    {
        delete [] m_s;
    }

    trivial_string::char_type *trivial_string::begin()
    {
        return m_s;
    }

    trivial_string &trivial_string::operator +=(trivial_string::char_type const *s)
    {
        size_t      len     =   string_len(s);
        size_t      new_len =   len + m_len;
        char_type   *new_s  =   new char_type[1 + new_len];

        string_cpy(new_s, m_s);
        string_cat(new_s, s);
        delete [] m_s;

        m_s = new_s;
        m_len = new_len;

        return *this;
    }

    trivial_string &trivial_string::operator +=(trivial_string::char_type const ch)
    {
        char_type   sz[2];

        sz[0] = ch;
        sz[1] = 0;

        return operator +=(sz);
    }

    trivial_string &trivial_string::operator +=(trivial_string const &s)
    {
        return operator +=(s.c_str());
    }

    trivial_string::char_type *trivial_string::end()
    {
        return m_s + m_len;
    }

    trivial_string::char_type const *trivial_string::begin() const
    {
        return m_s;
    }

    trivial_string::char_type const *trivial_string::end() const
    {
        return m_s + m_len;
    }

    trivial_string::char_type const *trivial_string::c_str() const
    {
        return m_s;
    }

    trivial_string::char_type const *trivial_string::data() const
    {
        return m_s;
    }

    trivial_string::char_type &trivial_string::operator [](size_t index)
    {
        return m_s[index];
    }

    trivial_string::char_type const &trivial_string::operator [](size_t index) const
    {
        return m_s[index];
    }

    size_t trivial_string::length() const
    {
        return m_len;
    }

} // namespace fc_test

/* ////////////////////////////////////////////////////////////////////////// */

#ifdef USE_FAST_CONCAT

namespace fc_test
{
    typedef stlsoft::fast_string_concatenator<::fc_test::trivial_string>        fast_concat_t;

    inline fast_concat_t operator +(stlsoft::fsc_seed const &lhs, ::fc_test::trivial_string const &rhs)
    {
        return fast_concat_t(lhs, rhs);
    }

    inline fast_concat_t operator +(::fc_test::trivial_string const &lhs, ::fc_test::trivial_string const &rhs)
    {
        return fast_concat_t(lhs, rhs);
    }

    inline fast_concat_t operator +(::fc_test::trivial_string const &lhs, ::fc_test::trivial_string::value_type const *rhs)
    {
        return fast_concat_t(lhs, rhs);
    }

    inline fast_concat_t operator +(::fc_test::trivial_string const &lhs, ::fc_test::trivial_string::value_type const rhs)
    {
        return fast_concat_t(lhs, rhs);
    }

    inline fast_concat_t operator +(::fc_test::trivial_string::value_type const *lhs, ::fc_test::trivial_string const &rhs)
    {
        return fast_concat_t(lhs, rhs);
    }

    inline fast_concat_t operator +(::fc_test::trivial_string::value_type const lhs, ::fc_test::trivial_string const &rhs)
    {
        return fast_concat_t(lhs, rhs);
    }

} // namespace fc_test

#endif /* USE_FAST_CONCAT */

/* ////////////////////////////////////////////////////////////////////////// */

/* ////////////////////////////////////////////////////////////////////////// */

extern "C" void __stdcall Sleep(unsigned long);

namespace fc_client
{
    int main(int /* argc */, char ** /*argv*/)
    {
        typedef fc_test::trivial_string String;

    #if 0
        ::Sleep(100000);
    #endif /* 0 */

        puts("custom_string_test: " __STLSOFT_COMPILER_LABEL_STRING);

        /* . */
        String      s1  = "Goodbye";
        char const  *s2 = "cruel";
        String      s3  = "world!";
        String      s   = s1 + ' ' + s2 + (' ' + s3);

        String      r1  =   stlsoft::fsc_seed() + s1 + ' ' + "cruel" + ' ' + "world!";

    #if 0
        String      r2  =   stlsoft::fsc_seed2<String> + s1 + ' ' + "cruel" + ' ' + "world!";
    #endif /* 0 */

        return 0;
    }
}

int main()
{
    return fc_client::main(0, NULL);
}

/* ////////////////////////////////////////////////////////////////////////// */
