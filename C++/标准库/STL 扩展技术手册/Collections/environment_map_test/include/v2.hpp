
#include <string>

/* /////////////////////////////////////////////////////////////////////////////
 * Classes
 */

namespace stlsoft
{

	// v2
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
	};

} // namespace stlsoft

/* ////////////////////////////////////////////////////////////////////////// */

