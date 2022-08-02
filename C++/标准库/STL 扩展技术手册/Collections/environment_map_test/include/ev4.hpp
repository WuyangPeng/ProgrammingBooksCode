
// Updated: 22nd November 2005

#include <string>
#include <vector>

#include <stlsoft/shared_ptr.hpp>

/* /////////////////////////////////////////////////////////////////////////////
 * Classes
 */

namespace stlsoft
{
	// Full version
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
						>										first_second_type;
		typedef first_second_type								value_type;
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
			struct									variable
			{
			public:
				variable();

				void assign(char const *p);

			public:
				string_type			data;
				first_second_type	nameValue;
			};
			typedef variable						value_type;

		public:
			context();

		public:
			void erase(variable const *it);

		public:
			variable const	*base() const;
			size_t			size() const;

		private:
			std::vector<variable>	m_variables;
		};

	public:
		static context::ref_type	make_context()
		{
			return context::ref_type();
		}

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
		void refresh()
		{
			m_context.close();
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

			return const_iterator(NULL, m_context);
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
			friend class environment_map;
		public:
			typedef const_iterator	class_type;

		public:
			const_iterator()
				: m_p(NULL)
			{}
			const_iterator(context::variable const *p, context::ref_type context)
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

			value_type const &operator *() const
			{
				return m_p->nameValue;
			}

		public:
			class_type &operator --()
			{
				if(NULL == m_p)
				{
					m_p = m_context->base() + m_context->size();
				}

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
				context::variable const	*p1		=	m_p;
				context::variable const	*p2		=	rhs.m_p;
				context::variable const *base	=	m_context->base();

				if( NULL == p1 ||
					NULL == base)
				{
					p1 = base + m_context->size();
				}
				if( NULL == p2 ||
					NULL == base)
				{
					p2 = base + m_context->size();
				}

				return p1 == p2;
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
			context::variable const	*m_p;
			context::ref_type		m_context;
		};

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
				STLSOFT_ASSERT(::strlen(buff.data()) == buff.size() - 1);

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
		: m_variables(find_end_(const_cast<char const **>(environ)) - environ)
	{
		{ for(size_t i = 0; NULL != environ[i] && i != m_variables.size(); ++i)
		{
			m_variables[i].assign(environ[i]);
		}}
	}

	environment_map::context::variable const *environment_map::context::base() const
	{
		return &m_variables[0];
	}

	size_t environment_map::context::size() const
	{
		return m_variables.size();
	}

	environment_map::context::variable::variable()
		: data()
		, nameValue()
	{}

	void environment_map::context::variable::assign(char const *p)
	{
		stlsoft::split(data = p, '=', nameValue.first, nameValue.second);
	}

	void environment_map::context::erase(environment_map::context::variable const *p)
	{
		m_variables.erase(const_cast<environment_map::context::variable*>(p));
	}

} // namespace stlsoft

/* ////////////////////////////////////////////////////////////////////////// */

