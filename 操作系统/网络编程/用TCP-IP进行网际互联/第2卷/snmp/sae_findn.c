/* sae_findn.c - sae_findnext */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP

/*-----------------------------------------------------------------------
 * sae_findnext - find the next interface in the lexical ordering
 *-----------------------------------------------------------------------
 */
int
sae_findnext(int iface, int numifaces)
{
	int 	i, nextif;
	
	for (nextif = -1, i = 1; i <= numifaces; ++i) {
		if (iface >= 0 &&
		    memcmp(&nif[i].ni_ip,&nif[iface].ni_ip,IP_ALEN) <= 0)
			continue;
		if (nextif < 0 ||
		    memcmp(&nif[i].ni_ip,&nif[nextif].ni_ip,IP_ALEN) < 0)
			nextif = i;
	}
	return nextif;
}
#endif	/* SNMP */
