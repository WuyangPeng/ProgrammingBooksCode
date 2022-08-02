/* if_elect1.c - if_elect1 */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 * if_elect1 - make one neighbor list pass in the election algorithm
 *------------------------------------------------------------------------
 */
int
if_elect1(struct ospf_if *pif,struct ospf_nb **ppdr,struct ospf_nb **ppbr)
{
	unsigned long	brid, drid;
	Bool		bdecl, cdecl;
	struct ospf_nb	*pnb, *pdr, *pbr;
	int		i;

	drid = pif->if_drid;
	brid = pif->if_brid;
	bdecl = FALSE;
	pdr = pbr = 0;
	pnb = &pif->if_nbtab[0];
	for (i=0; i<=MAXNBR; ++i, ++pnb) {
		if (pnb->nb_state < NBS_2WAY)
			continue;
		if (pnb->nb_rid == pnb->nb_drid) {
			/* neighbor claims designated routership */

			if (pdr) {
				if (pnb->nb_prio < pdr->nb_prio)
					continue;
				if ((pnb->nb_prio == pdr->nb_prio) &&
				    (net2hl(pnb->nb_rid) <
				     net2hl(pdr->nb_rid)))
					continue;
			}
			pdr = pnb;
			continue;
		} /* else pnb is a backup candidate */

		cdecl = pnb->nb_rid == pnb->nb_brid;
		if (bdecl && !cdecl)
			continue;
		if (cdecl && !bdecl) {
			bdecl = TRUE;
			pbr = pnb;
			continue;
		}
		if (pbr == 0) {
			pbr = pnb;
			continue;
		}
		if (pnb->nb_prio < pbr->nb_prio)
			continue;
		if ((pnb->nb_prio == pbr->nb_prio) &&
		    (net2hl(pnb->nb_rid) < net2hl(pbr->nb_rid)))
			continue;
		pbr = pnb;	/* new backup */
	}
	*ppbr = pbr;
	*ppdr = pdr;
}
