/* nb_add.c - nb_add */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  nb_add - add a neighbor to our neighbor list (update timer if present)
 *------------------------------------------------------------------------
 */
struct ospf_nb *
nb_add(struct ospf_if *pif, struct ospf *po)
{
	struct ospf_hello	*poh = (struct ospf_hello *)po->ospf_data;
	struct ospf_nb		*pnb, *pnbfree;
	int			nn;

	wait(pif->if_nbmutex);
	pnb = &pif->if_nbtab[1];
	pnbfree = 0;
	for (nn=0; nn<MAXNBR; ++nn, ++pnb) {
		if (pnbfree == 0 && pnb->nb_state == NBS_DOWN) {
			pnbfree = pnb;
			continue;
		}
		if (pnb->nb_rid == po->ospf_rid)
			break;
	}
	if (nn >= MAXNBR)
		pnb = pnbfree;
	if (pnb) {
		if (pnb->nb_state < NBS_INIT) {
			pnb->nb_rid = po->ospf_rid;
			pnb->nb_prio = 0;
			pnb->nb_drid = 0;
			pnb->nb_brid = 0;
			pnb->nb_lsal = pnb->nb_dsl = EMPTY;
			pnb->nb_lsrl = EMPTY;
			pnb->nb_state = NBS_INIT;
			pnb->nb_tlastdd = 0;
		}
		pnb->nb_lastheard = pif->if_rdintv;
	}
	signal(pif->if_nbmutex);
	return pnb;
}
