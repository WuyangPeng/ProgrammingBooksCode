/* ospf_hsend.c - ospf_hsend */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

struct ep *ospfhtmpl(struct ospf_if *);

/*------------------------------------------------------------------------
 * ospf_hsend - send OSPF hello packet for an interface
 *------------------------------------------------------------------------
 */
int
ospf_hsend(unsigned ifn)
{
	struct ospf_if		*pif = &ospf_if[ifn];
	struct ep		*pep;
	struct ip		*pip;
	struct ospf		*po;
	struct ospf_hello	*poh;
	struct ospf_nb		*pnb;
	int			i, nn, len;

	pep = ospfhtmpl(pif);
	wait(pif->if_nbmutex);
	pip = (struct ip *) pep->ep_data;
	po = (struct ospf *) pip->ip_data;
	poh = (struct ospf_hello *) po->ospf_data;
	pnb = &pif->if_nbtab[1];
	for (i=0, nn=0; i<MAXNBR; ++i, ++pnb)
		if (pnb->nb_state >= NBS_INIT) {
			poh->oh_neighbor[nn++] = pnb->nb_rid;
			po->ospf_len += sizeof(poh->oh_neighbor[0]);
		}
	signal(pif->if_nbmutex);
	poh->oh_netmask = nif[ifn].ni_mask;
	po->ospf_authtype = net2hs(pif->if_area->ar_authtype);
	len = po->ospf_len;
	po->ospf_len = net2hs(po->ospf_len);
	pep->ep_order &= ~EPO_OSPF;	/* all in net order now */
	memset(po->ospf_auth, 0, AUTHLEN);
	po->ospf_cksum = 0;
	po->ospf_cksum = cksum((WORD *)po, len);
	memcpy(po->ospf_auth, pif->if_area->ar_auth, AUTHLEN);
	pip->ip_src = nif[ifn].ni_ip;
	if (ifn == NI_PRIMARY)
		ipsend(AllSPFRouters, pep, len, IPT_OSPF,
			IPP_INCTL, 1);
	else
		ipsend(nif[ifn].ni_brc, pep, len, IPT_OSPF,
			IPP_INCTL, 1);
}

#if	BYTE_ORDER == LITTLE_ENDIAN
IPaddr AllSPFRouters	= 0x050000E0;	/* 224.0.0.5 */
IPaddr AllDRouters	= 0x060000E0;	/* 224.0.0.6 */
#else	/* BYTE_ORDER == LITTLE_ENDIAN */
IPaddr AllSPFRouters	= 0xE0000005;	/* 224.0.0.5 */
IPaddr AllDRouters	= 0xE0000006;	/* 224.0.0.6 */
#endif	/* BYTE_ORDER == LITTLE_ENDIAN */
