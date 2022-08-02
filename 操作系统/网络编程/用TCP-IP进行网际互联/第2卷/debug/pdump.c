/* pdump.c - pdump */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 * pdump - pretty-print an Ethernet packet on the console
 *------------------------------------------------------------------------
 */
int pdump(pep)
struct ep	*pep;
{
	int		i;
	unsigned short	type;

	if (pep->ep_order & EPO_NET)
		type = pep->ep_type;
	else
		type = net2hs(pep->ep_type);
	kprintf("KERN: pep %X ifn %d nexthop %X len %d order %X\n", pep,
		pep->ep_ifn, pep->ep_nexthop, pep->ep_len, pep->ep_order);
	kprintf("ETHER: dst %02x", pep->ep_dst[0]);
	for (i=1; i<EP_ALEN; ++i)
		kprintf(":%02x", pep->ep_dst[i]);
	kprintf(" src %02x", pep->ep_src[0]);
	for (i=1; i<EP_ALEN; ++i)
		kprintf(":%02x", pep->ep_src[i]);
	kprintf("\nETHER: type %x\n", type);

	switch (type) {
	case EPT_ARP:
	case EPT_RARP:
		return arpdump(pep->ep_data, pep->ep_order);
	case EPT_IP:
		return ipdump(pep->ep_data, pep->ep_order);
	default:
		hexdump(pep->ep_data, pep->ep_len);
		break;
	}
}
