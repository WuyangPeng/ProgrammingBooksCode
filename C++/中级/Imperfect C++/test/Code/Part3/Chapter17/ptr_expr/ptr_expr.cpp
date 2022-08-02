/*
 *  Copyright © 1997-2002 Metrowerks Corporation.  All Rights Reserved.
 *
 *  Questions and comments to:
 *       <mailto:support@metrowerks.com>
 *       <http://www.metrowerks.com/>
 */

#include <memory>

using std::auto_ptr;

template <typename T>
class dumb_ptr
{
public:
    dumb_ptr(T *p)
        : m_p(p)
    {}

    operator T *() const
    {
        return m_p;
    }
    
protected:
    T   *m_p;
};

int main()
{
    bool                b   =   false;
    int                 i   =   3;
    void                *pv =   0;
    auto_ptr<double>    apd(new double(12.34));
    dumb_ptr<double>    dpd(new double(56.78));

    if(b)
    {}

    if( b &&
        i < 3)
    {}

    if( b &&
        pv)
    {}

    if(!apd.get())
    {}

    if(dpd)
    {}

    if( b &&
        dpd)
    {}

    if( i < 2 &&
        dpd)
    {}

    return 0;
}

