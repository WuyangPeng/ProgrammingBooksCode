
#include <stdio.h>

#include "vt.h"

int main()
{
    IObject *object;

    printf("\nvt client (C++)\n");
    printf("sizeof(IObject): %u\n", sizeof(IObject));

    if(!make_Object(&object))
    {
        fprintf(stderr, "Failed to make Object!\n");
    }
    else
    {
        object->SetName("Reginald Perrin");

        printf("Object name (in C++): %s\n", object->GetName());        
    }

    return 0;
}
