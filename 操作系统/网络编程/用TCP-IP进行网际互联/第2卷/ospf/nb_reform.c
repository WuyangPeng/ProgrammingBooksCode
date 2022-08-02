/* nb_reform.c - nb_reform */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

SYSCALL gettime(unsigned long *);

/*------------------------------------------------------------------------
 *  nb_reform - reform adjacencies after a DR or BDR change
 *------------------------------------------------------------------------
 */
int
nb_reform(struct ospf_if *pif)
{
	struct ospf_nb	*pnb = &pif->if_nbtab[1];
	int		nn;

	for (nn=0; nn<MAXNBR; ++nn, ++pnb) {
		if (pnb->nb_state >= NBS_EXSTART) {
			if (!nb_aok(pif, pnb)) {
				/* break an adjacency */
				pnb->nb_state = NBS_2WAY;
				nb_clearl(pnb);
			}
		} else if (pnb->nb_state == NBS_2WAY) {
			if (nb_aok(pif, pnb)) {
				/* form an adjacency */
				gettime(&pnb->nb_seq);
				pnb->nb_state = NBS_EXSTART;
				nb_makel(pnb);
				dd_queue(pif, pnb);
			}
		}
	}
}
