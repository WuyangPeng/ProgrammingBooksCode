/* /////////////////////////////////////////////////////////////////////////////
 * File:        sequence_7.hpp
 *
 * Purpose:     Implementation of the Fibonacci_sequence class. 
 *
 * Created:     18th August 2005
 * Updated:     20th August 2005
 *
 * Author:      Matthew Wilson
 *
 * Copyright:   Synesis Software Pty Ltd, 2005. All rights reserved.
 *
 * Home:        www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////////// */



#if defined(__GNUC__)
//# undef STLSOFT_CF_MEMBER_CONSTANT_SUPPORT
#endif /* compiler */

template <typename T>
struct Fibonacci_traits;

template <>
struct Fibonacci_traits<stlsoft::uint32_t>
{
#ifdef STLSOFT_CF_MEMBER_CONSTANT_SUPPORT
  static const stlsoft::uint32_t	maxThreshold  = 2971215073;
  static const size_t				maxLimit      = 47;
#else /* ? STLSOFT_CF_MEMBER_CONSTANT_SUPPORT */
  static stlsoft::uint32_t			maxThreshold()  { return 2971215073;	}
  static size_t						maxLimit()		{ return 47;			}
#endif /* STLSOFT_CF_MEMBER_CONSTANT_SUPPORT */
};

template <>
struct Fibonacci_traits<stlsoft::uint64_t>
{
#ifdef STLSOFT_CF_MEMBER_CONSTANT_SUPPORT
  static const stlsoft::uint64_t	maxThreshold  = __STLSOFT_GEN_UINT64_SUFFIX(12200160415121876738);
  static const size_t				maxLimit      = 93;
#else /* ? STLSOFT_CF_MEMBER_CONSTANT_SUPPORT */
  static stlsoft::uint64_t			maxThreshold()  { return __STLSOFT_GEN_UINT64_SUFFIX(12200160415121876738);	}
  static size_t						maxLimit()		{ return 93;												}
#endif /* STLSOFT_CF_MEMBER_CONSTANT_SUPPORT */
};

class Fibonacci_sequence
{
public:
#ifdef XSTL_FIBONACCI_USE_64BIT
  typedef stlsoft::uint64_t							value_type;
#else /* ? XSTL_FIBONACCI_USE_64BIT */
  typedef stlsoft::uint32_t							value_type;
#endif /* XSTL_FIBONACCI_USE_64BIT */
  typedef Fibonacci_traits<value_type>				traits_type;
  typedef stlsoft::true_typedef<size_t, unsigned>   limit;
  typedef stlsoft::true_typedef<value_type, signed> threshold;
  class												const_iterator;
public: // Construction
#ifdef STLSOFT_CF_MEMBER_CONSTANT_SUPPORT
  explicit Fibonacci_sequence(limit l = limit(traits_type::maxLimit));
#else /* ? STLSOFT_CF_MEMBER_CONSTANT_SUPPORT */
  explicit Fibonacci_sequence(limit l = limit(traits_type::maxLimit()));
#endif /* STLSOFT_CF_MEMBER_CONSTANT_SUPPORT */
  explicit Fibonacci_sequence(threshold t);
  ~Fibonacci_sequence()
  {
	STLSOFT_STATIC_ASSERT(stlsoft::is_integral_type<value_type>::value);
#ifdef __STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT
	STLSOFT_STATIC_ASSERT(	(stlsoft::is_same_type<	stlsoft::sign_traits<value_type>::type
												,	stlsoft::sign_traits<value_type>::unsigned_type
												>::value));
#endif /* __STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT */
  }
public: // Iteration
  const_iterator  begin() const;
  const_iterator  end() const;
public: // Size
  bool  empty() const
  {
#if defined(STLSOFT_COMPILER_IS_DMC) || \
	defined(STLSOFT_COMPILER_IS_MSVC)
    return 0 == m_limit.base_type_value() && 0 == m_threshold.base_type_value();
#else /* ? compiler */
    return 0 == m_limit && 0 == m_threshold;
#endif /* compiler */
  }
  size_t max_size() const
  {
#ifdef STLSOFT_CF_MEMBER_CONSTANT_SUPPORT
    return traits_type::maxLimit;
#else /* ? STLSOFT_CF_MEMBER_CONSTANT_SUPPORT */
    return traits_type::maxLimit();
#endif /* STLSOFT_CF_MEMBER_CONSTANT_SUPPORT */
  }
private:
  const limit		m_limit;
  const threshold	m_threshold;
};

