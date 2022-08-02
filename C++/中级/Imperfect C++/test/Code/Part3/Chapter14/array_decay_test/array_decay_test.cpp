/* /////////////////////////////////////////////////////////////////////////////
 * File:        array_decay_test.cpp
 *
 * Purpose:     Implementation file for the array_decay_test project.
 *
 * Created:     19th October 2003
 * Updated:     19th October 2003
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (C) 1999-2003, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              email:      software@synesis.com.au
 *
 *              This source code is placed into the public domain 2003
 *              by Synesis Software Pty Ltd. There are no restrictions
 *              whatsoever to your use of the software. 
 *
 *              This source code is provided by Synesis Software Pty Ltd "as is"
 *              and any warranties, whether expressed or implied, including, but
 *              not limited to, the implied warranties of merchantability and
 *              fitness for a particular purpose are disclaimed. In no event
 *              shall the Synesis Software Pty Ltd be liable for any direct,
 *              indirect, incidental, special, exemplary, or consequential
 *              damages (including, but not limited to, procurement of
 *              substitute goods or services; loss of use, data, or profits; or
 *              business interruption) however caused and on any theory of
 *              liability, whether in contract, strict liability, or tort
 *              (including negligence or otherwise) arising in any way out of
 *              the use of this software, even if advised of the possibility of
 *              such damage. 
 *
 *              Neither the name of Synesis Software Pty Ltd nor the names of
 *              any subdivisions, employees or agents of Synesis Software Pty
 *              Ltd, nor the names of any other contributors to this software
 *              may be used to endorse or promote products derived from this
 *              software without specific prior written permission. 
 *
 * ////////////////////////////////////////////////////////////////////////// */

#include <stdio.h>
#include <stlsoft.h>

/* ////////////////////////////////////////////////////////////////////////// */

#ifndef assert
# define assert         stlsoft_assert
#endif /* assert */

#ifndef dimensionof
# define dimensionof    stlsoft_num_elements
#endif /* dimensionof */

/* ////////////////////////////////////////////////////////////////////////// */

#if 0
template <typename T>
class array_proxy
{
// Construction
public:
  template <size_t N>
  explicit array_proxy(T (&t)[N])
    : m_base(t)
    , m_size(N)
  {}
  explicit array_proxy(T *base, size_t size)
    : m_base(t)
    , m_size(size)
  {}

// State
public:
  T *base()
  {
    return m_base;
  }
  size_t size() const
  {
    return m_size;
  }

// Members
private:
  pointer const m_base;
  size_t const  m_size;

// Not to be implemented
private:
  array_proxy &operator =(array_proxy const &);
};

template <typename T, size_t N>
inline array_proxy<T> make_array_proxy(T (&t)[N])
{
  return array_proxy<T>(t);
}
#endif /* 0 */


/* ////////////////////////////////////////////////////////////////////////// */

void process_array(int ar[10])
//void process_array(int ar[20])
//void process_array(int ar[])
//void process_array(int *ar)
{
  printf("[");
  for(int i = 0; i < dimensionof(ar); ++i)
  {
    printf("%d ", ar[i]);
  }
  printf("]\n");
}

/* ////////////////////////////////////////////////////////////////////////// */

int main()
{
  int ar1[10];
  int i;

  for(i = 0; i < dimensionof(ar1); ++i)
  {
    ar1[i] = i;
  }
  assert(10 == i);

  process_array(ar1);

  return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
