
#include <stdio.h>

#ifdef __cplusplus
namespace {
#else
static 
#endif /* __cplusplus */

/* static */ void the_func()
{
    printf("the_func(%p), %s\n", the_func, __THE_FILE__);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
