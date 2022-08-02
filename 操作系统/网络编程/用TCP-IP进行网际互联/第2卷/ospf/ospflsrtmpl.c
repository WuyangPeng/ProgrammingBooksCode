/* ospflsrtmpl.c - ospflsrtmpl */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 * ospflsrtmpl - fill in OSPF Link State Request packet template
 *------------------------------------------------------------------------
 */
struct ep *
ospflsrtmpl(struct ospf_if *pif)
{
	struct ep		*pep;
	struct ip		*pip;
	struct ospf		*po;

	pep = (struct ep *)getbuf(Net.netpool);
	if ((int)pep == SYSERR)
		return 0;
	pip = (struct ip *)pep->ep_data;
	po = (struct ospf *)pip->ip_data;
	po->ospf_version = OSPF_VERSION;
	po->ospf_type = T_LSREQ;
	po->ospf_len = MINHDRLEN;
	po->ospf_rid = pif->if_rid;
	po->ospf_aid = pif->if_area->ar_id;
	po->ospf_authtype = pif->if_area->ar_authtype;
	memcpy(po->ospf_auth, pif->if_auth, AUTHLEN);
	return pep;
}
