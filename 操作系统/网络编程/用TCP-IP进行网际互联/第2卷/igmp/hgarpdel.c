/* hgarpdel.c - hgarpdel */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <igmp.h>

struct arpentry *arpfind(u_char *, u_short, struct netif *);

/*------------------------------------------------------------------------
 *  hgarpdel  -  remove an ARP table entry for a multicast address
 *------------------------------------------------------------------------
 */
int
hgarpdel(unsigned ifnum, IPaddr ipa)
{
	struct netif	*pni = &nif[ifnum];
	int		ifdev = nif[ifnum].ni_dev;
	struct arpentry	*pae;
	STATWORD	ps;

	disable(ps);
	if (pae = arpfind((u_char *)&ipa, EPT_IP, pni))
		pae->ae_state = AS_FREE;
	if (pni->ni_mcast)
		(pni->ni_mcast)(NI_MDEL, ifdev, pae->ae_hwa, ipa);
	restore(ps);
	return OK;
}
