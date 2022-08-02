/* netwrite.c - netwrite */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#include <ospf.h>

struct	arpentry	*arpalloc();
struct	arpentry	 *arpfind(u_char *, u_short, struct netif *);
int	arpsend(struct arpentry *);
int	local_out(struct ep *);

/*#define	DEBUG */

/*------------------------------------------------------------------------
 * netwrite - write a packet on an interface, using ARP if needed
 *------------------------------------------------------------------------
 */
int
netwrite(struct netif *pni, struct ep *pep, unsigned len)
{
	struct	arpentry 	*pae;
	STATWORD		ps;

	if (pni->ni_state != NIS_UP) {
		freebuf(pep);
		return SYSERR;
	}
	pep->ep_len = len;
#ifdef	DEBUG
if (pni != &nif[NI_LOCAL])
{
struct ip *pip = (struct ip *)pep->ep_data;
	if (pip->ip_proto == IPT_OSPF) {
		struct ospf *po = (struct ospf *)pip->ip_data;
/*		if (po->ospf_type != T_HELLO) { */
{
			kprintf("netwrite(pep %X, len %d)\n", pep, len);
			pdump(pep);
		}
	}
}
#endif	/* DEBUG */
	if (pni == &nif[NI_LOCAL])
		return local_out(pep);
	else if (isbrc(pep->ep_nexthop)) {
		memcpy(pep->ep_dst, pni->ni_hwb.ha_addr, EP_ALEN);
		write(pni->ni_dev, pep, len);
		return OK;
	}
	/* else, look up the protocol address... */

	disable(ps);
	pae = arpfind((u_char *)&pep->ep_nexthop, pep->ep_type, pni);
	if (pae && pae->ae_state == AS_RESOLVED) {
		memcpy(pep->ep_dst, pae->ae_hwa, pae->ae_hwlen);
		restore(ps);
		return write(pni->ni_dev, pep, len);
	}
	if (IP_CLASSD(pep->ep_nexthop)) {
		restore(ps);
		return SYSERR;
	}
	if (pae == 0) {
		pae = arpalloc();
		pae->ae_hwtype = AR_HARDWARE;
		pae->ae_prtype = EPT_IP;
		pae->ae_hwlen = EP_ALEN;
		pae->ae_prlen = IP_ALEN;
		pae->ae_pni = pni;
		pae->ae_queue = EMPTY;
		memcpy(pae->ae_pra, &pep->ep_nexthop, pae->ae_prlen);
		pae->ae_attempts = 0;
		pae->ae_ttl = ARP_RESEND;
		arpsend(pae);
	}
	if (pae->ae_queue == EMPTY)
		pae->ae_queue = newq(ARP_QSIZE, QF_NOWAIT);
	if (enq(pae->ae_queue, pep, 0) < 0)
		freebuf(pep);
	restore(ps);
	return OK;
}
