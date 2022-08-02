/* ospfdump.c - ospfdump */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <ospf.h>

static	hdump(), dddump(), lsrdump(), lsudump(), lsadump(), lssdump();

/*------------------------------------------------------------------------
 * ospfdump - pretty-print an OSPF packet to the console
 *------------------------------------------------------------------------
 */
ospfdump(po, dlen, order)
struct ospf	*po;
int		dlen, order;
{
	unsigned long	ospf_aid, ospf_rid;
	unsigned short	ospf_len, ospf_cksum, ospf_authtype;

	if (order & EPO_OSPF) {
		ospf_len = po->ospf_len;
		ospf_rid = po->ospf_rid;
		ospf_aid = po->ospf_aid;
		ospf_cksum = po->ospf_cksum;
		ospf_authtype = po->ospf_authtype;
	} else {
		ospf_len = net2hs(po->ospf_len);
		ospf_rid = net2hl(po->ospf_rid);
		ospf_aid = net2hl(po->ospf_aid);
		ospf_cksum = net2hl(po->ospf_cksum);
		ospf_authtype = net2hl(po->ospf_authtype);
	}
	kprintf("OSPF:\tvers %u\ttype %d\tlen %d\n", po->ospf_version,
		po->ospf_type, ospf_len);
	kprintf("OSPF:\tRID %X AID %X sum %x autype %u\n", ospf_rid,
		ospf_aid, ospf_cksum, ospf_authtype);
	kprintf("OSPF:\tAuth %X %X\n", po->ospf_auth[0], po->ospf_auth[1]);
	dlen -= MINHDRLEN;
/* the rest is assumed to always be in net order */
	switch (po->ospf_type) {
	case T_HELLO:		return hdump(po->ospf_data, dlen, order);
	case T_DATADESC:	return dddump(po->ospf_data, dlen, order);
	case T_LSREQ:		return lsrdump(po->ospf_data, dlen, order);
	case T_LSUPDATE:	return lsudump(po->ospf_data, dlen, order);
	case T_LSACK:		return lsadump(po->ospf_data, dlen, order);
	default:
		kprintf("OSPF: unknown packet type (%d)\n", po->ospf_type);
		hexdump(po->ospf_data, dlen);
	}
	return SYSERR;
}

static
int hdump(struct ospf_hello *poh, int dlen, int order)
{
	int	i;

	kprintf("OSPF: (HELLO)\n");
	kprintf("OSPF:\tnetmask %X hellointv %u opts %x\n",
		net2hl(poh->oh_netmask),
		net2hs(poh->oh_hintv), (unsigned short)poh->oh_opts);
	kprintf("OSPF:\trprio %u deadintv %d\n", (unsigned)poh->oh_prio,
		net2hl(poh->oh_rdintv));
	kprintf("OSPF:\tdesignate %X backup %X\n", net2hl(poh->oh_drid),
		net2hl(poh->oh_brid));
	dlen -= MINHELLOLEN - MINHDRLEN;
	for (i=0; dlen > 0; dlen -= sizeof(long), ++i)
		kprintf("OSPF:\tneighbor %X\n", net2hl(poh->oh_neighbor[i]));
}

static
int dddump(pdd, dlen)
struct ospf_dd		*pdd;
int			dlen;
{
	int	count;

	kprintf("OSPF: (DD)\n");
	kprintf("OSPF: mbz %d opts %x control %x\n", pdd->dd_mbz,
		pdd->dd_opts, pdd->dd_control);
	kprintf("OSPF: seq %08X\n", net2hl(pdd->dd_seq));
	dlen -= MINDDLEN - MINHDRLEN;
	count = 0;
	while (count < dlen)
		count += lssdump((char *)pdd->dd_lss + count, dlen-count);
}


static
int lssdump(plss, len)
struct ospf_lss		*plss;
int			len;
{
	unsigned short	lss_len;

	if (len < LSSHDRLEN) {
		kprintf("OSPF: MALFORMED PACKET resid %d min %d\n",
			len, LSSHDRLEN);
		return len;
	}
	kprintf("OSPF: (LSS)\nOSPF:\tage %u opts %x type %d\n",
		net2hs(plss->lss_age), plss->lss_opts, plss->lss_type);
	kprintf("OSPF:\tLSID %08X RID %08X Seq %08X\n",
		net2hl(plss->lss_lsid),
		net2hl(plss->lss_rid), net2hl(plss->lss_seq));
	kprintf("OSPF:\tcksum %x len %d\n", net2hs(plss->lss_cksum),
		net2hs(plss->lss_len));

	return LSSHDRLEN;
}

static
int lsadump()
{
}

static
int lsrdump(plsr, dlen, order)
struct ospf_lsr	*plsr;
int		dlen;
{
	int	i;
	int 	nlsr = dlen / LSRLEN;

	kprintf("OSPF: (LSR)\n");
	for (i=0; i<nlsr; ++i) {
		kprintf("OSPF:\ttype %d  LSID %08X  RID %08X\n",
			net2hl(plsr->lsr_type), net2hl(plsr->lsr_lsid),
			net2hl(plsr->lsr_rid));
		dlen -= LSRLEN;
		plsr++;
	}
	if (dlen)
		kprintf("OSPF: MALFORMED PACKET resid %d\n", dlen);
	return dlen;
}

static
int lsudump(plsu, dlen)
struct ospf_lsu	*plsu;
int	dlen;
{
	int	nlsa, count;

	dlen -= sizeof(plsu->lsu_nads);
	nlsa = net2hl(plsu->lsu_nads);
	kprintf("OSPF: (LSU) nads %d\n", nlsa);
	count = 0;
	while (count < dlen && nlsa--)
		count += lsadump1((char *)plsu->lsu_data + count, dlen-count);
	dlen -= count;
	if (dlen)
		kprintf("OSPF: MALFORMED PACKET resid %d\n", dlen);
	return dlen;
}

static
lsadump1(plsa, len)
struct ospf_lsa	*plsa;
int		len;
{
	unsigned short	lsalen;

	if (len < LSSHDRLEN) {
		kprintf("OSPF: MALFORMED PACKET resid %d min %d\n",
			len, LSSHDRLEN);
		return len;
	}
	kprintf("OSPF: (LSA)\nOSPF:\tage %u opts %x type %d\n",
		net2hs(plsa->lsa_age), plsa->lsa_opts, plsa->lsa_type);
	kprintf("OSPF:\tLSID %08X RID %08X Seq %08X\n",
		net2hl(plsa->lsa_lsid), net2hl(plsa->lsa_rid),
		net2hl(plsa->lsa_seq));
	lsalen = net2hs(plsa->lsa_len);
	kprintf("OSPF:\tcksum %x len %d\n", net2hs(plsa->lsa_cksum),
		lsalen);

/* check length relative to type of LSA here */
	if (len < lsalen) {
		kprintf("OSPF: MALFORMED PACKET resid %d lsa_len %d\n",
			len, lsalen);
		return len;
	}
	return lsalen;
}
