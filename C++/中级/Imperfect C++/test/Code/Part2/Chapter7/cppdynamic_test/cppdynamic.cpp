
#define MAKING_CDYNAMIC

//#include <SLBase.h>

#include <stlsoft.h>

#include "cppdynamic.h"

/* ////////////////////////////////////////////////////////////////////////// */

CDYNAMIC_DECL(char const *) cfunc(X arg0, Y arg1)
{
    STLSOFT_SUPPRESS_UNUSED(arg0);
    STLSOFT_SUPPRESS_UNUSED(arg1);

    return __STLSOFT_COMPILER_VERSION_STRING;
}

/* ////////////////////////////////////////////////////////////////////////// */
