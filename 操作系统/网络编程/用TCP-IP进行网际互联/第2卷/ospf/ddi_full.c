/* ddi_full.c - ddi_full */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 * ddi_full - handle DD packet input for FULL and LOADING state neighbors
 *------------------------------------------------------------------------
 */
int
ddi_full(struct ospf_if *pif, struct ospf_nb *pnb, struct ep *pep)
{
	struct ip	*pip = (struct ip *)pep->ep_data;
	struct ospf	*po = (struct ospf *)((char *)pip + IP_HLEN(pip));
	struct ospf_dd	*pdd = (struct ospf_dd *)po->ospf_data;

	if (((pdd->dd_control & DDC_MSTR) & pnb->nb_master) ||
	    (!(pdd->dd_control & DDC_MSTR) & !pnb->nb_master) ||
	    (pdd->dd_control & DDC_INIT) ||
	    (pdd->dd_opts != pnb->nb_opts))
		return nb_mismatch(pif, pnb);
	if (pnb->nb_master && pdd->dd_seq == pnb->nb_seq-1)
		return 0;		/* duplicate; master discards */
	if (!pnb->nb_master && pdd->dd_seq == pnb->nb_seq) {
		dd_xmit(pif, pnb);	/* duplicate; slave responds */
		return 1;
	}
	/* else, NOT a duplicate; Sequence mismatch */
	return nb_mismatch(pif, pnb);
}
