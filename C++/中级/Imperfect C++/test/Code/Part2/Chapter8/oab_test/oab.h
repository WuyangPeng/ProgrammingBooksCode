
#define OBJECT_CALLCONV     __cdecl

struct IObject
{
    virtual char const  *OBJECT_CALLCONV GetHost() = 0;

    virtual void        OBJECT_CALLCONV SetHost(char const *s) = 0;

    virtual char const  *OBJECT_CALLCONV GetCompiler() = 0;
};


#ifdef _DEBUG
extern "C"
#else /* ? _DEBUG */
extern
#endif /* _DEBUG */
int 
#ifndef MAKING_OAB
__declspec(dllimport)
#else
__declspec(dllexport)
#endif /* !MAKING_OAB */
make_Object(IObject **pp);
