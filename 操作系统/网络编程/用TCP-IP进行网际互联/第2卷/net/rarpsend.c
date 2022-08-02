/* rarpsend.c - rarpsend */

#include <conf.h>
#include <kernel.h>
#include <network.h>
#include <proc.h>

static struct ep *mkarp(int,short,short,IPaddr,IPaddr);

/*------------------------------------------------------------------------
 *  rarpsend  -  broadcast a RARP packet to obtain my IP address
 *------------------------------------------------------------------------
 */
int
rarpsend(int ifn)
{
	STATWORD		ps;
	struct	netif		*pni = &nif[ifn];
	struct	ep		*pep;
	int			i, mypid, resp;
	IPaddr			junk = 0; /* arg to mkarp; never used */

	mypid = getpid();
	for (i=0; i<ARP_MAXRETRY; ++i) {
		pep = mkarp(ifn, EPT_RARP, RA_REQUEST, junk, junk);
		if ((int)pep == SYSERR)
			break;
		disable(ps);
		rarppid = mypid;
		restore(ps);
		recvclr();
		write(pni->ni_dev, pep, EP_MINLEN);
		/* ARP_RESEND is in secs, recvtim uses 1/10's of secs	*/
		resp = recvtim(10*ARP_RESEND<<i);
		if (resp != TIMEOUT) {
			/* host route */
			rtadd(pni->ni_ip, ip_maskall, pni->ni_ip, 0,
				NI_LOCAL, RT_INF);

			/* non-subnetted route */
			rtadd(pni->ni_net, ip_maskall, pni->ni_ip, 0,
				NI_LOCAL, RT_INF);

			return OK;
		}
	}
	panic("No response to RARP");
	return SYSERR;
}


/*------------------------------------------------------------------------
 *  mkarp  -  allocate and fill in an ARP or RARP packet
 *------------------------------------------------------------------------
 */
static
struct ep *
mkarp(int ifn, short type, short op, IPaddr spa, IPaddr tpa)
{
	register struct	arp	*parp;
	struct	ep		*pep;

	pep = (struct ep *) getbuf(Net.netpool);
	if ((int)pep == SYSERR)
		return (struct ep *)SYSERR;
	memcpy(pep->ep_dst, nif[ifn].ni_hwb.ha_addr, EP_ALEN);
	pep->ep_order = ~0;
	pep->ep_type = type;
	parp = (struct arp *)pep->ep_data;
	parp->ar_hwtype = hs2net(AR_HARDWARE);
	parp->ar_prtype = hs2net(EPT_IP);
	parp->ar_hwlen = EP_ALEN;
	parp->ar_prlen = IP_ALEN;
	parp->ar_op = hs2net(op);
	memcpy(SHA(parp), nif[ifn].ni_hwa.ha_addr, EP_ALEN);
	memcpy(SPA(parp), &spa, IP_ALEN);
	memcpy(THA(parp), nif[ifn].ni_hwa.ha_addr, EP_ALEN);
	memcpy(TPA(parp), &tpa, IP_ALEN);
	return pep;
}
