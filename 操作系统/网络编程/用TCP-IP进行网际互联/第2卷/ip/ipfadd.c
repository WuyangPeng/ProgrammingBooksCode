/* ipfadd.c - ipfadd */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <network.h>

/*------------------------------------------------------------------------
 *  ipfadd  -  add a fragment to an IP fragment queue
 *------------------------------------------------------------------------
 */
Bool
ipfadd(struct ipfq *iq, struct ep *pep)
{
	struct	ip	*pip;
	int		fragoff;

	if (iq->ipf_state != IPFF_VALID) {
		freebuf(pep);
		return FALSE;
	}
	pip = (struct ip *)pep->ep_data;
	fragoff = pip->ip_fragoff & IP_FRAGOFF;

	if (enq(iq->ipf_q, pep, -fragoff) < 0) {
		/* overflow-- free all frags and drop */
		freebuf(pep);
		IpReasmFails++;
		while (pep = (struct ep *)deq(iq->ipf_q)) {
			freebuf(pep);
			IpReasmFails++;
		}
		freeq(iq->ipf_q);
		iq->ipf_state = IPFF_BOGUS;
		return FALSE;
	}
	iq->ipf_ttl = IP_FTTL;		/* restart timer */
	return TRUE;
}
