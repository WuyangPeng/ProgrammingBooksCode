/* dd_queue.c - dd_queue */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  dd_queue - generate Data Description packets
 *------------------------------------------------------------------------
 */
void
dd_queue(struct ospf_if *pif, struct ospf_nb *pnb)
{
	struct	ep	*pep;
	struct	ip	*pip;
	struct	ospf	*po;
	struct	ospf_dd	*pdd;

	pep = ospfddtmpl(pif);
	if (pep == 0)
		return;
	pip = (struct ip *)pep->ep_data;
	po = (struct ospf *)pip->ip_data;
	pdd = (struct ospf_dd *)po->ospf_data;

	if (pnb->nb_state == NBS_EXSTART) {
		pdd->dd_control = DDC_INIT | DDC_MORE | DDC_MSTR;
		pdd->dd_seq = hl2net(pnb->nb_seq);
		if (enq(pnb->nb_dsl, pep, 0) < 0)
			freebuf(pep);
		dd_xmit(pif, pnb);
		pnb->nb_trexmt = pif->if_rintv;
		return;
	}
	/* else we're in EXCHANGE state */
	lss_build(pif, pnb, pep);
	dd_xmit(pif, pnb);
	if (pnb->nb_master)
		pnb->nb_trexmt = pif->if_rintv;
}
