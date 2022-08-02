/* lsa_send.c - lsa_send */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  lsa_send - send a link-state advertisement (immediately; not queued)
 *------------------------------------------------------------------------
 */
int
lsa_send(struct ospf_if *pif, IPaddr to, struct ep *pep)
{
	struct	ip	*pip = (struct ip *)pep->ep_data;
	struct	ospf	*po = (struct ospf *)pip->ip_data;

	memset(po->ospf_auth, 0, AUTHLEN);
	po->ospf_cksum = 0;
	po->ospf_cksum = cksum((WORD *)po, po->ospf_len);
	memcpy(po->ospf_auth, pif->if_area->ar_auth, AUTHLEN);
	pip->ip_src = ip_anyaddr;
	ipsend(to, pep, po->ospf_len, IPT_OSPF, IPP_INCTL, IP_TTL);
}
