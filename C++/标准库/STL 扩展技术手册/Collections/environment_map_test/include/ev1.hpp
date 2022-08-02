
// Updated: 22nd November 2005

#include <string>

/* /////////////////////////////////////////////////////////////////////////////
 * Classes
 */

namespace stlsoft
{
	// Enumeration Version 1 uses straight access to the environ array:
	//
	//  - value_type is const char **. User is given "name=value" string, which is not very usable
	//  - begin() is environ, 
	//  - end() is environ + N, where NULL == *(environ + N)
	//
	// any change to the environ caused by putenv() (or whatever) will invalidate the
	// iterators.

	class environment_map
	{
	public:
		typedef std::string				string_type;

		typedef char const				*value_type;
		typedef value_type const		*const_iterator;
		typedef ss_ptrdiff_t			difference_type;

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
			return environ_();
		}

		const_iterator	end() const
		{
			return find_end_(environ_());
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

