/* ddi_exstart.c - ddi_exstart */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 * ddi_exstart - handle Data Descrip. input for EXSTART state neighbors
 *------------------------------------------------------------------------
 */
void
ddi_exstart(struct ospf_if *pif, struct ospf_nb *pnb, struct ep *pep)
{
	struct ip	*pip = (struct ip *)pep->ep_data;
	struct ospf	*po = (struct ospf *)((char *)pip + IP_HLEN(pip));
	struct ospf_dd	*pdd = (struct ospf_dd *)po->ospf_data;
	struct ep	*peptmp;
	unsigned int	cbits = DDC_INIT | DDC_MORE | DDC_MSTR;

	if (((pdd->dd_control & cbits) == cbits) &&
	    po->ospf_len == MINDDLEN &&
	    net2hl(pnb->nb_rid) > net2hl(pif->if_rid)) {
		pnb->nb_master = FALSE;
		pnb->nb_seq = pdd->dd_seq;
		pnb->nb_opts = pdd->dd_opts;
		pnb->nb_state = NBS_EXCHNG;
	} else if (((pdd->dd_control&(DDC_INIT|DDC_MSTR)) == 0) &&
	    pdd->dd_seq == pnb->nb_seq &&
	    net2hl(pnb->nb_rid) < net2hl(pif->if_rid)) {
		pnb->nb_master = TRUE;
		pnb->nb_opts = pdd->dd_opts;
		pnb->nb_state = NBS_EXCHNG;
	} else
		return;
	if (peptmp = (struct ep *)deq(pnb->nb_dsl))
		freebuf(peptmp);
	if (pnb->nb_master)
		pnb->nb_seq++;
	lsr_queue(pif, pnb, pep);
	dd_queue(pif, pnb);
}
