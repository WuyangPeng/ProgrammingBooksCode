/*
 *  Copyright © 1997-2002 Metrowerks Corporation.  All Rights Reserved.
 *
 *  Questions and comments to:
 *       <mailto:support@metrowerks.com>
 *       <http://www.metrowerks.com/>
 */

#include <vector>
#include <string>




class Double
{
public:
  typedef double  value_type;

// Constructors
public:
  Double()
    : m_d(0.0)
  {}    
  Double(double d)
    : m_d(d)
  {}    

// Accessors
  double GetValue() const
  {
    return m_d;
  }

// Members
protected:
  double m_d;
};

#if 1
template <typename T>
class ImplicitAccessProvider
  : public T
{
public:
  typedef T   base_class_type;

// Construction
public:
  ImplicitAccessProvider()
  {}

  template <typename T1>
  explicit ImplicitAccessProvider(T1 &t1)
    :  base_class_type (t1)
  {}

public:
  operator typename T::value_type() const
  {
    return T::GetValue();
  }
};

#else

template <typename T>
class ImplicitAccessProvider
  : public T
{
public:
  typedef T   base_class_type;

// Conversion
public:
  operator typename base_class_type::value_type() const
  {
    return base_class_type::GetValue();
  }
};
#endif

typedef ImplicitAccessProvider<Double>  Double_t;


int main()
{
    Double_t    d1;
    double const        v0(12.34);
//  Double_t    d2(12.34); // Error
    Double_t    d2(v0); // Error
    double      v1 = d1;


    return 0;
}

