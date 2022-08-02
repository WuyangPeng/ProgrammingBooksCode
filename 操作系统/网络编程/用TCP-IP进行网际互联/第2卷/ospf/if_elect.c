/* if_elect.c - if_elect */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

int if_elect1(struct ospf_if *, struct ospf_nb **, struct ospf_nb **);
void db_resync(struct ospf_if *), nb_reform(struct ospf_if *);

/*------------------------------------------------------------------------
 * if_elect - elect a designated router and backup designated router
 *------------------------------------------------------------------------
 */
void
if_elect(unsigned int ifn)
{
	struct ospf_if	*pif = &ospf_if[ifn];
	struct ospf_nb	*pnb, *pdr, *pbr;
	unsigned long		odrid, obrid;

	wait(pif->if_nbmutex);
	odrid = pif->if_drid;
	obrid = pif->if_brid;
	if_elect1(pif, &pdr, &pbr);
	pif->if_brid = pbr ? pbr->nb_rid : 0;
	if (pdr)
		pif->if_drid = pdr->nb_rid;
	else {
		pif->if_drid = pif->if_brid;
		pif->if_brid = 0;
	}
	/*
	 * if designate or backup has changed in this pass and this
	 * router is old or new designate or backup, run again to get
	 * a backup designate. Also update DB if we were/are designate
	 */
	if ((odrid != pif->if_drid &&
	   (odrid == pif->if_rid || pif->if_drid == pif->if_rid))) {
		if_elect1(pif, &pdr, &pbr);
		pif->if_brid = pbr ? pbr->nb_rid : 0;
		db_resync(pif);
	}
	if ((obrid != pif->if_brid &&
	   (obrid == pif->if_rid || pif->if_brid == pif->if_rid))) {
		if_elect1(pif, &pdr, &pbr);
		pif->if_brid = pbr ? pbr->nb_rid : 0;
	}
	signal(pif->if_nbmutex);
	if (obrid != pif->if_brid || odrid != pif->if_drid) {
		if (pif->if_drid == pif->if_rid)
			pif->if_state = IFS_DR;
		else if (pif->if_brid == pif->if_rid)
			pif->if_state = IFS_BACKUP;
		else
			pif->if_state = IFS_DROTHER;
		nb_reform(pif);
	}
}
