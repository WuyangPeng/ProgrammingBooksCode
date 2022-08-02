
#include <iterator>

#define STLSOFT_TEMPLATE_SPECIALISATION	template <>

template<	typename C1
		,	typename C2
		>
struct min_iterator_category;

#define	STLSOFT_ITER_CAT_LIMITER_DEFINE_SPECIALISATION(c1, c2, cr)	\
																	\
	STLSOFT_TEMPLATE_SPECIALISATION									\
	struct min_iterator_category<c1, c2>							\
	{																\
		typedef cr		iterator_category;							\
	}

STLSOFT_ITER_CAT_LIMITER_DEFINE_SPECIALISATION(std::input_iterator_tag,         std::input_iterator_tag, std::input_iterator_tag);
STLSOFT_ITER_CAT_LIMITER_DEFINE_SPECIALISATION(std::forward_iterator_tag,       std::input_iterator_tag, std::input_iterator_tag);
STLSOFT_ITER_CAT_LIMITER_DEFINE_SPECIALISATION(std::bidirectional_iterator_tag, std::input_iterator_tag, std::input_iterator_tag);
STLSOFT_ITER_CAT_LIMITER_DEFINE_SPECIALISATION(std::random_access_iterator_tag, std::input_iterator_tag, std::input_iterator_tag);
STLSOFT_ITER_CAT_LIMITER_DEFINE_SPECIALISATION(std::input_iterator_tag,         std::forward_iterator_tag, std::input_iterator_tag);
STLSOFT_ITER_CAT_LIMITER_DEFINE_SPECIALISATION(std::forward_iterator_tag,       std::forward_iterator_tag, std::forward_iterator_tag);
STLSOFT_ITER_CAT_LIMITER_DEFINE_SPECIALISATION(std::bidirectional_iterator_tag, std::forward_iterator_tag, std::forward_iterator_tag);
STLSOFT_ITER_CAT_LIMITER_DEFINE_SPECIALISATION(std::random_access_iterator_tag, std::forward_iterator_tag, std::forward_iterator_tag);
STLSOFT_ITER_CAT_LIMITER_DEFINE_SPECIALISATION(std::input_iterator_tag,         std::bidirectional_iterator_tag, std::input_iterator_tag);
STLSOFT_ITER_CAT_LIMITER_DEFINE_SPECIALISATION(std::forward_iterator_tag,       std::bidirectional_iterator_tag, std::forward_iterator_tag);
STLSOFT_ITER_CAT_LIMITER_DEFINE_SPECIALISATION(std::bidirectional_iterator_tag, std::bidirectional_iterator_tag, std::bidirectional_iterator_tag);
STLSOFT_ITER_CAT_LIMITER_DEFINE_SPECIALISATION(std::random_access_iterator_tag, std::bidirectional_iterator_tag, std::bidirectional_iterator_tag);
STLSOFT_ITER_CAT_LIMITER_DEFINE_SPECIALISATION(std::input_iterator_tag,         std::random_access_iterator_tag, std::input_iterator_tag);
STLSOFT_ITER_CAT_LIMITER_DEFINE_SPECIALISATION(std::forward_iterator_tag,       std::random_access_iterator_tag, std::forward_iterator_tag);
STLSOFT_ITER_CAT_LIMITER_DEFINE_SPECIALISATION(std::bidirectional_iterator_tag, std::random_access_iterator_tag, std::bidirectional_iterator_tag);
STLSOFT_ITER_CAT_LIMITER_DEFINE_SPECIALISATION(std::random_access_iterator_tag, std::random_access_iterator_tag, std::random_access_iterator_tag);



#define STLSOFT_TEMPLATE_SPECIALISATION	template <>

template<	typename C1
		,	typename C2
		>
struct min_iterator_category;

#define	STLSOFT_ITER_CAT_LIMITER_DEFINE_SPECIALISATION(c1, c2, cr)																			STLSOFT_TEMPLATE_SPECIALISATION										struct min_iterator_category<c1, c2>								{																		typedef cr		iterator_category;								}

template <>
struct min_iterator_category<std::input_iterator_tag, std::input_iterator_tag>
{
	typedef std::input_iterator_tag iterator_category;
};
template <>
struct min_iterator_category<std::forward_iterator_tag, std::input_iterator_tag>
{
	typedef std::input_iterator_tag iterator_category;
};
template <>
struct min_iterator_category<std::bidirectional_iterator_tag, std::input_iterator_tag>
{
	typedef std::input_iterator_tag iterator_category;
};
template <>
struct min_iterator_category<std::random_access_iterator_tag, std::input_iterator_tag>
{
	typedef std::input_iterator_tag iterator_category;
};
template <>
struct min_iterator_category<std::input_iterator_tag, std::forward_iterator_tag>
{
	typedef std::input_iterator_tag iterator_category;
};
template <>
struct min_iterator_category<std::forward_iterator_tag, std::forward_iterator_tag>
{
	typedef std::forward_iterator_tag iterator_category;
};
template <>
struct min_iterator_category<std::bidirectional_iterator_tag, std::forward_iterator_tag>
{
	typedef std::forward_iterator_tag iterator_category;
};
template <>
struct min_iterator_category<std::random_access_iterator_tag, std::forward_iterator_tag>
{
	typedef std::forward_iterator_tag iterator_category;
};
template <>
struct min_iterator_category<std::input_iterator_tag, std::bidirectional_iterator_tag>
{
	typedef std::input_iterator_tag iterator_category;
};
template <>
struct min_iterator_category<std::forward_iterator_tag, std::bidirectional_iterator_tag>
{
	typedef std::forward_iterator_tag iterator_category;
};
template <>
struct min_iterator_category<std::bidirectional_iterator_tag, std::bidirectional_iterator_tag>
{
	typedef std::bidirectional_iterator_tag iterator_category;
};
template <>
struct min_iterator_category<std::random_access_iterator_tag, std::bidirectional_iterator_tag>
{
	typedef std::bidirectional_iterator_tag iterator_category;
};
template <>
struct min_iterator_category<std::input_iterator_tag, std::random_access_iterator_tag>
{
	typedef std::input_iterator_tag iterator_category;
};
template <>
struct min_iterator_category<std::forward_iterator_tag, std::random_access_iterator_tag>
{
	typedef std::forward_iterator_tag iterator_category;
};
template <>
struct min_iterator_category<std::bidirectional_iterator_tag, std::random_access_iterator_tag>
{
	typedef std::bidirectional_iterator_tag iterator_category;
};
template <>
struct min_iterator_category<std::random_access_iterator_tag, std::random_access_iterator_tag>
{
	typedef std::random_access_iterator_tag iterator_category;
};