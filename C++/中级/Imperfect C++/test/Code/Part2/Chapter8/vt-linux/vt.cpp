
#include <new>
#include <stdio.h>

#include "vt.h"

class Object
    : public IObject
{
public:
    Object()
        : m_name("No Name Set")
    {
        printf("{{Object::Object}}(0x%p): (0x%p, %s)\n", this, m_name, m_name);

printf("sizeof(IObject): %u\n", sizeof(IObject));

        void **pvThis = (void**)this;

        printf("pvThis:   0x%p [0x%p]\n", pvThis, *pvThis);
        printf("pvThis+1: 0x%p [0x%p]\n", pvThis + 1, *(pvThis + 1));
    }
public:
    void SetName(char const *name)
    {
        printf("{{Object::SetName()}}\n");


//printf("&SetName: 0x%p\n", &Object::SetName);

        int x = 1;
        int y = 2;

//      asm("nop");
        asm("mov %0,%%eax" : : "n" (100));
        asm("mov %%esp,%0" : "=m" (x) : );

//#pragma asm mov [x], name
//#pragma asm mov y, x

//printf("x:\t0x%08x\n", x);

        printf("SetName(0x%p):\t(0x%p, %s)\n", this, name, name);

        m_name = name;
    }
    char const *GetName()
    {
        printf("{{Object::GetName()}}\n");

        return m_name;
    }

public:
    void *operator new (size_t cb, std::nothrow_t const &nt)
    {
        void    *pv = ::operator new(cb, nt);

        printf("Allocating %u bytes for Object (0x%p) instance\n", cb, pv);

        return pv;
    }
private:
    char const  *m_name;
};

extern "C" int make_Object(IObject **pp)
{
    *pp = new(std::nothrow) Object();

    printf("(*pp):\t0x%p\n", *pp);

    return (*pp) != NULL;
}

