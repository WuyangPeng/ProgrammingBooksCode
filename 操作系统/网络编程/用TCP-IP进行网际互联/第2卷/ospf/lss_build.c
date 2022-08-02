/* lss_build.c - lss_build */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

#define LSS_ABORT(par, pnb, pep) { \
		signal(par->ar_dbmutex);	\
		if (pep)			\
			freebuf(pep);		\
		pnb->nb_state = NBS_2WAY;	\
		nb_clearl(pnb);	}

/*------------------------------------------------------------------------
 *  lss_build - build link-state summaries for DD packets
 *------------------------------------------------------------------------
 */
void
lss_build(struct ospf_if *pif, struct ospf_nb *pnb, struct ep *pep)
{
	struct ospf_ar	*par = pif->if_area;
	struct ip	*pip = (struct ip *)pep->ep_data;
	struct ospf	*po = (struct ospf *)pip->ip_data;
	struct ospf_dd	*pdd = (struct ospf_dd *)po->ospf_data;
	struct ospf_db	*pdb;
	struct ospf_lss	*plss;
	int		nls, ifn, maxlspp;

	ifn = pif - &ospf_if[0];
	maxlspp = (nif[ifn].ni_mtu - IPMHLEN - MINDDLEN) / LSSHDRLEN;
	wait(par->ar_dbmutex);
	nls = 0;
	for (pdb = par->ar_dblhead; pdb; pdb = pdb->db_lnext) {
		if (nls >= maxlspp) {
			pdd->dd_control = DDC_MORE;
			if (pnb->nb_master)
				pdd->dd_control |= DDC_MSTR;
			if (enq(pnb->nb_dsl, pep, 0) < 0) {
				LSS_ABORT(par, pnb, pep);
				return;
			}
			pep = ospfddtmpl(pif);
			if (pep == 0) {
				LSS_ABORT(par, pnb, pep);
				return;
			}
			pip = (struct ip *)pep->ep_data;
			po = (struct ospf *)pip->ip_data;
			pdd = (struct ospf_dd *)po->ospf_data;
			nls = 0;
		}
		plss = &pdd->dd_lss[nls];
		memcpy(plss, &pdb->db_lsa.lsa_lss, LSSHDRLEN);
		plss->lss_age = hs2net(plss->lss_age);
		plss->lss_seq = hl2net(plss->lss_seq);
		plss->lss_len = hs2net(plss->lss_len);
		po->ospf_len += LSSHDRLEN;
		++nls;
	}
	pdd->dd_control = 0;
	if (pnb->nb_master)
		pdd->dd_control |= DDC_MSTR;
	if (enq(pnb->nb_dsl, pep, 0) < 0) {
		LSS_ABORT(par, pnb, pep);
		return;
	}
	signal(par->ar_dbmutex);
}
