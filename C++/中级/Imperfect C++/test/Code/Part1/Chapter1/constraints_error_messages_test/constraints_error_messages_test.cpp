/* /////////////////////////////////////////////////////////////////////////////
 * File:        constraints_error_messages_test.cpp
 *
 * Purpose:     Implementation file for the constraints_error_messages_test project.
 *
 * Created:     12th January 2004
 * Updated:     12th January 2004
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (C) 1999-2004, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              email:      software@synesis.com.au
 *
 *              This source code is placed into the public domain 2004
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
#include <stlsoft_constraints.h>

/* ////////////////////////////////////////////////////////////////////////// */

class B
{};

class D
    : public B
{};

class P
    : protected B
{
};

struct V1
{
    virtual ~V1()
    {}
};

struct V2
{
    V2(int v)
    {}
};

struct V3
{
    V3()
    {}
};

struct V4
{
    virtual void method() const
    {}
};

template <typename T>
struct must_be_pod_
{
  ~must_be_pod_()
  {
    int (*p)() = constraints;
  }
private:
  static int constraints()
  {
    union
    {
      T   T_is_not_a_POD_type;
      int i; // Not used
    } u;
    return (&u)->i;
  }
};

/* ////////////////////////////////////////////////////////////////////////// */

int main(int /* argc */, char ** /*argv*/)
{
    puts("constraints_error_messages_test: " __STLSOFT_COMPILER_LABEL_STRING);

    /* . */
    stlsoft_constraint_must_have_base(D, B);
//  stlsoft_constraint_must_have_base(P, B);

#if 0
#if 0
    stlsoft::must_be_pod<int>();
    stlsoft::must_be_pod<B>();
    stlsoft::must_be_pod<V>();
#else /* ? 0 */
    stlsoft_constraint_must_be_pod(int);
    stlsoft_constraint_must_be_pod(B);
    stlsoft_constraint_must_be_pod(V1);
//  stlsoft_constraint_must_be_pod(V2);
    stlsoft_constraint_must_be_pod(V3);
    stlsoft_constraint_must_be_pod(V4);
#endif /* 0 */
#else /* ? 0 */
    must_be_pod_<int>();
    must_be_pod_<B>();
//  must_be_pod_<V1>();
//  must_be_pod_<V2>();
//  must_be_pod_<V3>();
    must_be_pod_<V4>();
#endif /* 0 */

    return 0;
}

/* ////////////////////////////////////////////////////////////////////////// */
