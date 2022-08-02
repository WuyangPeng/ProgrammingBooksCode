/* nb_mismatch.c - nb_mismatch */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  nb_mismatch - handle sequence # mismatch event
 *------------------------------------------------------------------------
 */
int
nb_mismatch(struct ospf_if *pif, struct ospf_nb *pnb)
{
	struct ep	*pep;

	pnb->nb_state = NBS_EXSTART;
	
	/* empty lists */
	while (pep = (struct ep *)deq(pnb->nb_lsal))
		freebuf(pep);
	while (pep = (struct ep *)deq(pnb->nb_dsl))
		freebuf(pep);
	while (pep = (struct ep *)deq(pnb->nb_lsrl))
		freebuf(pep);
	pnb->nb_seq++;
	dd_queue(pif, pnb);
	return 0;
}
