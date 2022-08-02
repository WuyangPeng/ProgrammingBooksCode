#ifndef CONSTRAINED_VALUE_HPP
#define CONSTRAINED_VALUE_HPP

#include <cstdlib>
#include <iostream>

using namespace std;

template<class Policy_T>
struct ConstrainedValue
{
  public:
    // public typedefs
    typedef typename Policy_T policy_type;
    typedef typename Policy_T::value_type value_type;
    typedef ConstrainedValue self;

    // default constructor
    ConstrainedValue( ) : m(Policy_T::default_value) { }
    ConstrainedValue(const self& x) : m(x.m) {  }
    ConstrainedValue(const value_type& x) { Policy_T::assign(m, x); }
    operator value_type( ) const { return m; }

    // uses the policy defined assign function
    void assign(const value_type& x) {
      Policy_T::assign(m, x);
    }

    // assignment operations
    self& operator=(const value_type& x) { assign(x); return *this; }
    self& operator+=(const value_type& x) { assign(m + x); return *this; }
    self& operator-=(const value_type& x) { assign(m - x); return *this; }
    self& operator*=(const value_type& x) { assign(m * x); return *this; }
    self& operator/=(const value_type& x) { assign(m / x); return *this; }
    self& operator%=(const value_type& x) { assign(m % x); return *this; }
    self& operator>>=(int x) { assign(m >> x); return *this; }
    self& operator<<=(int x) { assign(m << x); return *this; }

    // unary operations
    self operator-( ) { return self(-m); }
    self operator+( ) { return self(-m); }
    self operator!( ) { return self(!m); }
    self operator~( ) { return self(~m); }

    // binary operations
    friend self operator+(self x, const value_type& y) { return x += y; }
    friend self operator-(self x, const value_type& y) { return x -= y; }
    friend self operator*(self x, const value_type& y) { return x *= y; }
    friend self operator/(self x, const value_type& y) { return x /= y; }
    friend self operator%(self x, const value_type& y) { return x %= y; }
    friend self operator+(const value_type& y, self x) { return x += y; }
    friend self operator-(const value_type& y, self x) { return x -= y; }
    friend self operator*(const value_type& y, self x) { return x *= y; }
    friend self operator/(const value_type& y, self x) { return x /= y; }
    friend self operator%(const value_type& y, self x) { return x %= y; }
    friend self operator>>(self x, int y) { return x >>= y; }
    friend self operator<<(self x, int y) { return x <<= y; }

    // stream operators
    friend ostream& operator<<(ostream& o, self x) { o << x.m; return o; }
    friend istream& operator>>(istream& i, self x) {
      value_type tmp; i >> tmp; x.assign(tmp); return i;
    }

    // comparison operators
    friend bool operator<(const self& x, const self& y) { return x.m < y.m; }
    friend bool operator>(const self& x, const self& y) { return x.m > y.m; }
    friend bool operator<=(const self& x, const self& y) { return x.m <= y.m; }
    friend bool operator>=(const self& x, const self& y) { return x.m >= y.m; }
    friend bool operator==(const self& x, const self& y) { return x.m == y.m; }
    friend bool operator!=(const self& x, const self& y) { return x.m != y.m; }
  private:
    value_type m;
};

template<int Min_N, int Max_N>
struct RangedIntPolicy
{
  typedef int value_type;
  const static value_type default_value = Min_N;
  static void assign(value_type& lvalue, const value_type& rvalue) {
    if ((rvalue < Min_N) || (rvalue > Max_N)) {
      throw range_error("out of valid range");
    }
    lvalue = rvalue;
  }
};

#endif
