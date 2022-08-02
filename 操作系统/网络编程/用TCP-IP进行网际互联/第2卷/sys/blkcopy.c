/* memcpy.c - memcpy */

#include <kernel.h>

/*------------------------------------------------------------------------
 *  memcpy  -  copy a block of memory form one location to another
 *------------------------------------------------------------------------
 */
memcpy(to, from, nbytes)
register char	*to;
register char	*from;
register int	nbytes;
{
	if (from > to) {
		while (--nbytes >= 0)
			*to++ = *from++;
	} else {
		to += nbytes-1;
		from += nbytes-1;
		while (--nbytes >= 0)
			*to-- = *from--;
	}
	return OK;
}
