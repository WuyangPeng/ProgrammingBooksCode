
#ifdef __cplusplus
# include <stlsoft.h>

# ifndef _STLSOFT_NO_NAMESPACE
using stlsoft::uint32_t;
# endif /* _STLSOFT_NO_NAMESPACE */
#else /* ? __cplusplus */
/* Just have to assume we're on a 32-bit platform. Sorry. */
typedef unsigned long   uint32_t;
#endif /* __cplusplus */

/* ////////////////////////////////////////////////////////////////////////// */

struct uinteger64
{
  uint32_t  lowerVal;
  uint32_t  upperVal;
};

/* ////////////////////////////////////////////////////////////////////////// */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */
    void    UI64_Assign(uinteger64 *lhs, uint32_t higher, uint32_t lower);

    void    UI64_Add(uinteger64 *result, uinteger64 const *lhs, uinteger64 const *rhs);

    int     UI64_Compare(uinteger64 const *lhs, uinteger64 const *rhs);
#define     UI64_IsLessThan(pi1, pi2)       (UI64_Compare(pi1, pi2) < 0)
#define     UI64_IsEqual(pi1, pi2)          (0 == UI64_Compare(pi1, pi2))
#define     UI64_IsGreaterThan(pi1, pi2)    (0 < UI64_Compare(pi1, pi2))

#ifdef __cplusplus
} // extern "C"
#endif /* __cplusplus */

/* ////////////////////////////////////////////////////////////////////////// */

