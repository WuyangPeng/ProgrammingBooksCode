#line 1 "object2.cpp"
#line 1 "object2.h"
#line 1 "object2.h"
#line 16 "object2.h"
#line 1 "poab_gen.h"
#line 1 "poab/poab.h"
#line 1 "poab/compiler_intel.h"
#line 19 "poab/poab.h"
#line 5 "poab_gen.h"
#line 53 "poab_gen.h"
#line 147 "poab_gen.h"
#line 18 "object2.h"
struct IObject; struct IObjectVTable {
    void (*SetName)(struct IObject *obj, char const * a1);
    char const * (*GetName)(struct IObject const *obj);
STRUCT_END(IObject)
#line 10 "object2.h"
#line 1 "object2.h"
#line 16 "object2.h"
#line 1 "poab_gen.h"
#line 1 "poab/poab.h"
#line 1 "poab/compiler_intel.h"
#line 19 "poab/poab.h"
#line 5 "poab_gen.h"
#line 53 "poab_gen.h"
#line 76 "poab_gen.h"
#line 92 "poab_gen.h"
#line 100 "poab_gen.h"
#line 107 "poab_gen.h"
#line 114 "poab_gen.h"
#line 125 "poab_gen.h"
#line 145 "poab_gen.h"
#line 18 "object2.h"
struct IObject { protected: struct IObjectVTable * const vtable; protected: typedef struct IObjectVTable vtable_t; protected: IObject(vtable_t *vt) : vtable(vt) {} public:
    inline void SetName(char const * a1) { vtable->SetName(this, a1); }
    inline char const * GetName() const { return vtable->GetName(this); }
private:
    IObject(IObject const &rhs);
    IObject &operator =(IObject const &rhs);
protected:
    ~IObject()
    {}
};
#line 14 "object2.h"
#line 3 "object2.cpp"
