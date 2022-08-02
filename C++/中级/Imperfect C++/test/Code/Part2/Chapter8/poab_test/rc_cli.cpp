
#define STRICT

#include "rc_svr.h"

#include <winstl_findfile_sequence.h>

#include <stdio.h>

int (*make_Thing)(char const *compiler, IThing **ppThing);


int main()
{
    typedef winstl_ns_qual(findfile_sequence)    srch_t;

    srch_t                              libraries(".", "*.dll", srch_t::files);
    srch_t::const_iterator              b = libraries.begin();
    srch_t::const_iterator              e = libraries.end();

    for(; b != e; ++b)
    {
        printf("\n--------------------------------\n%s:", (*b).get_filename());

        HINSTANCE   hLib = ::LoadLibrary((*b).get_path());

        if(NULL == hLib)
        {
            printf(" - load failed");
        }
        else
        {
            (void*&)(make_Thing) = (void*)::GetProcAddress(hLib, "make_Thing");

            if(NULL == make_Thing)
            {
                (void*&)(make_Thing) = (void*)::GetProcAddress(hLib, "_make_Thing");
            }

            if(NULL == make_Thing)
            {
                printf(" - could not locate \"make_Thing\"");
            }
            else
            {
                IThing  *pThing;
                int     i = make_Thing(__STLSOFT_COMPILER_VERSION_STRING, &pThing);

                if(0 == i)
                {
                    printf(" - make_Thing() failed");
                }
                else
                {
                    printf(" - \"%s\" calling \"%s\"", pThing->GetClientCompiler(), pThing->GetBuildCompiler());

                    puts("");
                    pThing->Release();
                }
            }
        }
    }

    return 0;
}
