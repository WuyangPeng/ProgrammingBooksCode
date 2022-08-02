/* snm_findn.c - snm_findnext, snmcmp */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	SNMP
#include <snmp.h>

/*------------------------------------------------------------------------
 * snm_findnext - for given iface, find next resolved arp entry
 *------------------------------------------------------------------------
 */
int
snm_findnext(int entry, int iface)
{
	int	i, next;

	next = -1;
	for (i = 0; i < ARP_TSIZE; ++i) {
		struct arpentry	*pae = &arptable[i];

		if (pae->ae_state == AS_FREE ||
		    pae->ae_pni != &nif[iface] ||
		    (entry >= 0 && snmcmp(pae, &arptable[entry]) <= 0))
			continue;
		if (next < 0 || snmcmp(pae, &arptable[next]) < 0)
			next = i;
	}
	return next;
}

/*------------------------------------------------------------------------
 * snmcmp - compare two ARP table entries in SNMP lexicographic order
 *------------------------------------------------------------------------
 */
int
snmcmp(struct arpentry *pae1, struct arpentry *pae2)
{
	int	rv;

	if ((rv = (pae1->ae_prlen - pae2->ae_prlen)))
		return rv;
	return memcmp(pae1->ae_pra, pae2->ae_pra, pae1->ae_prlen);
}
#endif	/* SNMP */
