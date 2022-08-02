
// Updated: 13th November 2005

#include <string>
//#include <vector>

#include <stlsoft/shared_ptr.hpp>

/* /////////////////////////////////////////////////////////////////////////////
 * Classes
 */

namespace stlsoft
{
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
														,	value_type
														,	void
														,	difference_type
														>		const_reverse_iterator;
#endif /* __STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT */
		typedef environment_map									class_type;

	private:
		friend class const_iterator;
		struct context
		{
		public:
			typedef stlsoft::shared_ptr<context>	ref_type;

		public:
			context();
			~context();

		public:
			char const	**base() const;
			size_t		size() const;

		private:
			char	**m_base;
			size_t	m_size;
		};

	public:
		static context::ref_type	make_context()
		{
			return context::ref_type();
		}

	public:
		environment_map()
		{}
		~environment_map()
		{}

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
			check_refresh_context_();

			return const_iterator(m_context->base(), m_context);
		}

		const_iterator	end() const
		{
			check_refresh_context_();

			return const_iterator(m_context->base() + m_context->size(), m_context);
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
			const_iterator(char const **p, context::ref_type context)
				: m_p(p)
				, m_context(context)
			{}
			const_iterator(class_type const &rhs)
				: m_p(rhs.m_p)
				, m_context(rhs.m_context)
			{}

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
				value_type	v;

				stlsoft::split(*m_p, '=', v.first, v.second);

				return v;
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
			char const			**m_p;
			context::ref_type	m_context;
		};

	private:
    private:
        static void putenv_(char const *name, char const *value)
        {
		    STLSOFT_MESSAGE_ASSERT("Name may not contain '='", NULL == ::strchr(name, '='));

            const size_t        cchName     =   stlsoft::c_str_len(name);
            const size_t        cchValue    =   stlsoft::c_str_len(value);
            auto_buffer<char>   buff(cchName + 1 + cchValue + 1);

            if(!buff.empty()) // This check worthwhile since implementation or ator may not support bad_alloc
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

	private:
		void check_refresh_context_() const
		{
			const_cast<class_type*>(this)->check_refresh_context_();
		}

		void check_refresh_context_()
		{
			if(1 == m_context.count())
			{
				m_context.close();
			}

			if(NULL == m_context.get())
			{
				m_context = context::ref_type(new context());
			}
		}

	private:
		context::ref_type	m_context;
	};

	environment_map::context::context()
		: m_size(find_end_(const_cast<char const **>(environ)) - environ)
	{
		char	**dest;
		char	**src;

		m_base	=	new char*[m_size + 1];

		try
		{
			{ for(src = environ, dest = m_base; NULL != *src; ++src, ++dest)
			{
				*dest = ::strdup(*src);
			}}
			*dest = NULL;
		}
		catch(...)
		{
			{ for(char **p = m_base; dest != p; ++p)
			{
				::free(*p);
			}}

			delete [] m_base;

			throw;
		}
	}

	environment_map::context::~context()
	{
		if(NULL != m_base)
		{
			{ for(char **p = m_base; NULL != *p; ++p)
			{
				::free(*p);
			}}

			delete [] m_base;
		}
	}

	char const **environment_map::context::base() const
	{
		return const_cast<char const**>(m_base);
	}

	size_t environment_map::context::size() const
	{
		return m_size;
	}

} // namespace stlsoft

/* ////////////////////////////////////////////////////////////////////////// */

