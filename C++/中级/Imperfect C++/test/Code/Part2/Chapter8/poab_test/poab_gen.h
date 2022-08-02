
// Updated: 4th March 2004

#include "poab/poab.h"

#undef STRUCT_BEGIN
#undef STRUCT_END
#undef STRUCT_METHOD_1
#undef STRUCT_METHOD_1_VOID
#undef STRUCT_METHOD_0_CONST

#ifdef POAB_COMPILER_HAS_COMPATIBLE_VTABLES

# ifdef POAB_FIRST_PASS

#  define STRUCT_BEGIN(S)                   \
                                            \
    struct S                                \
    {

#  define STRUCT_METHOD_1(S, M, R, A1)      \
                                            \
    virtual R M(A1 a1) = 0;

#  define STRUCT_METHOD_1_VOID(S, M, A1)    \
                                            \
    virtual void M(A1 a1) = 0;

#  define STRUCT_METHOD_0_CONST(S, M, R)    \
                                            \
    virtual R M() const = 0;

#  define STRUCT_END(S)                     \
                                            \
    };

# else /* ? POAB_FIRST_PASS */

#  define STRUCT_BEGIN(S)

#  define STRUCT_METHOD_1(S, M, R, A1)

#  define STRUCT_METHOD_1_VOID(S, M, A1)

#  define STRUCT_METHOD_0_CONST(S, M, R)

#  define STRUCT_END(S)

# endif /* POAB_FIRST_PASS */


#else /* POAB_COMPILER_HAS_COMPATIBLE_VTABLES */

# ifdef POAB_FIRST_PASS

#  define STRUCT_BEGIN(S)                   \
                                            \
    struct S;                               \
    struct S##VTable                        \
    {

#  define STRUCT_METHOD_1(S, M, R, A1)      \
                                            \
    R (*M)(struct S *obj, A1 a1);

#  define STRUCT_METHOD_1_VOID(S, M, A1)    \
                                            \
    void (*M)(struct S *obj, A1 a1);

#  define STRUCT_METHOD_0_CONST(S, M, R)    \
                                            \
    R (*M)(struct S const *obj);


# else /* ? POAB_FIRST_PASS */

#  ifdef __cplusplus 

#   define   STRUCT_BEGIN(S)                \
                                            \
    struct S                                \
    {                                       \
    protected:                              \
        struct S##VTable * const vtable;    \
    protected:                              \
        typedef struct S##VTable  vtable_t; \
    protected:                              \
        S(vtable_t *vt)                     \
            : vtable(vt)                    \
        {}                                  \
    public:


#  define    STRUCT_METHOD_1(S, M, R, A1)   \
                                            \
    inline R M(A1 a1)                       \
    {                                       \
        return vtable->M(this, a1);         \
    }

#  define STRUCT_METHOD_1_VOID(S, M, A1)    \
                                            \
    inline void M(A1 a1)                    \
    {                                       \
        vtable->M(this, a1);                \
    }

#  define STRUCT_METHOD_0_CONST(S, M, R)    \
                                            \
    inline R M() const                      \
    {                                       \
        return vtable->M(this);             \
    }

#   define STRUCT_END(S)                    \
                                            \
    private:                                \
        S(S const &rhs);                    \
        S &operator =(S const &rhs);        \
    protected:                              \
        ~S()                                \
        {}                                  \
                                            \
    };

#  else /* ? __cplusplus */

#   define STRUCT_BEGIN(S)                  \
                                            \
    struct S                                \
    {                                       \
        struct S##VTable * const vtable;

#   define STRUCT_METHOD_1(S, M, R, A1)

#   define STRUCT_METHOD_1_VOID(S, M, A1)

#   define STRUCT_METHOD_0_CONST(S, M, R)

#   define STRUCT_END(S)                    \
                                            \
    };

#  endif /* __cplusplus */

# endif /* POAB_FIRST_PASS */

#endif /* POAB_COMPILER_HAS_COMPATIBLE_VTABLES */



