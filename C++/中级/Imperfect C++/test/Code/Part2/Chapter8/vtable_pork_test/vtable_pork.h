

#define LOCKABLE_CALLCONV __cdecl

#ifdef __cplusplus
struct IThing
{
public:
  virtual void LOCKABLE_CALLCONV Set(char const *) = 0;
  virtual char const *LOCKABLE_CALLCONV Get() = 0;
};

class Thing
    : public IThing
{
  void LOCKABLE_CALLCONV Set(char const *);
  char const *LOCKABLE_CALLCONV Get();

private:
    char const  *m_s;
};

#else /* ? __cplusplus */

typedef struct IThing IThing;

typedef void (LOCKABLE_CALLCONV *PFnThingSet)(IThing*, char const *);
typedef char const *(LOCKABLE_CALLCONV *PFnThingUnlock)(IThing*);

struct IThingVTable
{
  void (LOCKABLE_CALLCONV *Set)(IThing*, char const *);
  typedef char const *(LOCKABLE_CALLCONV *PFnThingUnlock)(IThing*);
  PFnThingSet   Set;
  PFnThingUnlock Get;
};
struct IThing
{
  struct IThingVTable const *vtable;
};
#endif /* __cplusplus */


#ifdef __cplusplus
extern "C"
#endif /* __cplusplus */
void PorkThing(IThing *thing);