class Fibonacci_sequence::const_iterator
	: public stlsoft_ns_qual(iterator_base)<stlsoft_ns_qual_std(forward_iterator_tag)
										,	Fibonacci_sequence::value_type
										,	ptrdiff_t
										,	void
										,	const Fibonacci_sequence::value_type
										>
{
public:
	typedef const_iterator					class_type;
	typedef Fibonacci_sequence::value_type	value_type;

/// Construction
private:
	friend class Fibonacci_sequence;
	const_iterator();
	const_iterator(Fibonacci_sequence::limit l);
	const_iterator(Fibonacci_sequence::threshold t);

public:
	class_type &operator ++();
	class_type operator ++(int);
	value_type operator *() const;

/// Comparison
public:
	bool equal(class_type const &rhs) const;

private:
	value_type		m_i0;
	value_type		m_i1;
	size_t			m_stepIndex;
	const limit		m_limit;
	const threshold	m_threshold;
};

/* ////////////////////////////////////////////////////////////////////////// */

inline Fibonacci_sequence::Fibonacci_sequence(limit l /* = limit(traits_type::maxLimit) */)
	: m_limit(l)
	, m_threshold(0)
{
#ifdef STLSOFT_CF_MEMBER_CONSTANT_SUPPORT
//	STLSOFT_MESSAGE_ASSERT("Fibonacci sequence construction limit exceeded", l <= traits_type::maxLimit);
#else /* ? STLSOFT_CF_MEMBER_CONSTANT_SUPPORT */
	STLSOFT_MESSAGE_ASSERT("Fibonacci sequence construction limit exceeded", l <= traits_type::maxLimit());
#endif /* STLSOFT_CF_MEMBER_CONSTANT_SUPPORT */
}

inline Fibonacci_sequence::Fibonacci_sequence(threshold t)
	: m_limit(0)
	, m_threshold(t)
{
#ifdef STLSOFT_CF_MEMBER_CONSTANT_SUPPORT
//	STLSOFT_MESSAGE_ASSERT("Fibonacci sequence construction threshold exceeded", t <= traits_type::maxThreshold);
#else /* ? STLSOFT_CF_MEMBER_CONSTANT_SUPPORT */
	STLSOFT_MESSAGE_ASSERT("Fibonacci sequence construction threshold exceeded", t <= traits_type::maxThreshold());
#endif /* STLSOFT_CF_MEMBER_CONSTANT_SUPPORT */
}


inline Fibonacci_sequence::const_iterator Fibonacci_sequence::begin() const
{
	return const_iterator();
}

inline Fibonacci_sequence::const_iterator Fibonacci_sequence::end() const
{
#if defined(STLSOFT_COMPILER_IS_DMC) || \
	defined(STLSOFT_COMPILER_IS_MSVC)
	if(0 == m_limit.base_type_value())
#else /* ? compiler */
	if(0 == m_limit)
#endif /* compiler */
	{
		return const_iterator(m_threshold);
	}
	else
	{
		return const_iterator(m_limit);
	}
}

/* ////////////////////////////////////////////////////////////////////////// */

inline Fibonacci_sequence::const_iterator::const_iterator()
	: m_i0(0)
	, m_i1(1)
	, m_stepIndex(0)
	, m_limit()
	, m_threshold()
{}

inline Fibonacci_sequence::const_iterator::const_iterator(Fibonacci_sequence::limit l)
	: m_i0(0)
	, m_i1(0)
	, m_stepIndex(0)
	, m_limit(l)
	, m_threshold()
{}

inline Fibonacci_sequence::const_iterator::const_iterator(Fibonacci_sequence::threshold t)
	: m_i0(0)
	, m_i1(0)
	, m_stepIndex(0)
	, m_limit()
	, m_threshold(t)
{}

inline Fibonacci_sequence::const_iterator::class_type &Fibonacci_sequence::const_iterator::operator ++()
{
	STLSOFT_MESSAGE_ASSERT("Fibonacci sequence has exhausted limitations of integral type", m_i0 <= m_i1);

	value_type	res		=	m_i0 + m_i1;
				m_i0	=	m_i1;
				m_i1	=	res;

	++m_stepIndex;

	return *this;
}

inline Fibonacci_sequence::const_iterator::class_type Fibonacci_sequence::const_iterator::operator ++(int)
{
	class_type	r(*this);

	operator ++();

	return r;
}

inline Fibonacci_sequence::const_iterator::value_type Fibonacci_sequence::const_iterator::operator *() const
{
	return m_i0;
}

