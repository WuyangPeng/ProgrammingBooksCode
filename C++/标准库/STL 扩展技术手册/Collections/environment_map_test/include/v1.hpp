
/* /////////////////////////////////////////////////////////////////////////////
 * Classes
 */

namespace stlsoft
{

	// v1
	class environment_map
	{
	public:
		char const	*operator [](char const *name) const
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

