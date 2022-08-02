/* ospfhtmpl.c - ospfhtmpl */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 * ospfhtmpl - fill in OSPF HELLO packet template
 *------------------------------------------------------------------------
 */
struct ep *
ospfhtmpl(struct ospf_if *pif)
{
	struct ep		*pep;
	struct ip		*pip;
	struct ospf		*po;
	struct ospf_hello	*poh;

	pep = (struct ep *)getbuf(Net.netpool);
	if ((int)pep == SYSERR)
		return 0;
	pep->ep_order =  ~0;
	pip = (struct ip *)pep->ep_data;
	po = (struct ospf *)pip->ip_data;
	poh = (struct ospf_hello *)po->ospf_data;
	po->ospf_version = OSPF_VERSION;
	po->ospf_type = T_HELLO;
	po->ospf_len = MINHELLOLEN;
	po->ospf_rid = pif->if_rid;
	po->ospf_aid = pif->if_area->ar_id;
	po->ospf_authtype = pif->if_area->ar_authtype;
	memcpy(po->ospf_auth, pif->if_auth, AUTHLEN);
	poh->oh_hintv = net2hs(pif->if_hintv);
	poh->oh_opts = pif->if_opts;
	poh->oh_rdintv = net2hl(pif->if_rdintv);
	poh->oh_prio = pif->if_prio;
	poh->oh_drid = pif->if_drid;
	poh->oh_brid = pif->if_brid;
	return pep;
}
