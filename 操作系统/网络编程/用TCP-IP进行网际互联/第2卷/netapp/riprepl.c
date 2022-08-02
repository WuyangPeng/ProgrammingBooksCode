/* riprepl.c - riprepl */

#include <conf.h>
#include <kernel.h>
#include <network.h>

#ifdef	RIP
/*------------------------------------------------------------------------
 *  riprepl  -  process a received RIP request
 *------------------------------------------------------------------------
 */
int
riprepl(struct rip *pripin, unsigned len, IPaddr gw, unsigned short port)
{
	struct	ep	*pep;
	struct	rip	*prip;
	struct	route	*prt;
	int		rn, nrts;

	nrts = (len - RIPHSIZE)/sizeof(struct riprt);
	if (nrts == 1 && pripin->rip_rts[0].rr_family == 0 &&
	    net2hl(pripin->rip_rts[0].rr_metric) == RIP_INFINITY)
		return ripsend(gw, port);	/* send the full table	*/
	pep = (struct ep *)getbuf(Net.netpool);
	/* get to the RIP data... */
	prip = (struct rip *)((struct udp *)
		((struct ip *)pep->ep_data)->ip_data)->u_data;
	memcpy(prip, pripin, len);
	for (rn = 0; rn < nrts; ++rn) {
		struct riprt	*rp = &prip->rip_rts[rn];

		if (net2hs(rp->rr_family) != AF_INET)
			continue;
		prt = rtget(rp->rr_ipa, RTF_LOCAL);
		if (prt) {
			rp->rr_metric = hl2net(prt->rt_metric);
			rtfree(prt);
		} else
			rp->rr_metric = hl2net(RIP_INFINITY);
	}
	prip->rip_cmd = RIP_RESPONSE;
	prip->rip_vers = RIP_VERSION;
	prip->rip_mbz = 0;
	udpsend(gw, port, UP_RIP, pep, len, 1);
	return OK;
}
#endif	/* RIP */
