/* /////////////////////////////////////////////////////////////////////////////
 * File:        Int.cpp
 *
 * Purpose:     Int main implementation file.
 *
 * Created:     15th January 2003
 * Updated:     18th January 2003
 *
 * Copyright:   Synesis Software Pty Ltd, (c) 1999-2003. All rights reserved.
 *
 * Home:        www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////////// */

#include <stlsoft_nulldef.h>


#if 0
/* ////////////////////////////////////////////////////////////////////////// */

struct Int
{
    int *pvalue;
};

// Allocation
struct Int *Int_Alloc()
{
    return new struct Int;
}

void Int_Free(struct Int *p)
{
    delete p;
}

// Initialisation
bool Int_Init(struct Int *p)
{
    p->pvalue = new int(0);

    return p->pvalue != NULL;
}

bool Int_InitValue(struct Int *p, int value)
{
    p->pvalue = new int(value);

    return p->pvalue != NULL;
}

void Int_Uninit(struct Int *p)
{
    delete p->pvalue;
}

// Manipulation

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    struct Int  *pi =   Int_Alloc();

    if(Int_InitValue(pi, 23))
    {

        Int_Uninit(pi);
    }

    Int_Free(pi);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
#else

struct Int
{
#if 0
  Int();
  Int(int value);
  Int(Int const &i)
    : pvalue(new int(*i.pvalue))
  {}
  Int const &operator =(Int const &i)
  {
    delete pvalue;

    pvalue = new int(*i.pvalue);

    return *this;
  }
  ~Int();

private:
#else
#endif /* 0 */
  int *pvalue;
};

int main(int /* argc */, char ** /*argv*/)
{
#if 0
    struct Int  i1(3);
    struct Int  i2(i1); // Does a deep copy: value semantics
#else
    struct Int  i1;
    struct Int  i2;
#endif /* 0 */

    if(i1 == i2)
    {
        int i   =   3;

        ++i;
    }

    return 0;
}

#endif /* 0 */
