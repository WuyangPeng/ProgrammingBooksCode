/* nb_clearl.c - nb_clearl */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  nb_clearl - clear lists of pending messages for a given neighbor
 *------------------------------------------------------------------------
 */
int
nb_clearl(struct ospf_nb *pnb)
{
	struct ep	*pep;

	while (pep = (struct ep *)deq(pnb->nb_lsal))
		freebuf(pep);
	freeq(pnb->nb_lsal);
	pnb->nb_lsal = EMPTY;

	while (pep = (struct ep *)deq(pnb->nb_dsl))
		freebuf(pep);
	freeq(pnb->nb_dsl);
	pnb->nb_dsl = EMPTY;

	while (pep = (struct ep *)deq(pnb->nb_lsrl))
		freebuf(pep);
	freeq(pnb->nb_lsrl);
	pnb->nb_lsrl = EMPTY;
}
