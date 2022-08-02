
#include <stlsoft.h>

#include <new>

#define MAKING_OAB

struct IObject;

#include "oab.h"

class CompilerObject
    : public IObject
{
private:
    virtual char const  *OBJECT_CALLCONV GetHost()
    {
        return m_host;
    }

    virtual void        OBJECT_CALLCONV SetHost(char const *s)
    {
        m_host = s;
    }

    virtual char const  *OBJECT_CALLCONV GetCompiler()
    {
        return __STLSOFT_COMPILER_VERSION_STRING;
    }

private:
    char const  *m_host;
};

extern "C" int __declspec(dllexport) make_Object(IObject **pp)
{
    struct X
    {
        char    x[sizeof(CompilerObject)];
    };

    static X    s;

    *pp = new(&s) CompilerObject();

    return 1;
}
