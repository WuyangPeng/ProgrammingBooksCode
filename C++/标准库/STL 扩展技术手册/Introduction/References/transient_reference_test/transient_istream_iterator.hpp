


#include <stlsoft/iterator.hpp>

#include <stlsoft/shared_ptr.hpp>

namespace stlsoft
{


template<	ss_typename_param_k	T
		,	ss_typename_param_k C	=	char
		,	ss_typename_param_k TR	=	std::char_traits<C>
		,	ss_typename_param_k	D	=	ptrdiff_t
		>
class transient_istream_iterator
	: public iterator_base<std::input_iterator_tag, T, D, T const*, T const&>
{
public:
	typedef T										value_type;
	typedef C										char_type;
	typedef TR										traits_type;
	typedef std::basic_istream<C, TR>				istream_type;
	typedef transient_istream_iterator<T, C, TR>	class_type;

// Construction
public:
	transient_istream_iterator()
		: m_pstm(0)
		, m_value(new value_type())
	{}
	transient_istream_iterator(istream_type& _I)
		: m_pstm(&_I)
		, m_value(new value_type())
	{
		readValue();
	}

public:
	class_type &operator++()
	{
		readValue();

		return (*this);
	}
	class_type operator++(int)
	{
		class_type	t(*this);

		operator ++();

		return t;
	}
	value_type const &operator*() const
	{
		return *m_value;
	}
#if 0
	value_type const *operator->() const
	{
		return &*(*this);
	}
#endif /* 0 */

public:
	bool equal(class_type const &rhs) const
	{
		return m_pstm == rhs.m_pstm;
	}

// Implementation
private:
	void readValue()
	{
		if( NULL != m_pstm && 
			!(*m_pstm >> *m_value))
		{
			m_pstm = NULL;
		}
		else
		{
			m_value = value_ptr_type(new value_type(*m_value));
		}
	}

// Members
private:
	typedef shared_ptr<value_type>	value_ptr_type;

	istream_type 	*m_pstm;
	value_ptr_type	m_value;
};

template<	ss_typename_param_k	T
		,	ss_typename_param_k C
		,	ss_typename_param_k TR
		,	ss_typename_param_k	D
		>
inline bool operator==(transient_istream_iterator<T, C, TR, D> const &lhs, transient_istream_iterator<T, C, TR, D> const &rhs)
{
	return lhs.equal(rhs);
}

template<	ss_typename_param_k	T
		,	ss_typename_param_k C
		,	ss_typename_param_k TR
		,	ss_typename_param_k	D
		>
inline bool operator!=(transient_istream_iterator<T, C, TR, D> const &lhs, transient_istream_iterator<T, C, TR, D> const &rhs)
{
	return !lhs.equal(rhs);
}

} // namespace stlsoft
