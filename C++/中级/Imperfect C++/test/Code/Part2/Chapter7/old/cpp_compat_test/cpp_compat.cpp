
#include "cpp_compat.h"

#include <stlsoft.h>

/* ////////////////////////////////////////////////////////////////////////// */

#ifdef __cplusplus
extern "C++"
#endif /* __cplusplus */
char const * const C_COMPAT_CALLCONV cfunc()
{
    return __STLSOFT_COMPILER_VERSION_STRING;
}

/* ////////////////////////////////////////////////////////////////////////// */
