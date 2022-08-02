
#include <stdio.h>

#include "vt.h"

int main()
{
    IObject *object;

    printf("\nvt client (C)\n");
    printf("sizeof(IObject): %u\n", sizeof(IObject));
    printf("sizeof(IObjectVTable): %u\n", sizeof(struct IObjectVTable));

    if(!make_Object(&object))
    {
        fprintf(stderr, "Failed to make Object!\n");
    }
    else
    {
        printf("object: 0x%p\n", object);
        printf("object->vtable: 0x%p\n", object->vtable);

        {
            long    *pl =   object->vtable;
            int     i;

            for(i = 0; i < 10; ++i, ++pl)
            {
                printf("object->vtable[%d]: 0x%p\n", i, *pl);
                if(0 != *pl)
                {
                    char const *(*pfn)(IObject *, char const *) =   *pl;

                    if( i != 0
                        )
                    {
                        char const  *s  =   (*pfn)(object, "Test");

                        printf("  [%p, ", s);
                        printf("  %s]", (s > 0x00200000) ? s : "<unknown>");
                    }
                }
                printf("\n");
            }
        }

//      printf("object->vtable->v1: 0x%p\n", object->vtable->v1);
//      printf("object->vtable->v2: 0x%p\n", object->vtable->v2);
        printf("object->vtable->SetName: 0x%p\n", object->vtable->SetName);
        printf("object->vtable->GetName: 0x%p\n", object->vtable->GetName);
//      printf("object->vtable->v3: 0x%p\n", object->vtable->v3);
//      printf("object->vtable->v4: 0x%p\n", object->vtable->v4);

        printf("Calling GetName()\n");
        {
            char const  *s  =   object->vtable->GetName(object);

            printf("Return from GetName(): 0x%p\n", s);
            printf("Return from GetName(): %s\n", s);
        }

        printf("Calling SetName()\n");
        object->vtable->SetName(object, "Reginald Perrin");

        printf("Calling GetName()\n");
        printf("Object name (from C): %s\n", object->vtable->GetName(object));      
    }

    return 0;
}
