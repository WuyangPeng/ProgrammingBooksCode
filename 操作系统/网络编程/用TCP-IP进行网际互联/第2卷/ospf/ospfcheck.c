/* ospfcheck.c - ospfcheck */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ports.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  ospfcheck - check if a packet is a valid OSPF packet
 *------------------------------------------------------------------------
 */
int
ospfcheck(struct ep *pep)
{
	struct	ip	*pip = (struct ip *)pep->ep_data;
	struct	ospf	*po = (struct ospf *)((char *)pip + IP_HLEN(pip));
	struct	ospf_if	*pif = &ospf_if[pep->ep_ifn];

	if (pif->if_state == IFS_DOWN)
		return FALSE;
	if (po->ospf_version != OSPF_VERSION)
		return FALSE;
	if (net2hs(po->ospf_authtype) != pif->if_area->ar_authtype)
		return FALSE;
	if (pif->if_area->ar_authtype &&
	    memcmp(po->ospf_auth, pif->if_area->ar_auth, AUTHLEN))
		return FALSE;
	memset(po->ospf_auth, 0, AUTHLEN);
	if (cksum((WORD *)po, net2hs(po->ospf_len)))
		return FALSE;
	return TRUE;
}
