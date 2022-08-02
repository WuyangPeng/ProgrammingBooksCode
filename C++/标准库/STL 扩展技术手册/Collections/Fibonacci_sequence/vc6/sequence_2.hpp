

class Fibonacci_sequence
{
public:
#if 1
	typedef stlsoft::uint64_t	value_type;
#else /* ? 0 */
	typedef stlsoft::uint32_t	value_type;
//	typedef unsigned			value_type;
#endif /* 0 */
	class						const_iterator;

public:
	Fibonacci_sequence();
	~Fibonacci_sequence()
	{
#ifdef __STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT
		using stlsoft::is_same_type;
		using stlsoft::sign_traits;
#endif /* __STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT */

		STLSOFT_STATIC_ASSERT(stlsoft::is_integral_type<value_type>::value);
#ifdef __STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT
		STLSOFT_STATIC_ASSERT((is_same_type<sign_traits<value_type>::type, sign_traits<value_type>::unsigned_type>::value));
#endif /* __STLSOFT_CF_TEMPLATE_PARTIAL_SPECIALISATION_SUPPORT */
	}

public:
	const_iterator	begin() const;
	const_iterator	end() const;
};

class Fibonacci_sequence::const_iterator
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
	value_type	res		=	m_i0 + m_i1;

#if 1
	STLSOFT_ASSERT(m_i0 <= res);

	if(res < m_i0)
	{
		throw std::length_error("Fibonacci sequence has exhausted limitations of integral type");
	}
#endif /* 0 */

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

