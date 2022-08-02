/* ospftimer.c - ospftimer */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 * ospftimer - update neighbor time-out values
 *------------------------------------------------------------------------
 */
int
ospftimer(int delay)
{
	struct ospf_if	*pif;
	struct ospf_nb	*pnb;
	int		ifn, i;

	pif = &ospf_if[0];
	for (ifn=0; ifn<NIF; ++ifn, ++pif) {
		switch (pif->if_state) {
		case IFS_DOWN:
			continue;
		case IFS_WAITING:
			pif->if_twait -= delay;
			if (pif->if_twait <= 0)
				if_elect(ifn);
			break;
		default:
			break;
		}
		wait(pif->if_nbmutex);
		pnb = &ospf_if[ifn].if_nbtab[1];
		for (i=0; i<MAXNBR; ++i, ++pnb) {
			if (pnb->nb_state == NBS_DOWN)
				continue;
			pnb->nb_lastheard -= delay;
			if (pnb->nb_lastheard <= 0) {
				pnb->nb_state = NBS_DOWN;
				pif->if_event |= IFE_NCHNG;
			}
			if (pnb->nb_state == NBS_EXSTART) {
				pnb->nb_trexmt -= delay;
				if (pnb->nb_trexmt <= 0)
					nb_rexmt(pif, pnb);
			}
			if (pnb->nb_state >= NBS_FULL &&
			    pnb->nb_tlastdd > 0) {
				pnb->nb_tlastdd -= delay;
				if (pnb->nb_tlastdd < 0)
					freebuf(deq(pnb->nb_dsl));
			}
			if (headq(pnb->nb_lsrl)) {
				pnb->nb_tlsr -= delay;
				if (pnb->nb_tlsr <= 0)
					lsr_xmit(pif, pnb);
			}
		}
		signal(pif->if_nbmutex);
		if (pif->if_event & IFE_NCHNG) {
			if_elect(ifn);
			pif->if_event &= ~IFE_NCHNG;
		}
	}
}