inline bool Fibonacci_sequence::const_iterator::equal(Fibonacci_sequence::const_iterator::class_type const &rhs) const
{
	// At this point we have nine possibilities, of which only seven are valid:

	// 1. lhs = <normal>, rhs = <normal>
	// 2. lhs = <normal>, rhs = <end, limit>
	// 3. lhs = <normal>, rhs = <end, threshold>
	// 4. lhs = <end, limit>, rhs = <normal>
	// 5. lhs = <end, threshold>, rhs = <normal>
	// 6. lhs = <end, limit>, rhs = <end, limit>
	// 7. lhs = <end, threshold>, rhs = <end, threshold>
	//
	// 8. lhs = <end, limit>, rhs = <end, threshold> - INVALID
	// 9. lhs = <end, threshold>, rhs = <end, limit> - INVALID

	enum type
	{
			normal			=	0 // We'll rely on this later
		,	endLimit		=	1
		,	endThreshold	=	5
	};

	int			this_type;
	int			rhs_type;
	const int	factor		=	3;

	if(0 != m_i1)
	{
		this_type = normal;
	}
#if defined(STLSOFT_COMPILER_IS_DMC) || \
	defined(STLSOFT_COMPILER_IS_MSVC)
	else if(0 != m_threshold.base_type_value())
#else /* ? compiler */
	else if(0 != m_threshold)
#endif /* compiler */
	{
		this_type = endThreshold;
	}
	else
	{
		this_type = endLimit;
	}

	if(0 != rhs.m_i1)
	{
		rhs_type = normal;
	}
#if defined(STLSOFT_COMPILER_IS_DMC) || \
	defined(STLSOFT_COMPILER_IS_MSVC)
	else if(0 != rhs.m_threshold.base_type_value())
#else /* ? compiler */
	else if(0 != rhs.m_threshold)
#endif /* compiler */
	{
		rhs_type = endThreshold;
	}
	else
	{
		rhs_type = endLimit;
	}

	switch(this_type + rhs_type * factor)
	{
		case	normal + normal * factor:				// 1. lhs = <normal>, rhs = <normal>
			return m_i0 == rhs.m_i0 && m_i1 == rhs.m_i1;
		case	normal + endLimit * factor:				// 2. lhs = <normal>, rhs = <end, limit>
			return m_stepIndex == rhs.m_limit;
		case	normal + endThreshold * factor:			// 3. lhs = <normal>, rhs = <end, threshold>
			STLSOFT_ASSERT((m_i0 >= rhs.m_threshold) == (m_i0 >= rhs.m_threshold.base_type_value()));
            return m_i0 >= rhs.m_threshold;
		case	endLimit + normal * factor:				// 4. lhs = <end, limit>, rhs = <normal>
			return rhs.m_stepIndex == m_limit;
		case	endLimit + endLimit * factor:			// 6. lhs = <end, limit>, rhs = <end, limit>
			STLSOFT_ASSERT(m_limit == rhs.m_limit);
			return true;
		case	endLimit + endThreshold * factor:		// 8. lhs = <end, limit>, rhs = <end, threshold> - INVALID
			STLSOFT_MESSAGE_ASSERT("Invalid permutation", 0);
			break;
		case	endThreshold + normal * factor:			// 5. lhs = <end, threshold>, rhs = <normal>
            return rhs.m_i0 >= m_threshold;
		case	endThreshold + endLimit * factor:		// 9. lhs = <end, threshold>, rhs = <end, limit> - INVALID
			STLSOFT_MESSAGE_ASSERT("Invalid permutation", 0);
			break;
		case	endThreshold + endThreshold * factor:	// 7. lhs = <end, threshold>, rhs = <end, threshold>
			STLSOFT_ASSERT(m_threshold == rhs.m_threshold);
			return true;
		default:
			STLSOFT_MESSAGE_ASSERT("Unknown permutation", 0);
			break;
	}

	return false;
}

/* ////////////////////////////////////////////////////////////////////////// */

inline bool operator ==(Fibonacci_sequence::const_iterator const &lhs, Fibonacci_sequence::const_iterator const &rhs)
{
	return lhs.equal(rhs);
}

inline bool operator !=(Fibonacci_sequence::const_iterator const &lhs, Fibonacci_sequence::const_iterator const &rhs)
{
	return !lhs.equal(rhs);
}

#if defined(STLSOFT_COMPILER_IS_MSVC) && \
	_MSC_VER < 131
namespace std
{

inline bool operator ==(Fibonacci_sequence::const_iterator const &lhs, Fibonacci_sequence::const_iterator const &rhs)
{
	return lhs.equal(rhs);
}

inline bool operator !=(Fibonacci_sequence::const_iterator const &lhs, Fibonacci_sequence::const_iterator const &rhs)
{
	return !lhs.equal(rhs);
}

} // namespace std
#endif /* compiler */

/* ////////////////////////////////////////////////////////////////////////// */
