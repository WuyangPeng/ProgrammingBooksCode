/* /////////////////////////////////////////////////////////////////////////////
 * File:        sequence_2.hpp
 *
 * Purpose:     Implementation of the Fibonacci_sequence class. 
 *
 * Created:     10th August 2005
 * Updated:     20th August 2005
 *
 * Author:      Matthew Wilson
 *
 * Copyright:   Synesis Software Pty Ltd, 2005. All rights reserved.
 *
 * Home:        www.synesis.com.au/software
 *
 * ////////////////////////////////////////////////////////////////////////// */



class Fibonacci_sequence
{
public:
#ifdef XSTL_FIBONACCI_USE_64BIT
	typedef stlsoft::uint64_t	value_type;
#else /* ? XSTL_FIBONACCI_USE_64BIT */
	typedef stlsoft::uint32_t	value_type;
#endif /* XSTL_FIBONACCI_USE_64BIT */
	class						const_iterator;

public:
	Fibonacci_sequence();
	~Fibonacci_sequence()
	{
		STLSOFT_STATIC_ASSERT(stlsoft::is_integral_type<value_type>::value);
#ifdef __STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT
		STLSOFT_STATIC_ASSERT(	(stlsoft::is_same_type<	stlsoft::sign_traits<value_type>::type
													,	stlsoft::sign_traits<value_type>::unsigned_type
													>::value));
#endif /* __STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT */
	}

public:
	const_iterator	begin() const;
	const_iterator	end() const;
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

public:
	const_iterator(value_type i0, value_type i1);

public:
	class_type &operator ++();
	class_type operator ++(int);
	value_type operator *() const;

/// Comparison
public:
	bool equal(class_type const &rhs) const;

public:
	value_type i0() const { return m_i0; }
	value_type i1() const { return m_i1; }

private:
	value_type	m_i0;
	value_type	m_i1;
};

/* ////////////////////////////////////////////////////////////////////////// */

inline Fibonacci_sequence::Fibonacci_sequence()
{}

inline Fibonacci_sequence::const_iterator Fibonacci_sequence::begin() const
{
	return const_iterator(0, 1);
}

inline Fibonacci_sequence::const_iterator Fibonacci_sequence::end() const
{
	return const_iterator(0, 0);
}

/* ////////////////////////////////////////////////////////////////////////// */

inline Fibonacci_sequence::const_iterator::const_iterator(Fibonacci_sequence::value_type i0, Fibonacci_sequence::value_type i1)
	: m_i0(i0)
	, m_i1(i1)
{}

inline Fibonacci_sequence::const_iterator::class_type &Fibonacci_sequence::const_iterator::operator ++()
{
	STLSOFT_MESSAGE_ASSERT("Fibonacci sequence has exhausted limitations of integral type", m_i0 <= m_i1);

	value_type  res		=	m_i0 + m_i1;
				m_i0	=	m_i1;
				m_i1	=	res;

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
	return m_i0 == rhs.m_i0 && m_i1 == rhs.m_i1;
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
