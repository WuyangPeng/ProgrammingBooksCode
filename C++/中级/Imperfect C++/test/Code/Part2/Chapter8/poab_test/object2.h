
// Updated: 5th December 2003

#if !defined(OBJECT2_FIRST_PASS) && \
    !defined(OBJECT2_SECOND_PASS)

# define OBJECT2_FIRST_PASS
# define POAB_FIRST_PASS
# include "object2.h"
# undef POAB_FIRST_PASS

# define OBJECT2_SECOND_PASS
# include "object2.h"

#else /* ? !OBJECT2_FIRST_PASS && !OBJECT2_SECOND_PASS */

# include "poab_gen.h"

STRUCT_BEGIN(IObject)
    STRUCT_METHOD_1_VOID(IObject, SetName, char const *)
    STRUCT_METHOD_0_CONST(IObject, GetName, char const *)
STRUCT_END(IObject)

#endif /* !OBJECT2_FIRST_PASS && !OBJECT2_SECOND_PASS */
