/* memcmp.c - memcmp */

#include <kernel.h>

/*------------------------------------------------------------------------
 *  memcpy  -  return the difference of the first unequal bytes
 *------------------------------------------------------------------------
 */
int
memcmp(const void *b1, const void *b2, unsigned len)
{
	register int	rv;

	while (len-- > 0)
		if (rv = *(unsigned char *)b1++ - *(unsigned char *)b2++)
			break;
	return rv;
}
