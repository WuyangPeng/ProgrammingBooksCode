/* riprecv.c - riprecv */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	RIP
/*------------------------------------------------------------------------
 *  riprecv  -  process a received RIP advertisement
 *------------------------------------------------------------------------
 */
int
riprecv(struct rip *prip, unsigned len, IPaddr gw)
{
	struct	route	*prt;
	IPaddr		mask;
	int		nrts, rn, ifnum;

	nrts = (len - RIPHSIZE)/sizeof(struct riprt);
	prt = rtget(gw, RTF_REMOTE);	/* find the interface number	*/
	if (prt == NULL)
		return SYSERR;
	ifnum = prt->rt_ifnum;
	rtfree(prt);
	wait(riplock);		/* prevent updates until we're done	*/
	for (rn=0; rn<nrts; ++rn) {
		struct riprt	*rp = &prip->rip_rts[rn];

		rp->rr_family = net2hs(rp->rr_family);
		rp->rr_metric = net2hl(rp->rr_metric);
		if (!ripok(rp))
			continue;
		mask = netmask(rp->rr_ipa);
		rtadd(rp->rr_ipa, mask, gw, rp->rr_metric,
			ifnum, RIPRTTL);
	}
	signal(riplock);
	return OK;
}
#endif	/* RIP */
