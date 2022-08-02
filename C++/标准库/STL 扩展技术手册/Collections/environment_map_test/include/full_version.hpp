
// Updated: 23rd November 2005

#include <list>
#include <map>
#include <string>

#include <stlsoft/shared_ptr.hpp>

/* /////////////////////////////////////////////////////////////////////////////
 * Classes
 */

#define MUTATIONS_UPDATE_SNAPSHOT


namespace stlsoft
{
    // Full version
    static char const   **find_end_(char const **p)
    {
        for(; NULL != *p; ++p)
        {}

        return p;
    }

    class environment_map
    {
    public:
        typedef std::string                                     string_type;
        typedef string_type                                     first_type;
        typedef string_type                                     second_type;
        typedef std::pair<  const first_type
                        ,   second_type
                        >                                       value_type;
        typedef ss_ptrdiff_t                                    difference_type;
        typedef const value_type                                const_reference;
        class                                                   const_iterator;
#if defined(__STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT)
        typedef const_reverse_bidirectional_iterator_base<  const_iterator
                                                        ,   value_type
                                                        ,   value_type
                                                        ,   void
                                                        ,   difference_type
                                                        >       const_reverse_iterator;
#endif /* __STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT */
        typedef environment_map                                 class_type;

    private:
        friend class const_iterator;
        struct context
        {
        public:
            typedef std::list<value_type>               context_variables_type_;
            typedef context_variables_type_::iterator   iterator;
            typedef stlsoft::shared_ptr<context>        ref_type;
#ifdef MUTATIONS_UPDATE_SNAPSHOT
# if 0
            typedef std::map<	string_type
# else /* ? 0 */
            typedef std::map<	stlsoft::string_view
# endif /* 0 */
							,	iterator
							>							variable_lookup_type_;
#endif /* MUTATIONS_UPDATE_SNAPSHOT */

        public:
            context();

        public:
#ifdef MUTATIONS_UPDATE_SNAPSHOT
            void erase(char const   *name);
            void erase(iterator     it);

            void insert(char const  *name
                    ,   char const  *value);
#endif /* MUTATIONS_UPDATE_SNAPSHOT */

        public:
            iterator    begin();
            iterator    end();

        private:
            context_variables_type_ m_variables;
#ifdef MUTATIONS_UPDATE_SNAPSHOT
            variable_lookup_type_   m_lookup;
#endif /* MUTATIONS_UPDATE_SNAPSHOT */
        };

    public:
        static context::ref_type    make_context()
        {
            return context::ref_type();
        }

    public:
        string_type operator [](char const *name) const
        {
            char const  *value  =   ::getenv(name);

            if(NULL == value)
            {
                throw stlsoft_ns_qual_std(out_of_range)("variable does not exist");
            }

            return value;
        }

    public:
        void refresh()
        {
            m_context.close();
        }

    public:
		/// \note THis is not strongly exception safe
        void insert(char const *name, char const *value)
        {
            STLSOFT_ASSERT(NULL != value);

            putenv_(name, value);

#ifdef MUTATIONS_UPDATE_SNAPSHOT
            // TODO: Determine whether or not this needs to be done after the putenv_()

            if(m_context.count() > 1)
            {
                m_context->insert(name, value);
            }
#endif /* MUTATIONS_UPDATE_SNAPSHOT */

        }
        void erase(char const *name)
        {
#ifdef MUTATIONS_UPDATE_SNAPSHOT
            // TODO: Determine whether or not this needs to be done after the putenv_()

            if(m_context.count() > 1)
            {
                m_context->erase(name);
            }
#endif /* MUTATIONS_UPDATE_SNAPSHOT */

            putenv_(name, NULL);
        }

#ifdef MUTATIONS_UPDATE_SNAPSHOT
//		void erase(const_iterator it)
//		{
//			STLSOFT_MESSAGE_ASSERT("No context assigned, so erase() is inappropriate", NULL != m_context.get());
//
//			putenv_((*it).first.c_str(), NULL);
//
//			m_context->erase(it.m_it);
//		}
#endif /* MUTATIONS_UPDATE_SNAPSHOT */

