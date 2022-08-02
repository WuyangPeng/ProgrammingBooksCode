/* /////////////////////////////////////////////////////////////////////////////
 * File:        member_constant_test.h
 *
 * Purpose:     
 *
 * Created      
 * Updated:     5th August 2003
 *
 * Copyright:   Synesis Software Pty Ltd, (c) 2003. All rights reserved.
 *
 * Home:        www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////////// */



#define NUM_ELEMENTS(x) (sizeof(x) / sizeof(x[0]))

#if defined(_MSC_VER) && \
    _MSC_VER < 1100
 #define bool           int
 #define false          (0)
 #define true           (1)
#endif /* _MSC_VER < 1100 */

/* ////////////////////////////////////////////////////////////////////////// */

const int       W   =   10;
const double    D   =   10;
const bool      B   =   false;

#if !defined(__WATCOMC__)
struct X
{
    int x;
};

const X g_x = { 8 };

#if defined(__INTEL_COMPILER) || \
    !defined(_MSC_VER) || \
    _MSC_VER >= 1300
class Y
{
public:
    static const int    y   =   5;
};
#endif /* !_MSC_VER || _MSC_VER >= 1100 */

class Z
{
public:
    Z(int i)
        : z(i)
    {}

public:
    int z;
};

const Z g_z = 3;


#endif /* !__WATCOMC__ */

extern "C" void mod2_fn();

/* ////////////////////////////////////////////////////////////////////////// */
