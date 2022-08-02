
#include <stdio.h>
#ifndef __WATCOMC__
# include <stlsoft_simple_string.h>
#endif /* __WATCOMC__ */

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
#ifndef __WATCOMC__
        return m_str.c_str();
#else
        return m_str;
#endif /* __WATCOMC__ */
    }

private:
#ifndef __WATCOMC__
    stlsoft::basic_simple_string<char>  m_str;
#else
    char const                          *m_str;
#endif /* __WATCOMC__ */
};

extern Object o1;
extern Object o2;
extern Object o3;
