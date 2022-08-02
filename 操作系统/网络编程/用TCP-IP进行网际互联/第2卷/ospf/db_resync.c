/* db_resync.c - db_resync */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  db_resync - fix network DB entries after change to/from designated rtr
 *------------------------------------------------------------------------
 */
void
db_resync(struct ospf_if *pif)
{
	struct ospf_ar	*par = pif->if_area;
	struct ospf_db	*pdb;
	struct ospf_lsa	lsa;
	struct ospf_na	*pna;
	int		ifn = pif - &ospf_if[0];

	if (pif->if_drid == pif->if_rid) { /* newly the designate */
		db_nlink(pif);
		return;
	}
/* else, need to delete network lsa here XXX*/
}
