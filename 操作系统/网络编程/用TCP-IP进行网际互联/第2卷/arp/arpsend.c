/* arpsend.c - arpsend */

#include <conf.h>
#include <kernel.h>
#include <network.h>

/*------------------------------------------------------------------------
 * arpsend - broadcast an ARP request
 *	N.B. Assumes interrupts disabled
 *------------------------------------------------------------------------
 */
int
arpsend(struct arpentry *pae)
{
	struct	netif	*pni = pae->ae_pni;
	struct	ep	*pep;
	struct	arp	*parp;
	int		arplen;

	pep = (struct ep *) getbuf(Net.netpool);
	if ((int)pep == SYSERR)
		return SYSERR;
	memcpy(pep->ep_dst, pni->ni_hwb.ha_addr, pae->ae_hwlen);
	pep->ep_type = EPT_ARP;
	pep->ep_order = EPO_NET;
	parp = (struct arp *) pep->ep_data;
	parp->ar_hwtype = hs2net(pae->ae_hwtype);
	parp->ar_prtype = hs2net(pae->ae_prtype);
	parp->ar_hwlen = pae->ae_hwlen;
	parp->ar_prlen = pae->ae_prlen;
	parp->ar_op = hs2net(AR_REQUEST);
	memcpy(SHA(parp), pni->ni_hwa.ha_addr, pae->ae_hwlen);
	memcpy(SPA(parp), &pni->ni_ip, pae->ae_prlen);
	memset(THA(parp), 0, pae->ae_hwlen);
	memcpy(TPA(parp), pae->ae_pra, pae->ae_prlen);
	arplen = ARP_HLEN + 2*(parp->ar_hwlen + parp->ar_prlen);
	write(pni->ni_dev, pep, EP_HLEN+arplen);
	return OK;
}
