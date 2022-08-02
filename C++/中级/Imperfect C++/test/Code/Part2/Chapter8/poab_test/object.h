
// Updated: 4th March 2004

#include "poab/poab.h"

#ifndef stlsoft_assert
# define stlsoft_assert(x)      ((void)0)
#endif /* !stlsoft_assert */


#if defined(__cplusplus) && \
    defined(POAB_COMPILER_HAS_COMPATIBLE_VTABLES)

struct IObject
{
    virtual void SetName(char const *s) = 0;
    virtual char const *GetName() const = 0;
};

#else /* ? __cplusplus */

struct IObject;

# include "poab/pack_warning_push.h"
# include "poab/pack_push_4.h"

struct IObjectVTable
{
    void (*SetName)(struct IObject *obj, char const *s);
    char const *(*GetName)(struct IObject const *obj);
};

struct IObject
{
    struct IObjectVTable *const vtable;

# ifdef __cplusplus
protected:
    typedef struct IObjectVTable    vtable_t;

protected:
    IObject(vtable_t *vt)
        : vtable(vt)
    {}
    IObject(IObject const &, vtable_t *vt)
        : vtable(vt)
    {}

public:
    inline void SetName(char const *s)
    {
        stlsoft_assert(NULL != vtable);

        vtable->SetName(this, s);
    }
    inline char const *GetName() const
    {
        stlsoft_assert(NULL != vtable);

        return vtable->GetName(this);
    }
private:
    IObject(IObject const &rhs);
    IObject &operator =(IObject const &rhs);
protected:
    ~IObject()
    {}
# endif /* __cplusplus */
};

# include "poab/pack_pop_4.h"
# include "poab/pack_warning_pop.h"

#endif /* __cplusplus && POAB_COMPILER_HAS_COMPATIBLE_VTABLES */
