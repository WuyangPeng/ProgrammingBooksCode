/* /////////////////////////////////////////////////////////////////////////////
 * File:        friend_op_2_test.cpp
 *
 * Purpose:     Implementation file for the friend_op_2_test project.
 *
 * Created:     6th January 2006
 * Updated:     6th January 2006
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright (c) 2006, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              This source code is placed into the public domain 2006
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

//#define PLAIN_FORM
//#define STATIC_FORM
//#define FRIEND_OP_FORM
//#define FRIEND_OP_FORM_WITH_DEFN
//#define EQUAL_FORM

#if !defined(PLAIN_FORM) && \
	!defined(STATIC_FORM) && \
	!defined(FRIEND_OP_FORM) && \
	!defined(FRIEND_OP_FORM_WITH_DEFN) && \
	!defined(EQUAL_FORM)
# error Must define PLAIN_FORM or STATIC_FORM or FRIEND_OP_FORM or FRIEND_OP_FORM_WITH_DEFN or EQUAL_FORM
#endif

/* /////////////////////////////////////////////////////////////////////////////
 * Compiler warnings
 */

#if defined(__BORLANDC__)
# pragma warn -8008
#endif

/* /////////////////////////////////////////////////////////////////////////////
 * Definitions
 */

#if defined(FRIEND_OP_FORM)
# if defined(__GNUC__) || \
	 (	defined(_MSC_VER) && \
		_MSC_VER == 900)

template< class C
        >
class basic_path;

template< class C
        >
int operator ==(basic_path<C> const &lhs, basic_path<C> const &rhs);

template< class C
        >
int operator ==(basic_path<C> const &lhs, C const *rhs);

template< class C
        >
int operator ==(C const *lhs, basic_path<C> const &rhs);

template< class C
        >
int operator <(basic_path<C> const &lhs, basic_path<C> const &rhs);

template< class C
        >
int operator <(basic_path<C> const &lhs, C const *rhs);

template< class C
        >
int operator <(C const *lhs, basic_path<C> const &rhs);

# endif /* compiler */
#endif /* FRIEND_OP_FORM */



template< class C
        >
class basic_path
{
public: // Member Types
  typedef basic_path<C/* , T, A */>   class_type;
public: // Comparison
#if defined(PLAIN_FORM)
  int operator ==(class_type const &rhs) const;
  int operator ==(C const *rhs) const;
  int operator <(class_type const &rhs) const;
  int operator <(C const *rhs) const;
#elif defined(STATIC_FORM)
  static int operator ==(class_type const &lhs, class_type const &rhs);
  static int operator ==(class_type const &lhs, C const *rhs);
  static int operator ==(C const *lhs, class_type const &rhs);
  static int operator <(class_type const &lhs, class_type const &rhs);
  static int operator <(class_type const &lhs, C const *rhs);
  static int operator <(C const *lhs, class_type const &rhs);
#elif defined(FRIEND_OP_FORM)
# if defined(__GNUC__)
  friend int operator ==<>(class_type const &lhs, class_type const &rhs);
  friend int operator ==<>(class_type const &lhs, C const *rhs);
  friend int operator ==<>(C const *lhs, class_type const &rhs);
  friend int operator < <>(class_type const &lhs, class_type const &rhs);
  friend int operator < <>(class_type const &lhs, C const *rhs);
  friend int operator < <>(C const *lhs, class_type const &rhs);
# else
  friend int operator ==(class_type const &lhs, class_type const &rhs);
  friend int operator ==(class_type const &lhs, C const *rhs);
  friend int operator ==(C const *lhs, class_type const &rhs);
  friend int operator <(class_type const &lhs, class_type const &rhs);
  friend int operator <(class_type const &lhs, C const *rhs);
  friend int operator <(C const *lhs, class_type const &rhs);
# endif 
#elif defined(FRIEND_OP_FORM_WITH_DEFN)
  friend int operator ==(class_type const &lhs, class_type const &rhs)
  {
	  return 0;
  }
  friend int operator ==(class_type const &lhs, C const *rhs)
  {
	  return 0;
  }
  friend int operator ==(C const *lhs, class_type const &rhs)
  {
	  return 0;
  }
  friend int operator <(class_type const &lhs, class_type const &rhs)
  {
	  return 0;
  }
  friend int operator <(class_type const &lhs, C const *rhs)
  {
	  return 0;
  }
  friend int operator <(C const *lhs, class_type const &rhs)
  {
	  return 0;
  }
#elif defined(EQUAL_FORM)
  int equal(class_type const &rhs) const;
  int equal(C const *rhs) const;
  int compare(class_type const &rhs) const;
  int compare(C const *rhs) const;
#endif
};

#if defined(EQUAL_FORM)
template< class C
        >
int operator ==(basic_path<C> const &lhs, basic_path<C> const &rhs)
{
	return lhs.equal(rhs);
}

template< class C
        >
int operator ==(basic_path<C> const &lhs, C const *rhs)

{
	return lhs.equal(rhs);
}

template< class C
        >
int operator ==(C const *lhs, basic_path<C> const &rhs)
{
	return rhs.equal(lhs);
}

template< class C
        >
int operator <(basic_path<C> const &lhs, basic_path<C> const &rhs)
{
	return lhs.compare(rhs) < 0;
}

template< class C
        >
int operator <(basic_path<C> const &lhs, C const *rhs)
{
	return lhs.compare(rhs) < 0;
}

template< class C
        >
int operator <(C const *lhs, basic_path<C> const &rhs)
{
	return 0 < rhs.compare(lhs);
}
#endif


/* ////////////////////////////////////////////////////////////////////////// */

static int main_(int /* argc */, char ** /*argv*/)
{
	/* . */
	typedef basic_path<char>	path_t;

	path_t	p1;
	path_t	p2;

	if(p1 == p2)
	{}
	if(p1 == "path")
	{}
#if !defined(PLAIN_FORM)
	if("path2" == p2)
	{}
#endif /* !PLAIN_FORM */

	if(p1 < p2)
	{}
	if(p1 < "path")
	{}
#if !defined(PLAIN_FORM)
	if("path2" < p2)
	{}
#endif /* !PLAIN_FORM */

    return 0;
}

int main(int argc, char *argv[])
{
	return main_(argc, argv);
}

/* ////////////////////////////////////////////////////////////////////////// */
