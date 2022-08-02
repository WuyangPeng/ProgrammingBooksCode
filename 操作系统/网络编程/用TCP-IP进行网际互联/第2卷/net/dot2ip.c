/* dot2ip.c - dot2ip */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  dot2ip - convert a dotted decimal string into an IP address
 *------------------------------------------------------------------------
 */
IPaddr
dot2ip(const char *pdot)
{
	IPaddr		ip;
	unsigned char	*p;
	int		i;

	ip = 0;
	p = (unsigned char *)&ip;
	for (i=0; pdot && *pdot && i<IP_ALEN; ++i) {
		*p++ = atoi(pdot);
		if (pdot = index(pdot, '.'))
			++pdot;
		else
			break;
	}
	return ip;
}
