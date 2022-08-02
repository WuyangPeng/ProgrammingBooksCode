/* db_update.c - db_update */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  db_update - update/insert a link state advertisement
 *------------------------------------------------------------------------
 */
int
db_update(struct ospf_ar *par, struct ospf_lsa *plsa)
{
	struct ospf_db	*pdb;

	if (pdb = db_lookup(par, plsa->lsa_type, plsa->lsa_lsid)) {
	} else {
		int	hv;

		pdb = db_new(par, plsa);
		pdb->db_lnext = par->ar_dblhead;
		par->ar_dblhead = pdb;
		hv = DBHASH(pdb->db_lsa.lsa_lsid);
		pdb->db_hnext = par->ar_htable[hv];
		par->ar_htable[hv] = pdb;
	}
}
