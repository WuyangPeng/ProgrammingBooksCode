/* lsr_xmit.c - lsa_xmit */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  lsr_xmit - transmit pending Link State Request packets
 *------------------------------------------------------------------------
 */
int
lsr_xmit(struct ospf_if *pif, struct ospf_nb *pnb)
{
	struct	ep	*pephead, *pep;
	struct	ip	*pip;
	struct	ospf	*po;
	int		len;

	pephead = (struct ep *)headq(pnb->nb_lsrl);
	if (pephead == 0)
		return OK;
	pep = (struct ep *)getbuf(Net.netpool);
	if ((int)pep == SYSERR)
		return SYSERR;
	/* make a copy */
	pip = (struct ip *)pephead->ep_data;
	po = (struct ospf *)pip->ip_data;
	len = EP_HLEN + IPMHLEN + po->ospf_len;
	memcpy(pep, pephead, len);
	pip = (struct ip *)pep->ep_data;
	po = (struct ospf *)pip->ip_data;
	po->ospf_authtype = hs2net(pif->if_area->ar_authtype);
	memset(po->ospf_auth, 0, AUTHLEN);
	len = po->ospf_len;
	po->ospf_len = hs2net(po->ospf_len);
	pep->ep_order &= ~EPO_OSPF;
	po->ospf_cksum = 0;
	po->ospf_cksum = cksum((WORD *)po, len);
	memcpy(po->ospf_auth, pif->if_area->ar_auth, AUTHLEN);
	pip->ip_src = ip_anyaddr;
	ipsend(pnb->nb_ipa, pep, len, IPT_OSPF, IPP_INCTL, IP_TTL);
	pnb->nb_tlsr = pif->if_rintv;
	return OK;
}
