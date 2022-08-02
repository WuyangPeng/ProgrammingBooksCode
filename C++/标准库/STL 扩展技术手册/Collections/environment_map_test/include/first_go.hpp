
/* /////////////////////////////////////////////////////////////////////////////
 * Classes
 */

namespace stlsoft
{

#if 1
	template<	typename C
			,	typename A = std::allocator<C>
			>
#endif /* 0 */
	class basic_environment_map
	{
	public:
		// TODO: Need to define these here so can access them in the const_iterator
		// base class list, which are outside the const_iterator class defn
		//
		// XSTL: Get this in the chapter!!
		typedef	stlsoft::string_view	key_type;
		typedef	stlsoft::string_view	mapped_type;
		typedef std::pair<	key_type
						,	mapped_type
						>				value_type;
		typedef ss_ptrdiff_t			difference_type;


	public:
		class							const_iterator;
#if defined(__STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT)
		typedef const_reverse_bidirectional_iterator_base<	const_iterator
														,	value_type
														,	value_type const&
														,	value_type const*
														,	difference_type
														>		const_reverse_iterator;
#endif /* __STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT */

	public:
		basic_environment_map()
		{}

	public:
		C const	*operator [](C const *name) const
		{
			C const	*value	=	::getenv(name);

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

                if(0 != _putenv(buff.data()))
                {
                    throw std::runtime_error("Cannot set environment variable");
                }
            }
        }

	public:
		class const_iterator
	        : public stlsoft_ns_qual(iterator_base)<	stlsoft_ns_qual_std(random_access_iterator_tag)
													,	value_type
													,	ss_ptrdiff_t
													,	value_type const*
													,	value_type const&>
		{
		public:
			typedef	stlsoft::string_view	key_type;
			typedef	stlsoft::string_view	mapped_type;
			typedef std::pair<	key_type
							,	mapped_type
							>				value_type;
			typedef const_iterator			class_type;


		public:
			const_iterator()
				: m_p(NULL)
				, m_current()
			{}
			const_iterator(C const **p)
				: m_p(p)
				, m_current()
			{}

		public:
			const_iterator &operator ++()
			{
				stlsoft_assert(NULL != *m_p);

				++m_p;

				stlsoft::split(*m_p, '=', m_current.first, m_current.second);

				return *this;
			}
			value_type const &operator *() const
			{
				return m_current;
			}

        // Bidirectional iterator operations

        /// Pre-decrement operator
        class_type &operator --()
        {
            --m_p;

			stlsoft::split(*m_p, '=', m_current.first, m_current.second);

            return *this;
        }

        /// Post-decrement operator
        class_type operator --(int)
        {
            class_type  ret(*this);

            operator --();

            return ret;
        }

        // Random access operations

        class_type &operator +=(difference_type index)
        {
            m_p += index;

            return *this;
        }

        class_type &operator -=(difference_type index)
        {
            m_p -= index;

            return *this;
        }

#if 0
        value_type operator [](difference_type index) const
        {
            return m_p;
        }
#endif /* 0 */

        difference_type distance(class_type const &rhs) const
        {
            return m_p - rhs.m_p;
        }


		public:
			bool equal(const_iterator const &rhs) const
			{
				return m_p == rhs.m_p;
			}

		private:
			C const		**m_p;
			value_type	m_current;
		};

	public:
		const_iterator			begin() const;
		const_iterator			end() const;
#if defined(__STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT)
		const_reverse_iterator	rbegin() const;
		const_reverse_iterator	rend() const;
#endif /* __STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT */
	
	private:
		static C const	**find_end_(C **p)
		{
			for(; NULL != *p; ++p)
			{}

			return const_cast<C const**>(p);
		}
	};

#if 1
	typedef basic_environment_map<char>	environment_map;
# define	C_A							<C, A>
#else /* ? 0 */
	typedef basic_environment_map		environment_map;
# define	C_A
# undef		ss_typename_type_k
# define	ss_typename_type_k
#endif /* 0 */

//#define _environ	environ



#if 1
	template<	typename C
			,	typename A
			>
#endif /* 0 */
	inline ss_typename_type_k basic_environment_map C_A::const_iterator basic_environment_map C_A::begin() const
	{
		return const_iterator(const_cast<C const**>(_environ));
	}

#if 1
	template<	typename C
			,	typename A
			>
#endif /* 0 */
	inline ss_typename_type_k basic_environment_map C_A::const_iterator basic_environment_map C_A::end() const
	{
		return const_iterator(find_end_(_environ));
	}

#if defined(__STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT)
	template<	typename C
			,	typename A
			>
	inline ss_typename_type_k basic_environment_map C_A::const_reverse_iterator	basic_environment_map C_A::rbegin() const
	{
		return const_reverse_iterator(end());
	}
	template<	typename C
			,	typename A
			>
	inline ss_typename_type_k basic_environment_map C_A::const_reverse_iterator	basic_environment_map C_A::rend() const
	{
		return const_reverse_iterator(begin());
	}
#endif /* __STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT */

#if 0
#if 1
	template<	typename C
			,	typename A
			>
#endif /* 0 */
	inline basic_environment_map C_A::const_iterator::const_iterator()
		: m_p(NULL)
		, m_current()
	{}

#if 1
	template<	typename C
			,	typename A
			>
#endif /* 0 */
	inline basic_environment_map C_A::const_iterator::const_iterator(C const **p)
		: m_p(p)
		, m_current()
	{}
#endif /* 0 */

#if 0
#if 1
	template<	typename C
			,	typename A
			>
#endif /* 0 */
	inline ss_typename_type_k basic_environment_map C_A::const_iterator &basic_environment_map C_A::const_iterator::operator ++()
	{
		stlsoft_assert(NULL != *m_p);

		++m_p;

		stlsoft::split(*m_p, '=', m_current.first, m_current.second);

		return *this;
	}
#endif /* 0 */

#if 0
#if 1
	template<	typename C
			,	typename A
			>
#endif /* 0 */
	inline ss_typename_type_k basic_environment_map C_A::const_iterator::value_type const &basic_environment_map C_A::const_iterator::operator *() const
	{
		return m_current;
	}
#endif /* 0 */


#if 0
#if 1
	template<	typename C
			,	typename A
			>
#endif /* 0 */
	inline bool basic_environment_map C_A::const_iterator::equal(ss_typename_type_k basic_environment_map C_A::const_iterator const &rhs) const
	{
		return m_p == rhs.m_p;
	}
#endif /* 1 */

#if 1
	template<	typename C
			,	typename A
			>
#endif /* 0 */
	inline bool operator ==(ss_typename_type_k basic_environment_map C_A::const_iterator const	&lhs
						,	ss_typename_type_k basic_environment_map C_A::const_iterator const	&rhs)
	{
		return lhs.equal(rhs);
	}
#if 1
	template<	typename C
			,	typename A
			>
#endif /* 0 */
	inline bool operator !=(ss_typename_type_k basic_environment_map C_A::const_iterator const	&lhs
						,	ss_typename_type_k basic_environment_map C_A::const_iterator const	&rhs)
	{
		return !lhs.equal(rhs);
	}

} // namespace stlsoft

/* ////////////////////////////////////////////////////////////////////////// */

