
#define MAKING_CDYNAMIC

//#include <SLBase.h>

#include <stlsoft.h>

#include "cdynamic.h"

/* ////////////////////////////////////////////////////////////////////////// */

CDYNAMIC_DECL(char const *) cfunc(int arg0, int arg1)
{
    STLSOFT_SUPPRESS_UNUSED(arg0);
    STLSOFT_SUPPRESS_UNUSED(arg1);

    return __STLSOFT_COMPILER_VERSION_STRING;
}

/* ////////////////////////////////////////////////////////////////////////// */
