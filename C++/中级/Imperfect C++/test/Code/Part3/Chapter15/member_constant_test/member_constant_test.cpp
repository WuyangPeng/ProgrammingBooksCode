/* /////////////////////////////////////////////////////////////////////////////
 * File:        member_constant_test.cpp
 *
 * Purpose:     Implementation file for the member_constant_test project.
 *
 * Created:     5th August 2003
 * Updated:     5th March 2004
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

#include <limits>

#include "member_constant_test.h"

const double pi = 3.141592653590;

namespace Maths_
{
  const double pi = 3.141592653590;
}

class XXX
{
  static const int i1 = std::numeric_limits<char>::digits; // Ok
  static const int i2 = std::numeric_limits<char>::max(); // Error
};

class Maths
{
public:
#if 0
  const double pi = 3.141592653590; // Compiler may not support
  enum
  {
    pi = 3.141592653590             // Illegal
  };
#endif /* 0 */
  static const double pi()
  {
    return 3.14159265358979323846264;
  }
};


const int   i   =   1;

const double pi2 = Maths::pi();

int pi1_valid[(std::numeric_limits<char>::digits < 1000)];
int pi2_valid[(std::numeric_limits<char>::max() < 1000)];


#if 0
enum BigEnum
{
    big = 0x8765432187654321
};
#endif /* 0 */

/* ////////////////////////////////////////////////////////////////////////// */

#if !defined(__WATCOMC__)
extern const Z g_z3;

const Z g_z2 = g_z3;
const Z g_z3 = g_z;
#endif /* !__WATCOMC__ */

/* ////////////////////////////////////////////////////////////////////////// */

#if !defined(__WATCOMC__)
/* static */ const int  Y::y;
#endif /* !__WATCOMC__ */

int main(int /* argc */, char ** /*argv*/)
{
#if !defined(__WATCOMC__)
    printf("main: &g_z.z == %p\n", &g_z.z);
//  printf("main: &Y::y == %p\n", &Y::y);
    mod2_fn();
#endif /* !__WATCOMC__ */

#if !defined(__WATCOMC__)
    const int &ci = Y::y;
#endif /* !__WATCOMC__ */

    enum
    {
            b = B
//      ,   d = D
    };

#if !defined(__WATCOMC__)
    printf("%d %d %d\n", g_z.z, g_z2.z, g_z3.z);
#endif /* !__WATCOMC__ */

    int &w = const_cast<int&>(W);

    int const   *p = &W;

    w *= 2;

    int const   *q = &W;

    /* . */
//  int g[B];
//  int h[D];
    int i[W];
//  int j[g_x.x];
#if !defined(__WATCOMC__) && \
    (   !defined(_MSC_VER) || \
        _MSC_VER >= 1300)
    int k[Y::y];
#endif /* !__WATCOMC__ */
//  int l[g_z.z];

    printf("[%d, %d, %d, %d, %d]\n", W, NUM_ELEMENTS(i), w, *p, *q);

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
