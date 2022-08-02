/* db_lookup.c - db_lookup */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  db_lookup - look up a link state advertisement in the top. database
 *------------------------------------------------------------------------
 */
struct ospf_db *
db_lookup(struct ospf_ar *par, u_long type, u_long lsid)
{
	struct ospf_db	*pdb;

	pdb = par->ar_htable[DBHASH(lsid)];
	for (; pdb; pdb = pdb->db_hnext) {
		if (pdb->db_lsa.lsa_lsid == lsid &&
		    pdb->db_lsa.lsa_type == type)
			break;
	}
	return pdb;
}
