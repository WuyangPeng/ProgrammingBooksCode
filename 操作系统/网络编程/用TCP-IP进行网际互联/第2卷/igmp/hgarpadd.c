/* hgarpadd.c - hgarpadd */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <igmp.h>

/*------------------------------------------------------------------------
 *  hgarpadd  -  add an ARP table entry for a multicast address
 *------------------------------------------------------------------------
 */
int
hgarpadd(unsigned ifnum, IPaddr ipa)
{
	struct netif	*pni = &nif[ifnum];
	struct arpentry	*pae, *arpalloc();
	int		ifdev = nif[ifnum].ni_dev;
	STATWORD	ps;

	disable(ps);
	pae = arpalloc();
	if (pae == 0) {
		restore(ps);
		return SYSERR;
	}
	pae->ae_hwtype = pni->ni_hwtype;
	pae->ae_prtype = EPT_IP;
	pae->ae_pni = pni;
	pae->ae_hwlen = pni->ni_hwa.ha_len;
	pae->ae_prlen = IP_ALEN;
	pae->ae_queue = EMPTY;
	memcpy(pae->ae_pra, &ipa, IP_ALEN);
	if (pni->ni_mcast)
		(pni->ni_mcast)(NI_MADD, ifdev, pae->ae_hwa, ipa);
	else
		memcpy(pae->ae_hwa, pni->ni_hwb.ha_addr, pae->ae_hwlen);
	pae->ae_ttl = ARP_INF;
	pae->ae_state = AS_RESOLVED;
	restore(ps);
	return OK;
}
