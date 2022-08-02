/*
 *  Copyright © 1997-2002 Metrowerks Corporation.  All Rights Reserved.
 *
 *  Questions and comments to:
 *       <mailto:support@metrowerks.com>
 *       <http://www.metrowerks.com/>
 */

namespace std
{
 #include <time.h>
}

#include <ctime>


class Time
  : private std::tm
{
public:
  Time()
  {
    std::time_t t;

    std::time(&t);
    *static_cast<std::tm*>(this) = *std::localtime(&t);
  }
  
  Time(std::time_t const t)
  {
      *static_cast<std::tm*>(this) = *std::localtime(&t);
  }

public:
  operator std::tm const *() const
  {
    return this;
  }

  std::tm const *operator &() const
  {
    return this;
  }

};

int main()
{
  Time  t;

  std::asctime(&t);
    
  return 0;
}

