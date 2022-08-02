
//#include <SLBase.h>

#ifdef MAKING_CDYNAMIC
# define CDYNAMIC_IMPEXP    __declspec(dllexport)
#else /* ?MAKING_CDYNAMIC */
# define CDYNAMIC_IMPEXP    __declspec(dllimport)
#endif /* MAKING_CDYNAMIC */

#if 1
# define CDYNAMIC_EXTERN        extern "C"
#else /* ? 1 */
# define CDYNAMIC_EXTERN        extern "C++"
#endif /* 1 */


#if 0
# define CDYNAMIC_DECL(t)       CDYNAMIC_EXTERN CDYNAMIC_IMPEXP t __cdecl
#else /* ? 0 */
# define CDYNAMIC_DECL(t)       CDYNAMIC_EXTERN CDYNAMIC_IMPEXP t __stdcall
#endif /* 0 */


CDYNAMIC_DECL(char const *) cfunc(int arg0, int arg1);


