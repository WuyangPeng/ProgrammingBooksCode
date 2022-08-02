/*  $NetBSD: bswap.c,v 1.1 1997/10/09 13:19:32 bouyer Exp $    */

/*
 * Written by Manuel Bouyer <bouyer@netbsd.org>.
 * Public domain.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char *rcsid = "$NetBSD: bswap.c,v 1.1 1997/10/09 13:19:32 bouyer Exp $";
#endif

#include <sys/types.h>

#undef bswap64

#ifndef bswap16
u_int16_t
bswap16(x)
	u_int16_t x;
{
	return ((x << 8) & 0xff00) | ((x >> 8) & 0x00ff);
}
#endif

#ifndef bswap32
u_int32_t
bswap32(x)
	u_int32_t x;
{
	return	((x << 24) & 0xff000000 ) |
		((x <<  8) & 0x00ff0000 ) |
		((x >>  8) & 0x0000ff00 ) |
		((x >> 24) & 0x000000ff );
}
#endif

u_int64_t
bswap64(x)
	u_int64_t x;
{
	u_int32_t *p = (u_int32_t*)&x;
	u_int32_t t;
	t = bswap32(p[0]);
	p[0] = bswap32(p[1]);
	p[1] = t;
	return x;
}
