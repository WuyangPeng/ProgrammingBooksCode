
#include <stddef.h>

struct slice_t
{
	size_t		len;
	char const	*ptr;
};

#ifdef __cplusplus
extern "C" size_t sum_slice(size_t n, slice_t const& slice);
#else /* ? __cplusplus */
extern size_t sum_slice(size_t n, struct slice_t const* slice);
#endif /* __cplusplus */
