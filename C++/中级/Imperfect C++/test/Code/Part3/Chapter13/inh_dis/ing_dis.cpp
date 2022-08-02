/*
 *  Copyright © 1997-2002 Metrowerks Corporation.  All Rights Reserved.
 *
 *  Questions and comments to:
 *       <mailto:support@metrowerks.com>
 *       <http://www.metrowerks.com/>
 */

#include <cstdint>
#include <cassert>

using   std::uint16_t;
using   std::uint32_t;

class Base
{};

#if 0
// (a)
class Derived
  : public Base
  , public Base
{};


#elif 0
// (b)
class Intermediate
  : public Base
{};

class Derived
  : public Base
  , public Intermediate
{};

Derived         *d  =   0;
Intermediate    *i  =   d;
Base            *b1 =   i;
Base            *b2 =   d;

#elif 1
// (c)
class Intermediate1
  : public Base
{};

class Intermediate2
  : public Base
{};

class Derived
  : public Intermediate1
  , public Intermediate2
{};

Derived         *d  =   0;
Intermediate1   *i1 =   d;
Base            *b  =   i1;

#endif


//#include <iostream>

struct UInteger32
{
#ifdef BIG_ENDIAN
  uint16_t  high;
  uint16_t  low;
#else
  uint16_t  low;
  uint16_t  high;
#endif
};

int main()
{
uint32_t   v1   = 0x01234567;
UInteger32 ui32 = *reinterpret_cast<UInteger32*>(&v1);
uint32_t   v2   = *reinterpret_cast<uint32_t*>(&ui32);

assert(v1 == v2);



//  using namespace std;
    
//  cout << "Hello World, this is CodeWarrior!" << endl;
    
    return 0;
}

