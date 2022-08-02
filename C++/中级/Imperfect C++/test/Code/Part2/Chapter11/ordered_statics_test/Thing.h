

struct IThing
{
    virtual void SetName(char const *s) = 0;
    virtual char const *GetName() = 0;
};


extern "C" IThing *makeThing1();
extern "C" IThing *makeThing2();
extern "C" IThing *makeThing3();
extern "C" IThing *makeThing4();
extern "C" void   destroyThing1(IThing *);
extern "C" void   destroyThing2(IThing *);
extern "C" void   destroyThing3(IThing *);
extern "C" void   destroyThing4(IThing *);


class Thing
{
public:
    Thing(IThing *(*pfnCreate)(), void (*pfnDestroy)(IThing *));
    ~Thing();

public:
    void SetName(char const *s)
    {
        stlsoft_assert(NULL != m_thing);
        m_thing->SetName(s);
    }
    char const *GetName() const
    {
        stlsoft_assert(NULL != m_thing);
        return m_thing->GetName();
    }

private:
    IThing  *m_thing;
};

static Thing    thing1(makeThing1, destroyThing1);

static Thing    thing2(makeThing2, destroyThing2);

static Thing    thing3(makeThing3, destroyThing3);

