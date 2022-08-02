
//#include <SLBase.h>

class X
{
    int i;
};

class Y
{
    int X::*p;
};

#ifdef MAKING_CDYNAMIC
# define CDYNAMIC_IMPEXP    __declspec(dllexport)
#else /* ?MAKING_CDYNAMIC */
# define CDYNAMIC_IMPEXP    __declspec(dllimport)
#endif /* MAKING_CDYNAMIC */

#define CDYNAMIC_EXTERN     extern "C++"


#if 0
# define CDYNAMIC_DECL(t)       CDYNAMIC_EXTERN CDYNAMIC_IMPEXP t __cdecl
#else /* ? 0 */
# define CDYNAMIC_DECL(t)       CDYNAMIC_EXTERN CDYNAMIC_IMPEXP t __stdcall
#endif /* 0 */


CDYNAMIC_DECL(char const *) cfunc(X arg0, Y arg1);


