
// Updated: 20th November 2005

#include <string>

/* /////////////////////////////////////////////////////////////////////////////
 * Classes
 */

namespace stlsoft
{
	// Enumeration Version 2 uses
	//
	//
	// .

	class environment_map
	{
	public:
		typedef std::string 									string_type;
#if 0
		typedef stlsoft::string_view							first_type;
		typedef stlsoft::string_view							second_type;
#else /* ? 0 */
		typedef string_type 									first_type;
		typedef string_type 									second_type;
#endif /* 0 */
		typedef std::pair<	const first_type
						,	const second_type
						>										value_type;
		typedef ss_ptrdiff_t									difference_type;
		class													const_iterator;
		typedef const value_type								const_reference;
#if defined(__STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT)
		typedef const_reverse_bidirectional_iterator_base<	const_iterator
														,	value_type
														,	const value_type
														,	void
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
												,	void
												,	value_type
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
			}

		public:
			class_type &operator ++()
			{
				++m_p;

				return *this;
			}

			class_type operator ++(int)
			{
				class_type	r(*this);

				operator ++();

				return r;
			}

			value_type operator *() const
			{
#if 0
				value_type	v;

				stlsoft::split(*m_p, '=', v.first, v.second);

				return v;
#else /* ? 0 */
				first_type	first;
				second_type	second;

				stlsoft::split(*m_p, '=', first, second);

				return value_type(first, second);
#endif /* 0 */
			}

		public:
			class_type &operator --()
			{
				--m_p;

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

			const size_t		cchName 	=	stlsoft::c_str_len(name);
			const size_t		cchValue	=	stlsoft::c_str_len(value);
			auto_buffer<char>	buff(cchName + 1 + cchValue + 1);

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

