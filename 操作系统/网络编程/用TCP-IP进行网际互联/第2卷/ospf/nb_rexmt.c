/* nb_rexmt.c - nb_rexmt */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  nb_rexmt - handle neighbor retransmit timer event
 *------------------------------------------------------------------------
 */
int
nb_rexmt(struct ospf_if *pif, struct ospf_nb *pnb)
{
	if (pnb->nb_state == NBS_EXSTART) {
		dd_xmit(pif, pnb);
		pnb->nb_trexmt = pif->if_rintv;
	}
}
