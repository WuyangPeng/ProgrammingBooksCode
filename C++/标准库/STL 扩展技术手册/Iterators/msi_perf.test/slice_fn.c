

#include "slice.h"


size_t sum_slice(size_t n, struct slice_t const* slice)
{
	return n + slice->len;
}

