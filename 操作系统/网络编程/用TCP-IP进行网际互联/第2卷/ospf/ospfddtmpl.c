/* ospfddtmpl.c - ospfddtmpl */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 * ospfddtmpl - fill in OSPF Data Description packet template
 *------------------------------------------------------------------------
 */
struct ep *
ospfddtmpl(struct ospf_if *pif)
{
	struct ep	*pep;
	struct ip	*pip;
	struct ospf	*po;
	struct ospf_dd	*pdd;

	pep = (struct ep *)getbuf(Net.netpool);
	if ((int)pep == SYSERR)
		return 0;
	pip = (struct ip *)pep->ep_data;
	po = (struct ospf *)pip->ip_data;
	pdd = (struct ospf_dd *)po->ospf_data;

	po->ospf_version = OSPF_VERSION;
	po->ospf_type = T_DATADESC;
	po->ospf_len = MINDDLEN;
	po->ospf_rid = pif->if_rid;
	po->ospf_aid = pif->if_area->ar_id;
	po->ospf_authtype = pif->if_area->ar_authtype;
	memcpy(po->ospf_auth, pif->if_auth, AUTHLEN);
	pdd->dd_mbz = 0;
	pdd->dd_opts = pif->if_opts;
	pdd->dd_control = 0;
	return pep;
}
