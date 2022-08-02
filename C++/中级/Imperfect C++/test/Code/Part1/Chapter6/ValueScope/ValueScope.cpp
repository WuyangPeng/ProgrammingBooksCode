/*
 *  Copyright © 1997-2002 Metrowerks Corporation.  All Rights Reserved.
 *
 *  Questions and comments to:
 *       <mailto:support@metrowerks.com>
 *       <http://www.metrowerks.com/>
 */

#include <iostream>

template <typename T>
struct reference_cast
{
  typedef reference_cast<T>  class_type;
  
public:
  explicit reference_cast(T &t)
    : m_t(t)
  {}
  
  operator T &() const
  {
    return const_cast<class_type*>(this)->m_t;
  }

private:
  T &m_t;  
};

template <>
struct reference_cast<int>
{
  explicit reference_cast(int i)
    : m_i(i)
  {}
  
  operator int() const
  {
    return m_i;
  }

private:
  int m_i;
};

template <typename T>
struct is_pod
{
};



template <typename T>
class ValueScope
{
public:
  typedef T              value_type;
  typedef ValueScope<T>  class_type;
  typedef value_type     &reference;

// Construction
public:
  template <typename V>
  ValueScope(reference var, V const &set)
    : m_var(var)
    , m_revert(var)
  {
    m_var = set;
  }

  template <typename V1, typename V2>
  ValueScope(reference var, V1 const &set, V2 const &revert)
    : m_var(var)
    , m_revert(revert)
  {
    m_var = set;
  }

  ~ValueScope() throw()
  {
    m_var = m_revert;
  }

// Members
protected:
  reference   m_var;
  value_type  m_revert;

// Not to be implemented
public:
  ValueScope(class_type const &);
  ValueScope const &operator =(class_type const &);
};

int main()
{
    using namespace std;

    int     i1  =   33;
    int     i2  =   33;
    string  s1  =   "Original 1";
    string  s2  =   "Original 2";

//  ValueScope<int> v;

    cout << "i1: " << i1 << endl;
    {
        ValueScope<int> vs(i1, reference_cast<int>(20));

        cout << "i1: " << i1 << endl;
    }
    cout << "i1: " << i1 << endl;
    
    cout << "i2: " << i2 << endl;
    {
        ValueScope<int> vs(i2, 20, 10);

        cout << "i2: " << i2 << endl;
    }
    cout << "i2: " << i2 << endl;

    cout << "s1: " << s1 << endl;
    {
//      char const  *s  =   reference_cast<char const*>("Rebel");
//      ValueScope<string>  vs(s1, s);
        ValueScope<string>  vs(s1, "Rebel");

        cout << "s1: " << s1 << endl;
    }
    cout << "s1: " << s1 << endl;

    cout << "s2: " << s2 << endl;
    {
//      char const  *s  =   reference_cast<char const*>("Rebel");
//      ValueScope<string>  vs(s2, s);
        ValueScope<string>  vs(s2, "Matthew", "woz 'ere");

        cout << "s2: " << s2 << endl;

        string  sarah("Sarah");
        string  is_out("is out");
        ValueScope<string>  v2(s2, sarah, is_out);

        cout << "s2: " << s2 << endl;
    }
    cout << "s2: " << s2 << endl;
    
    return 0;
}

