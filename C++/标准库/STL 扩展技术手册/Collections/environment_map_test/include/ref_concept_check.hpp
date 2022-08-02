


#include <stlsoft/meta.hpp>

namespace stlsoft
{

	struct permanent_reference_tag
	{}

	struct fixed_reference_tag
	{}

	struct invalidatable_reference_tag
	{}

	struct transient_reference_tag
	{}

	struct byvalue_reference_tag
	{}

	struct void_reference_tag
	{}

	// Container

	// Collection

	// Iterator

#if 0
	template <typename T>
	struct reference_traits
	{
		// if defined(const_reference)
		//
		//  if is_same_type<void, const_reference>
		//
		//   category is void_reference_tag
		//
		// else // !defined(const_reference)
		//
		//
		//


		typedef typename select_first_type_if<	
											,	
	};
#endif /* 0 */





} // namespace stlsoft
