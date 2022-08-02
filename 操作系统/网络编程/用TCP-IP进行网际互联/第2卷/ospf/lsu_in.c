/* lsu_in.c - lsu_in */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  lsu_in - handle a received link state update packet
 *------------------------------------------------------------------------
 */
void
lsu_in(struct ep *pep)
{
	struct ip	*pip = (struct ip *)pep->ep_data;
	struct ospf	*po;
	struct ospf_if	*pif = &ospf_if[pep->ep_ifn];
	struct ospf_lsu	*plsu;
	struct ospf_db	*pdb, *db_lookup();
	struct ospf_nb	*pnb;
	int		i;

	if (pif->if_state <= IFS_WAITING)
		return;
	pnb = &pif->if_nbtab[1];
	po = (struct ospf *)((char *)pip+IP_HLEN(pip));
	for (i=0; i<MAXNBR; ++i, ++pnb)
		if (pnb->nb_rid == po->ospf_rid)
			break;
	if (i == MAXNBR || pnb->nb_state < NBS_EXCHNG)
		return;
/* db update here */
	if (headq(pnb->nb_lsrl) && lsr_check(pnb))
		freebuf(deq(pnb->nb_lsrl));
/* flooding procedure */
}
