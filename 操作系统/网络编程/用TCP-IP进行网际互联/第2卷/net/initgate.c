/* initgate.c - initgate */

#include <conf.h>
#include <kernel.h>
#include <bufpool.h>
#include <network.h>

/* static IP addresses, if used */

static	IPaddr	iftoip[] = { 0, 0, 0x800A0B00, 0x800A0C00 };

#ifdef	OTHER1
static	int	itod[] = { NI_LOCAL, ETHER, OTHER1, OTHER2 };
void ofaceinit(unsigned);
#else	OTHER1
static	int	itod[] = { -1, ETHER };
#endif	OTHER1

void efaceinit(unsigned);

/*------------------------------------------------------------------------
 * initgate  --  initialize a gateway's interface structures
 *------------------------------------------------------------------------
 */
int
initgate(void)
{
	int	i;

	Net.netpool = mkpool(MAXNETBUF, NETBUFS);
	Net.lrgpool = mkpool(MAXLRGBUF, LRGBUFS);
	Net.sema = screate(1);
	Net.nif = NIF;

#ifdef	IPADDR1
	iftoip[1] = dot2ip(IPADDR1);
#endif	/* IPADDR1 */

	for (i=0; i<Net.nif; ++i) {
		/* start off with all 0's (esp. statistics) */
		memset(&nif[i], 0, sizeof(nif[i]));

		nif[i].ni_state = NIS_DOWN;
		nif[i].ni_admstate = NIS_UP;
		nif[i].ni_ivalid = nif[i].ni_nvalid = FALSE;
		nif[i].ni_svalid = FALSE;
		nif[i].ni_dev = itod[i];
		nif[i].ni_mcast = 0;
		if (i == NI_LOCAL) {
			/* maxbuf - ether header - CRC - nexthop */
			nif[i].ni_mtu = MAXLRGBUF-EP_HLEN-EP_CRC-IP_ALEN;
			nif[i].ni_ip = ip_anyaddr;
			continue;
		}
		switch(nif[i].ni_dev) {
#if	Noth > 0
		case OTHER1:
		case OTHER2:
				ofaceinit(i);
				break;
#endif	/* Noth > 0 */
		case ETHER:	efaceinit(i);
				break;
		};
	}

	return OK;
}

#if	Noth > 0
void
ofaceinit(unsigned ifn)
{
	struct otblk	*otptr;
	struct etblk	*etptr;
	int		i;

	nif[ifn].ni_ip = iftoip[ifn];

	otptr = (struct otblk *)devtab[nif[ifn].ni_dev].dvioblk;
	otptr->ot_intf = ifn;

	nif[ifn].ni_descr = otptr->ot_descr;
	nif[ifn].ni_mtype = 1;	/* RFC 1156, "other" :-)	*/
	nif[ifn].ni_speed = 400000000; /* ~25Mz 32 bit mem copy :-)	*/
	nif[ifn].ni_maxreasm = MAXLRGBUF;

	/* fill in physical net addresses */
	memcpy(nif[ifn].ni_hwa.ha_addr, otptr->ot_paddr, EP_ALEN);
	memcpy(nif[ifn].ni_hwb.ha_addr, otptr->ot_baddr, EP_ALEN);
	nif[ifn].ni_hwa.ha_len = nif[ifn].ni_hwb.ha_len = EP_ALEN;

	/* set the mtu */

	if (nif[ifn].ni_dev == OTHER2)
		nif[ifn].ni_mtu = SMALLMTU;
	else
		nif[ifn].ni_mtu = EP_DLEN;

	etptr = (struct etblk *)devtab[otptr->ot_pdev].dvioblk;
	nif[ifn].ni_outq = etptr->etoutq;

	/* net num comes from ether addr */

FIX ME FIX ME
	nif[ifn].ni_ip[IP_ALEN-1] = etptr->etpaddr[EP_ALEN-1];
	nif[ifn].ni_net = netnum(nif[ifn].ni_ip);
	nif[ifn].ni_ivalid = TRUE;

	/* set the mask (same for both) */

	setmask(ifn, 0xffffff00);

	/* host */
	rtadd(nif[ifn].ni_ip, ip_maskall, nif[ifn].ni_ip, 0,
		NI_LOCAL, RT_INF);
	/* broadcast (all 0's, no subnet) */
	rtadd(nif[ifn].ni_net, ip_maskall, nif[ifn].ni_ip, 0,
		NI_LOCAL, RT_INF);
}
#endif	/* Noth > 0 */

void
efaceinit(unsigned ifn)
{
	extern	int	ethmcast(int, int, Eaddr, IPaddr);
	IPaddr	junk;
	struct utdev *pud = (struct utdev *)
			devtab[nif[ifn].ni_dev].dvioblk;

	memcpy(nif[ifn].ni_hwa.ha_addr, pud->ud_paddr, EP_ALEN);
	memcpy(nif[ifn].ni_hwb.ha_addr, pud->ud_bcast, EP_ALEN);
	nif[ifn].ni_descr = pud->ud_descr;
	nif[ifn].ni_mtype = 6;	/* RFC 1156, Ethernet CSMA/CD	*/
	nif[ifn].ni_speed = 10000000;	/* bits per second		*/
	nif[ifn].ni_maxreasm = MAXLRGBUF;
	nif[ifn].ni_hwa.ha_len = EP_ALEN;
	nif[ifn].ni_hwb.ha_len = EP_ALEN;
	nif[ifn].ni_mtu = EP_DLEN;
	nif[ifn].ni_outq = pud->ud_outq;
	nif[ifn].ni_mcast = ethmcast;
	pud->ud_ifnum = ifn;

/* TEMPORARY HACK to avoid RARP +-DLS */
{
	IPaddr mask;

	nif[ifn].ni_ip = iftoip[1];
	nif[ifn].ni_net = netnum(nif[ifn].ni_ip);
	nif[ifn].ni_ivalid = TRUE;
	mask = netmask(nif[ifn].ni_ip);
	setmask(ifn, mask);
/* host route */
	rtadd(nif[ifn].ni_ip, ip_maskall, nif[ifn].ni_ip, 0,
		NI_LOCAL, RT_INF);
/* non subnetted route */
	rtadd(nif[ifn].ni_net, ip_maskall, nif[ifn].ni_ip, 0,
		NI_LOCAL, RT_INF);
}
}
