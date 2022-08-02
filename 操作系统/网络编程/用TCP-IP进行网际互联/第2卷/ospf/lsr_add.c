/* lsr_add.c - lsr_add */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

struct ep *ospflsrtmpl(struct ospf_if *);

/*------------------------------------------------------------------------
 *  lsr_add - add a link state summary to a link state request packet
 *------------------------------------------------------------------------
 */
struct ep *
lsr_add(struct ospf_if *pif, struct ospf_lss *plss, struct ep *pep)
{
	struct ip	*pip;
	struct ospf	*po;
	struct ospf_lsr	*plsr;

	if (pep == 0) {
		pep = ospflsrtmpl(pif);
		if (pep == 0)
			return 0;
	}
	pip = (struct ip *)pep->ep_data;
	po = (struct ospf *)pip->ip_data;
	plsr = (struct ospf_lsr *)((char *)po + po->ospf_len);
	plsr->lsr_type = net2hl((unsigned long)plss->lss_type);
	plsr->lsr_lsid = plss->lss_lsid;
	plsr->lsr_rid = plss->lss_rid;
	po->ospf_len += LSRLEN;
	return pep;
}
