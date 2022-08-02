
#include <stlsoft.h>

#include <stdio.h>

#include "oab.h"

int main()
{
    IObject *pObject;

    if(make_Object(&pObject))
    {
        pObject->SetHost(__STLSOFT_COMPILER_VERSION_STRING);

        printf("%32s\tcalling\t%32s\n", pObject->GetHost(), pObject->GetCompiler());
    }

    return 0;
}
