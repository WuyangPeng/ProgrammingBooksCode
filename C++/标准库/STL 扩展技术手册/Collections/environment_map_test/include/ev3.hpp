
// Updated: 22nd November 2005

#include <string>
#include <vector>

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
		typedef string_type 									first_type;
		typedef string_type 									second_type;
		typedef std::pair<	first_type
						,	second_type
						>										value_type;
		typedef ss_ptrdiff_t									difference_type;
	private:
		typedef std::vector<value_type> 						variables_type_;
	public:
		typedef variables_type_::const_iterator 				const_iterator;
#if defined(__STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT)
		typedef variables_type_::const_reverse_iterator 		const_reverse_iterator;
#endif /* __STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT */
		typedef variables_type_::const_reference				const_reference;

	public:
		environment_map()
		{
			char const	**p =	const_cast<char const**>(environ);

			for(; NULL != *p; ++p)
			{
				first_type	name;
				second_type value;

				stlsoft::split(*p, '=', name, value);

				m_variables.push_back(value_type(name, value));
			}
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
			return m_variables.begin();
		}

		const_iterator	end() const
		{
			return m_variables.end();
		}

#if defined(__STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT)
		const_reverse_iterator	rbegin() const
		{
			return m_variables.rbegin();
		}
		const_reverse_iterator	rend() const
		{
			return m_variables.rend();
		}
#endif /* __STLSOFT_CF_BIDIRECTIONAL_ITERATOR_SUPPORT */

		bool	empty() const
		{
			return m_variables.empty();
		}

		size_t	size() const
		{
			return m_variables.size();
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

	private:
		variables_type_	m_variables;
	};

} // namespace stlsoft

/* ////////////////////////////////////////////////////////////////////////// */

