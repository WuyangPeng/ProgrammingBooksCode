/*
 *  Copyright © 1997-2002 Metrowerks Corporation.  All Rights Reserved.
 *
 *  Questions and comments to:
 *       <mailto:support@metrowerks.com>
 *       <http://www.metrowerks.com/>
 */

#include <iostream>

////////////////////////////////////////////////////////////////////////////////
#if 0

class A
{};

class B
  : public A
{};

class C
  : public A
{};

class D
  : public B
  , public C
{};

int main()
{
D *d = 0;
A *a_ = static_cast<B*>(d);  // ok

#if 1
A *a = d;    // Error. Ambiguous conversion
B *b = d;    // ok
A *a2 = b;   // ok
#endif

    return 0;
}

#endif
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
#if 0

class str2int
{
// Construction
public:
  explicit str2int(char const *s)
    : m_value(atoi(s))
  {}

// Operators
public:
  operator int() const
  {
    return m_value;
  }

// Members
protected:
  int m_value;
};

int main()
{
int val1 = str2int("34");

int val2 = (str2int)"34";

int val3 = static_cast<str2int>("34");

    return 0;
}

#endif
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
#if 1

template <typename I>
class str2int
{
// Construction
public:
  explicit str2int(char const *s);

// Operators
public:
  operator I() const
  {
    return m_value;
  }

// Members
protected:
  I m_value;
};


template <typename I>
inline str2int<I>::str2int(char const *s)
    : m_value(static_cast<I>(atoi(s)))
{}

template <>
inline str2int<long long>::str2int(char const *s)
    : m_value(strtoll(s, NULL, 10))
{}

template <>
inline str2int<bool>::str2int(char const *s)
    : m_value(strcmp(s, "true") == 0)
{}


int main()
{
short s = str2int<short>("34");

int i = str2int<int>("65536");

bool b = str2int<bool>("true");

long long ll = str2int<long long>("-9223372036854775808");

    return 0;
}

#endif
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
