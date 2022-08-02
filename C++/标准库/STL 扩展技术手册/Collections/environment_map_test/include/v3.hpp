
#include <string>

/* /////////////////////////////////////////////////////////////////////////////
 * Classes
 */

namespace stlsoft
{

	// v3
	class environment_map
	{
	public:
		typedef std::string		string_type;

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

