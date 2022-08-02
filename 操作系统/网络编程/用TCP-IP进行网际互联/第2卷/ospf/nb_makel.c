/* nb_makel.c - nb_makel */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>
#include <q.h>

/*------------------------------------------------------------------------
 *  nb_makel - create a new adjacency's retransmission lists
 *------------------------------------------------------------------------
 */
int
nb_makel(struct ospf_nb *pnb)
{
	pnb->nb_lsal = newq(NBMAXLIST, QF_WAIT);
	pnb->nb_dsl = newq(NBMAXLIST, QF_WAIT);
	pnb->nb_lsrl = newq(NBMAXLIST, QF_WAIT);
}
