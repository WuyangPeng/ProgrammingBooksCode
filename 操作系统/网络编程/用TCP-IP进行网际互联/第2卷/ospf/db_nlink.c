/* db_nlink.c - db_nlink */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  db_nlink - add self-originated network link ads to database
 *------------------------------------------------------------------------
 */
void
db_nlink(struct ospf_if *pif)
{
	struct ospf_ar	*par = pif->if_area;
	struct ospf_db	*pdb;
	struct ospf_lsa	lsa;
	struct ospf_na	*pna;
	struct ospf_nb	*pnb;
	int		rc, i;
	int		ifn = pif - &ospf_if[0];

	if (pif->if_drid != pif->if_rid)
		return;
	lsa.lsa_age = 0;
	lsa.lsa_opts = 0;
	lsa.lsa_type = LST_NLINK;
	lsa.lsa_lsid = nif[ifn].ni_ip;
	lsa.lsa_rid = pif->if_rid;
	lsa.lsa_seq = LSA_ISEQ;
	lsa.lsa_len = LSA_NLEN;
	pna = (struct ospf_na *)lsa.lsa_data;
	pna->na_mask = nif[ifn].ni_mask;
	rc = 0;
	pnb = &pif->if_nbtab[0];
	for (i=0; i<MAXNBR+1; ++i, ++pnb) {
		if (pnb->nb_state < NBS_FULL)
			continue;
		lsa.lsa_len += 4;	/* size of one RID */
		pna->na_rid[rc++] = pnb->nb_rid;
	}
	lsa.lsa_cksum = 0;
/*	lsa.lsa_cksum = fcksum((char *)&lsa + 2, lsa.lsa_len - 2); */
	db_update(par, &lsa);
}
