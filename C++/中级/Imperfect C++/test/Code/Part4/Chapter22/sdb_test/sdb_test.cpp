/*
 *  Copyright © 1997-2002 Metrowerks Corporation.  All Rights Reserved.
 *
 *  Questions and comments to:
 *       <mailto:support@metrowerks.com>
 *       <http://www.metrowerks.com/>
 */


template <typename T>
struct BoltIn
{
    void DoIt()
    {
        T   *pT = static_cast<T*>(this);
    
        pT->Do();
    }
};

struct Y
{};

class X
  : public BoltIn<X>
{
public:
    void Do()
    {
    }
};


int main()
{
    X   x;

    x.DoIt();

    return 0;
}

