/* ip2dot.c - ip2dot */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  ip2dot - create the dotted decimal form of ip in pdot
 *------------------------------------------------------------------------
 */
char *
ip2dot(char *pdot, IPaddr ip)
{
	char	*pch = pdot;
	int	i;

	sprintf(pch, "%u", ((char *)&ip)[0] & 0xff);
	pch += strlen(pch);
	for (i=1; i<IP_ALEN; ++i) {
		sprintf(pch, ".%u", ((char *)&ip)[i] & 0xff);
		pch += strlen(pch);
	}
	*pch = NULL;
	return pdot;
}