    public:
        const_iterator  begin() const
        {
            check_refresh_context_();

            context::ref_type   context =   m_context;  // Avoid a const_cast

            return const_iterator(context->begin(), m_context);
        }

        const_iterator  end() const
        {
            check_refresh_context_();

            context::ref_type   context =   m_context;  // Avoid a const_cast

            return const_iterator(context->end(), m_context);
        }

#if defined(__STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT)
        const_reverse_iterator  rbegin() const
        {
            return const_reverse_iterator(end());
        }
        const_reverse_iterator  rend() const
        {
            return const_reverse_iterator(begin());
        }
#endif /* __STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT */

    public:
        class const_iterator
            : public stlsoft_ns_qual(iterator_base)<stlsoft_ns_qual_std(bidirectional_iterator_tag)
                                                ,   value_type
                                                ,   ss_ptrdiff_t
                                                ,   void
                                                ,   const value_type
                                                >
        {
            friend class environment_map;
        public:
            typedef const_iterator  class_type;

        public:
            const_iterator()
                : m_it()
            {}
            const_iterator(context::iterator it, context::ref_type context)
                : m_it(it)
                , m_context(context)
            {}
            const_iterator(class_type const &rhs)
                : m_it(rhs.m_it)
                , m_context(rhs.m_context)
            {}

        public:
            class_type &operator ++()
            {
                ++m_it;

                return *this;
            }

            class_type operator ++(int)
            {
                class_type  r(*this);

                operator ++();

                return r;
            }

            const_reference operator *() const
            {
                return *m_it;
            }

        public:
            class_type &operator --()
            {
                --m_it;

                return *this;
            }

            class_type operator --(int)
            {
                class_type  r(*this);

                operator --();

                return r;
            }

        public:
            bool equal(class_type const &rhs) const
            {
                return m_it == rhs.m_it;
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
            context::iterator   m_it;
            context::ref_type   m_context;
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

                if(0 != ::putenv(buff.data()))
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
        context::ref_type   m_context;
    };

    environment_map::context::context()
    {
        first_type  name;
        second_type value;

        { for(char **p = environ; NULL != *p; ++p)
        {
            stlsoft::split(*p, '=', name, value);

#ifdef MUTATIONS_UPDATE_SNAPSHOT
            iterator    it  =   m_variables.insert(m_variables.end(), value_type(name, value));

            try
            {
#if 0
                m_lookup[name] = it;
#else /* ? 0 */
                m_lookup[stlsoft::string_view((*it).second.data(), (*it).second.size())] = it;
#endif /* 0 */
            }
            catch(...)
            {
                m_variables.erase(it);

                throw;
            }
#else /* ? MUTATIONS_UPDATE_SNAPSHOT */
            m_variables.push_back(value_type(name, value));
#endif /* MUTATIONS_UPDATE_SNAPSHOT */
        }}
    }

    environment_map::context::iterator environment_map::context::begin()
    {
        return m_variables.begin();
    }

    environment_map::context::iterator environment_map::context::end()
    {
        return m_variables.end();
    }

#ifdef MUTATIONS_UPDATE_SNAPSHOT
    void environment_map::context::erase(char const *name)
    {
        variable_lookup_type_::iterator it  =   m_lookup.find(name);

        if(m_lookup.end() != it)
        {
            m_variables.erase((*it).second);
            m_lookup.erase(it);
        }
    }

    void environment_map::context::erase(environment_map::context::iterator it)
    {
        m_variables.erase(it);
    }

    void environment_map::context::insert(char const *name, char const *value)
    {
        variable_lookup_type_::iterator it  =   m_lookup.find(name);

        if(m_lookup.end() != it)
        {
            (*(*it).second).second = value;
        }
        else
        {
            iterator    it2 =   m_variables.insert(m_variables.end(), value_type(name, value));

            try
            {
                m_lookup[name] = it2;
            }
            catch(...)
            {
                m_variables.erase(it2);

                throw;
            }
        }
    }
#endif /* MUTATIONS_UPDATE_SNAPSHOT */

} // namespace stlsoft

/* ////////////////////////////////////////////////////////////////////////// */

