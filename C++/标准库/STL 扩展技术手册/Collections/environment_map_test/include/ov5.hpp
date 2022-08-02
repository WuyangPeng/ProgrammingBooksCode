
// Updated: 19th November 2005

#include <string>

/* /////////////////////////////////////////////////////////////////////////////
 * Classes
 */

namespace stlsoft
{
	// Version 5 uses Transient Reference, and illustrates why iterators more
	// refined than Forward should not give out references to their internal
	// structures. The problem is that inside the dereference of a reverse
	// iterator a temporary instance of the iterator is returned, from which
	// the reference is returned. Thus, either a Bidirectional+ iterator should
	// return by value, or should return a reference to an external entity
	// (meaning that it must store a member reference, not a non-reference 
	// member).

	class environment_map
	{
	public:
		typedef stlsoft::string_view							first_type;
		typedef stlsoft::string_view							second_type;
		typedef std::string										string_type;
		typedef std::pair<	first_type
						,	second_type
						>										value_type;
		typedef ss_ptrdiff_t									difference_type;
		class													const_iterator;
#if defined(__STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT)
		typedef const_reverse_bidirectional_iterator_base<	const_iterator
														,	value_type
														,	value_type const&
														,	value_type const*
														,	difference_type
														>		const_reverse_iterator;
#endif /* __STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT */

	public:
		string_type operator [](char const *name) const
		{
			char const	*value	=	::getenv(name);

			if(NULL == value)
			{
		        throw stlsoft_ns_qual_std(out_of_range)("invalid key");
			}

			return value;
		}

    public:
        void insert(char const *name, char const *value)
        {
			STLSOFT_ASSERT(NULL != value);

			putenv_(name, value);
        }
        void erase(char const *name)
        {
            putenv_(name, NULL);
        }

	public:
		const_iterator	begin() const
		{
			return const_iterator(environ_());
		}

		const_iterator	end() const
		{
			return const_iterator(find_end_(environ_()));
		}

#if defined(__STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT)
		const_reverse_iterator	rbegin() const
		{
			return const_reverse_iterator(end());
		}
		const_reverse_iterator	rend() const
		{
			return const_reverse_iterator(begin());
		}
#endif /* __STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT */

	public:
		class const_iterator
	        : public stlsoft_ns_qual(iterator_base)<stlsoft_ns_qual_std(bidirectional_iterator_tag)
												,	value_type
												,	ss_ptrdiff_t
												,	value_type const*
												,	value_type const&
												>
		{
		public:
			typedef const_iterator	class_type;

		public:
			const_iterator()
				: m_p(NULL)
			{}
			const_iterator(char const **p)
				: m_p(p)
			{
				stlsoft::split(*m_p, '=', m_value.first, m_value.second);
			}

		public:
			class_type &operator ++()
			{
				++m_p;

				stlsoft::split(*m_p, '=', m_value.first, m_value.second);

				return *this;
			}

			class_type operator ++(int)
			{
				class_type	r(*this);

				operator ++();

				return r;
			}

			value_type const &operator *() const
			{
				return m_value;
			}

		public:
			class_type &operator --()
			{
				--m_p;

				stlsoft::split(*m_p, '=', m_value.first, m_value.second);

				return *this;
			}

			class_type operator --(int)
			{
				class_type	r(*this);

				operator --();

				return r;
			}

		public:
			bool equal(class_type const &rhs) const
			{
				return m_p == rhs.m_p;
			}
			bool operator ==(class_type const &rhs) const
			{
				return this->equal(rhs);
			}
			bool operator !=(class_type const &rhs) const
			{
				return !this->equal(rhs);
			}

		private:
			char const	**m_p;
			value_type	m_value;
		};

	private:
		static char const	**environ_()
		{
			return const_cast<char const**>(_environ);
		}

		static char const	**find_end_(char const **p)
		{
			for(; NULL != *p; ++p)
			{}

			return p;
		}

    private:
        static void putenv_(char const *name, char const *value)
        {
		    STLSOFT_ASSERT(NULL == ::strchr(name, '='));

            const size_t        cchName     =   stlsoft::c_str_len(name);
            const size_t        cchValue    =   stlsoft::c_str_len(value);
            auto_buffer<char>   buff(cchName + 1 + cchValue + 1);

            if(!buff.empty())
            {
                ::strncpy(&buff[0], name, cchName);
                buff[cchName] = '=';
                ::strncpy(&buff[cchName + 1], value, cchValue);
                buff[cchName + 1 + cchValue] = '\0';
				STLSOFT_ASSERT(::strlen(buff.data()) == buff.size() - 1);

                if(0 != _putenv(buff.data()))
                {
                    throw std::runtime_error("Cannot set environment variable");
                }
            }
        }
	};

} // namespace stlsoft

/* ////////////////////////////////////////////////////////////////////////// */

