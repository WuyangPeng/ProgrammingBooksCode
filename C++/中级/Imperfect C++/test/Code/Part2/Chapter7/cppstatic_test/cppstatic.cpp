
#include "cppstatic.h"

#include <stlsoft.h>

/* ////////////////////////////////////////////////////////////////////////// */

char const * const CSTATIC_CALLCONV cfunc(double **)
{
    return __STLSOFT_COMPILER_VERSION_STRING;
}

char const * const CSTATIC_CALLCONV cfunc(int *)
{
    return __STLSOFT_COMPILER_VERSION_STRING;
}

/* ////////////////////////////////////////////////////////////////////////// */
