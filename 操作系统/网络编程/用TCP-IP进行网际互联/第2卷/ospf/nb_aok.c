/* nb_aok.c - nb_aok */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  nb_aok - determine if adjacency with a neighbor is ok
 *------------------------------------------------------------------------
 */
int
nb_aok(struct ospf_if *pif, struct ospf_nb *pnb)
{
	if (pif->if_type == IFT_PT2PT || pif->if_type  == IFT_VIRTUAL)
		return TRUE;
	if (pif->if_drid == pif->if_rid || pif->if_brid == pif->if_rid)
		return TRUE;
	if (pif->if_drid == pnb->nb_rid || pif->if_brid == pnb->nb_rid)
		return TRUE;
	return FALSE;
}
