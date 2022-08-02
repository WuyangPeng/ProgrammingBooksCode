/* ospflstmpl.c - ospflstmpl */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 * ospflstmpl - fill in OSPF Link State Update packet template
 *------------------------------------------------------------------------
 */
struct ep *
ospflstmpl(struct ospf_if *pif)
{
	struct ep	*pep;
	struct ip	*pip;
	struct ospf	*po;
	struct ospf_lsu	*plsu;

	pep = (struct ep *)getbuf(Net.netpool);
	if ((int)pep == SYSERR)
		return 0;
	pip = (struct ip *)pep->ep_data;
	po = (struct ospf *)pip->ip_data;
	plsu = (struct ospf_lsu *)po->ospf_data;

	po->ospf_version = OSPF_VERSION;
	po->ospf_type = T_LSUPDATE;
	po->ospf_len = MINLSULEN;
	po->ospf_rid = pif->if_rid;
	po->ospf_aid = pif->if_area->ar_id;
	po->ospf_authtype = pif->if_area->ar_authtype;
	memcpy(po->ospf_auth, pif->if_auth, AUTHLEN);
	plsu->lsu_nads = 0;
	return pep;
}
