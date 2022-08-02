
#ifdef __cplusplus

struct IObject
{
    virtual void SetName(char const *s) = 0;
    virtual char const *GetName() = 0;
};

#else /* ? __cplusplus */

typedef struct IObject IObject;

struct IObjectVTable
{
#if 1
    unsigned    v1;
    void        (*v2)();
    unsigned    v3;
    void (*SetName)(IObject *, char const *s);
    unsigned    v4;
    char const *(*GetName)(IObject *);
#if 0
#endif /* 0 */
#else
    char const
#endif /* 0 */
};

struct IObject
{
    struct IObjectVTable *vtable;
};

#endif /* __cplusplus */

#ifdef __cplusplus
extern "C"
#else /* ? __cplusplus */
extern 
#endif /* __cplusplus */ 
int make_Object(IObject **pp);


