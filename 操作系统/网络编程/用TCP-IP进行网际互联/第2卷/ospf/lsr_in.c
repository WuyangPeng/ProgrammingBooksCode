/* lsr_in.c - lsr_in */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

/*------------------------------------------------------------------------
 *  lsr_in - handle a received link state request packet
 *------------------------------------------------------------------------
 */
void
lsr_in(struct ep *pep)
{
	struct ip	*pipout, *pip = (struct ip *)pep->ep_data;
	struct ospf	*poout, *po;
	struct ospf_if	*pif = &ospf_if[pep->ep_ifn];
	struct ospf_nb	*pnb;
	struct ospf_lsr	*plsr;
	struct ospf_lsu	*plsu;
	struct ospf_db	*pdb;
	struct ep	*pepout, *ospflstmpl(struct ospf_if *);
	unsigned	i, nlsr, maxlsapp;

	if (pif->if_state <= IFS_WAITING)
		return;
	pnb = &pif->if_nbtab[1];
	po = (struct ospf *)((char *)pip+IP_HLEN(pip));
	for (i=0; i<MAXNBR; ++i, ++pnb)
		if (pnb->nb_rid == po->ospf_rid)
			break;
	if (i == MAXNBR || pnb->nb_state < NBS_EXCHNG)
		return;
	maxlsapp = (nif[pep->ep_ifn].ni_mtu - IPMHLEN - MINLSULEN);
	maxlsapp /= (LSSHDRLEN + MAXLSDLEN);
	pepout = ospflstmpl(pif);
	if (pepout == 0)
		return;
	pipout = (struct ip *)pepout->ep_data;
	poout = (struct ospf *)pipout->ip_data;
	plsu = (struct ospf_lsu *)poout->ospf_data;
	
	nlsr = (po->ospf_len - MINHDRLEN) / sizeof (struct ospf_lsr);
	plsr = (struct ospf_lsr *)po->ospf_data;
	for (i=0; i<nlsr; ++i, ++plsr) {
		pdb = db_lookup(pif->if_area, plsr->lsr_type,
			plsr->lsr_lsid);
		if (pdb == 0) {
			freebuf(pepout);
			nb_mismatch(pif, pnb);
			return;
		}
		if (plsu->lsu_nads >= maxlsapp) {
			lsa_send(pif, pip->ip_src, pepout);
			if (!(pepout = ospflstmpl(pif)))
				return;
			pipout = (struct ip *)pepout->ep_data;
			poout = (struct ospf *)pipout->ip_data;
			plsu = (struct ospf_lsu *)poout->ospf_data;
		}
		lsa_add(pif, pepout, pdb);
	}
	lsa_send(pif, pip->ip_src, pepout);
}
