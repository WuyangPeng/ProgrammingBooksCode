
#include "rc_svr.h"

#include <MIRefCnt.h>
#include <MLRefCnt.h>

__SYNSOFT_GEN_USING(::SynesisStd::RefCounter)

#include <stlsoft_simple_string.h>

#include <new>
#include <stdio.h>

class Thing
  : public IThing_
{
public:
    Thing(char const *compiler)
        : m_compiler(compiler)
    {
//      printf("Thing::Thing(0x%p)\n", this);
    }
    Thing()
    {
//      printf("Thing::Thing(0x%p)\n", this);
    }
    ~Thing()
    {
//      printf("Thing::~Thing(0x%p)\n", this);
    }

public:
    virtual char const *__SYNSOFT_MOD_CALLCONV_VDECL GetBuildCompiler() const
    {
        return __STLSOFT_COMPILER_VERSION_STRING;
    }
    virtual char const *__SYNSOFT_MOD_CALLCONV_VDECL GetClientCompiler() const
    {
        return m_compiler.c_str();
    }

public:
    stlsoft_ns_qual(basic_simple_string)<char>  m_compiler;
};

extern "C"
__declspec(dllexport)
int make_Thing(char const *compiler, IThing **ppThing)
{
#if defined(__DMC__)
    Thing   *pThing = new RefCounter<Thing>;

    if(NULL != pThing)
    {
        pThing->m_compiler = compiler;
    }

    *ppThing = pThing;
#else
    *ppThing = new (std::nothrow) RefCounter<Thing>(compiler);
#endif /* __DMC__ */

    return NULL != *ppThing;
}

#ifdef __DMC__
int __stdcall DllMain(void *, unsigned, void *)
{
    return 1;
}
#endif /* __DMC__ */
