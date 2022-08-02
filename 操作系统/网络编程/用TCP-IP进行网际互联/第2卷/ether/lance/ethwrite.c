/* ethwrite.c - ethwrite */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <network.h>

#include <ospf.h>

/*------------------------------------------------------------------------
 *  ethwrite - write a single packet to the ethernet
 *------------------------------------------------------------------------
 */
ethwrite(devptr, pep, len)
struct	devsw	*devptr;
struct	ep	*pep;
int	len;
{
	STATWORD ps;
        struct	etblk	*etptr;

	etptr = (struct etblk *)devptr->dvioblk;
	if (len > EP_MAXLEN) {
		nif[etptr->etintf].ni_odiscard++;
		freebuf(pep);
		return SYSERR;
	}
	/* subtract the local header */
	len -= (int)&pep->ep_eh - (int)pep;
	if (len < EP_MINLEN)
		len = EP_MINLEN;
	blkcopy(pep->ep_src, etptr->etpaddr, EP_ALEN);
	pep->ep_len = len;
	pep->ep_type = hs2net(pep->ep_type);

#ifdef	DEBUG
	if (pep->ep_type == EPT_IP)
	{
		struct ip *pip = (struct ip *)pep->ep_data;
		if (pip->ip_proto == IPT_OSPF) {
			struct ospf *po = (struct ospf *)pip->ip_data;
			if (po->ospf_type != T_HELLO) {
				kprintf("ethwrite(%X, %d)\n", pep, len);
				pdump(pep);
			}
		}
	}
#endif	DEBUG
	if (enq(etptr->etoutq, pep, 0) < 0) {
		nif[etptr->etintf].ni_odiscard++;
		freebuf(pep);
		return SYSERR;
	}
	ethwstrt(etptr);
	return OK;
}
